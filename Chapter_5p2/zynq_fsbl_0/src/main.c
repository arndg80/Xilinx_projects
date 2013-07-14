/******************************************************************************
*
* (c) Copyright 2012-2013 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Xilinx, Inc.
* and is protected under U.S. and international copyright and other
* intellectual property laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any rights to the
* materials distributed herewith. Except as otherwise provided in a valid
* license issued to you by Xilinx, and to the maximum extent permitted by
* applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
* FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
* IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
* and (2) Xilinx shall not be liable (whether in contract or tort, including
* negligence, or under any other theory of liability) for any loss or damage
* of any kind or nature related to, arising under or in connection with these
* materials, including for any direct, or any indirect, special, incidental,
* or consequential loss or damage (including loss of data, profits, goodwill,
* or any type of loss or damage suffered as a result of any action brought by
* a third party) even if such damage or loss was reasonably foreseeable or
* Xilinx had been advised of the possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-safe, or for use in
* any application requiring fail-safe performance, such as life-support or
* safety devices or systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any other applications
* that could lead to death, personal injury, or severe property or
* environmental damage (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and liability of any use of
* Xilinx products in Critical Applications, subject only to applicable laws
* and regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
*
*******************************************************************************/
/*****************************************************************************/
/**
*
* @file main.c
*
* The main file for the First Stage Boot Loader (FSBL).
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver	Who	Date		Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a jz	06/04/11	Initial release
* 2.00a mb	25/05/12	standalone based FSBL
* 3.00a np/mb	08/03/12	Added call to FSBL user hook - before handoff.
*				DDR ECC initialization added
* 				fsbl print with verbose added
* 				Performance measurement added
* 				Flushed the UART Tx buffer
* 				Added the performance time for ECC DDR init
* 				Added clearing of ECC Error Code
* 				Added the watchdog timer value
* 4.00a sg	02/28/13	Code Cleanup
* 						Fix for CR#681014
* 						Fix for CR#689077
*						Fix for CR#694038
*						Fix for CR#694039
*                       Fix for CR#699475
*                       Removed DDR initialization check
*                       Removed DDR ECC initialization code
*						Modified hand off address check to 1MB
*						Added RSA authentication support
*						Watchdog disabled for AES E-Fuse encryption
* </pre>
*
* @note
* FSBL runs from OCM, Based on the boot mode selected, FSBL will copy
* the partitions from the flash device. If the partition is bitstream then
* the bitstream is programmed in the Fabric and for an partition that is
* an application , FSBL will copy the application into DDR and does a
* handoff.The application should not be starting at the OCM address,
* FSBL does not remap the DDR. Application should use DDR starting from 1MB
*
* FSBL can be stitched along with bitstream and application using bootgen
*
* Refer to fsbl.h file for details on the compilation flags supported in FSBL
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "fsbl.h"
#include "qspi.h"
#include "nand.h"
#include "nor.h"
#include "sd.h"
#include "pcap.h"
#include "image_mover.h"
#include "xparameters.h"
#include "xil_cache.h"
#include "xil_exception.h"
#include "xstatus.h"

#ifdef XPAR_XWDTPS_0_BASEADDR
#include "xwdtps.h"
#endif

#ifdef STDOUT_BASEADDRESS
#include "xuartps_hw.h"
#endif

#ifdef RSA_SUPPORT
#include "rsa.h"
#endif

/************************** Constant Definitions *****************************/


/* Reboot status register defines:
 * 0xF0000000 for FSBL fallback mask to notify Boot Rom
 * 0x60000000 for FSBL to mark that FSBL has not handoff yet
 * 0x00FFFFFF for user application to use across soft reset
 */
#define FSBL_FAIL_MASK		0xF0000000
#define FSBL_IN_MASK		0x60000000

/* The address that holds the base address for the image Boot ROM found */
#define BASEADDR_HOLDER		0xFFFFFFF8

#ifdef XPAR_XWDTPS_0_BASEADDR
#define WDT_DEVICE_ID		XPAR_XWDTPS_0_DEVICE_ID
#define WDT_EXPIRE_TIME		100
#define WDT_CRV_SHIFT		12
#endif

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#ifdef XPAR_XWDTPS_0_BASEADDR
XWdtPs Watchdog;		/* Instance of WatchDog Timer	*/
#endif
/************************** Function Prototypes ******************************/
extern u32 FsblHookBeforeBitstreamDload(void);
extern u32 FsblHookAfterBitstreamDload(void);
extern void FsblHandoffExit(u32 FsblStartAddr);
extern void FsblHandoffJtagExit(void);
extern int ps7_init();
extern void EnablePLtoPSLevelShifter(void);
#ifdef PEEP_CODE
extern void init_ddr(void);
#endif
u32 FsblHookBeforeHandoff(void);
void MarkFSBLIn(void);
void FsblHandoff(u32 FsblStartAddr);
u32 GetResetReason(void);

static void Update_MultiBootRegister(void);
/* Exception handlers */
static void RegisterHandlers(void);
static void Undef_Handler (void);
static void SVC_Handler (void);
static void PreFetch_Abort_Handler (void);
static void Data_Abort_Handler (void);
static void IRQ_Handler (void);
static void FIQ_Handler (void);


#ifdef XPAR_XWDTPS_0_BASEADDR
int InitWatchDog(void);
u32 ConvertTime_WdtCounter(u32 seconds);
void  CheckWDTReset(void);
#endif

/************************** Variable Definitions *****************************/
/*
 * Base Address for the Read Functionality for Image Processing
 */
u32 FlashReadBaseAddress = 0;
/*
 * Silicon Version
 */
u32 Silicon_Version;

extern PartHeader PartitionHeader[MAX_PARTITION_NUMBER];
extern u32 PartitionCount;

extern ImageMoverType MoveImage;
extern XDcfg *DcfgInstPtr;

/*
 * Partition information flags
 */
u8 EncryptedPartitionFlag;
u8 PLPartitionFlag;
u8 PSPartitionFlag;
u8 SignedPartitionFlag;

/*
 * Boot Device flag
 */
u8 LinearBootDeviceFlag;

u32 PcapCtrlRegVal;
/*****************************************************************************/
/**
*
* This is the main function for the FSBL ROM code.
*
*
* @param	None.
*
* @return
*		- XST_SUCCESS to indicate success
*		- XST_FAILURE.to indicate failure
*
* @note
*
****************************************************************************/
int main(void)
{
	u32 BootModeRegister = 0;
	u32 HandoffAddress = 0;
	u32 RebootStatusRegister = 0;
	u32 MultiBootReg = 0;
	u32 ImageStartAddress = 0;
	u32 Status = XST_SUCCESS;
	u32 PartitionNum;
	u32 PartitionDataLength;
	u32 PartitionImageLength;
	u32 PartitionExecAddr;
	u32 PartitionAttr;
	u8 ExecAddrFlag = 0;
	u8 BitstreamFlag;
	PartHeader *HeaderPtr;

#ifdef RSA_SUPPORT
	u32 PartitionTotalSize;
	u32 PartitionLoadAddr;
	u32 PartitionStartAddr;
#endif

#ifdef PEEP_CODE
	/*
	 * PEEP DDR initialization
	 */
	init_ddr();
#else
	/*
	 * PCW initialization for MIO,PLL,CLK and DDR
	 */
	ps7_init();
#endif

	/*
	 * Unlock SLCR for SLCR register write
	 */
	SlcrUnlock();

	/* If Performance measurement is required 
	 * then read the Global Timer value , Please note that the
	 * time taken for mio, clock and ddr initialisation
	 * done in the ps7_init function is not accounted in the FSBL
	 *
	 */
#ifdef FSBL_PERF
	XTime tCur = 0;
	FsblGetGlobalTime(tCur);
#endif

	/*
	 * Flush the Caches
	 */
	Xil_DCacheFlush();

	/*
	 * Disable Data Cache
	 */
	Xil_DCacheDisable();

	/*
	 * Register the Exception handlers
	 */
	RegisterHandlers();
	
	/*
	 * Print the FSBL Banner
	 */
	fsbl_printf(DEBUG_GENERAL,"\n\rXilinx First Stage Boot Loader \n\r");
	fsbl_printf(DEBUG_GENERAL,"Release %d.%d/%d.%d	%s-%s\r\n",
			SDK_RELEASE_VER, SDK_SUB_VER,
			SDK_RELEASE_YEAR, SDK_RELEASE_QUARTER,
			__DATE__,__TIME__);

#ifdef XPAR_PS7_DDR_0_S_AXI_BASEADDR
	/*
	 * PCAP initialization
	 */
	Status = InitPcap();
	if (Status == XST_FAILURE) {
		fsbl_printf(DEBUG_GENERAL,"PCAP_INIT_FAIL \n\r");
		OutputStatus(PCAP_INIT_FAIL);
		FsblFallback();
	}

	fsbl_printf(DEBUG_INFO,"Devcfg driver initialized \r\n");

	/*
	 * Get the Silicon Version
	 */
	GetSiliconVersion();

#ifdef XPAR_XWDTPS_0_BASEADDR
	/*
	 * Check if WDT Reset has occurred or not
	 */
	CheckWDTReset();

	/*
	 * Initialize the Watchdog Timer so that it is ready to use
	 */
	Status = InitWatchDog();
	if (Status == XST_FAILURE) {
		fsbl_printf(DEBUG_GENERAL,"WATCHDOG_INIT_FAIL \n\r");
		OutputStatus(WDT_INIT_FAIL);
		FsblFallback();
	}
	fsbl_printf(DEBUG_INFO,"Watchdog driver initialized \r\n");
#endif

	/*
	 * Get PCAP controller settings
	 */
	PcapCtrlRegVal = XDcfg_GetControlRegister(DcfgInstPtr);

	/*
	 * Check for AES source key
	 */
	if (PcapCtrlRegVal & PCAP_CTRL_PCFG_AES_FUSE_EFUSE_MASK) {
		/*
		 * For E-Fuse AES encryption Watch dog Timer disabled and
		 * User not allowed to do system reset
		 */
#ifdef	XPAR_XWDTPS_0_BASEADDR
		fsbl_printf(DEBUG_INFO,"Watchdog Timer Disabled\r\n");
		XWdtPs_Stop(&Watchdog);
#endif
		fsbl_printf(DEBUG_INFO,"User not allowed to do "
								"any system resets\r\n");
	}

	/*
	 * Store FSBL run state in Reboot Status Register
	 */
	MarkFSBLIn();

	/*
	 * Read bootmode register
	 */
	BootModeRegister = Xil_In32(BOOT_MODE_REG);
	BootModeRegister &= BOOT_MODES_MASK;

	/*
	 * QSPI BOOT MODE
	 */
#ifdef XPAR_PS7_QSPI_LINEAR_0_S_AXI_BASEADDR
	if (BootModeRegister == QSPI_MODE) {
		fsbl_printf(DEBUG_GENERAL,"Boot mode is QSPI\n\r");
		InitQspi();
		MoveImage = QspiAccess;
		fsbl_printf(DEBUG_INFO,"QSPI Init Done \r\n");
	} else
#endif

	/*
	 * NAND BOOT MODE
	 */
#ifdef XPAR_PS7_NAND_0_BASEADDR
	if (BootModeRegister == NAND_FLASH_MODE) {
		/*
	 	* Boot ROM always initialize the nand at lower speed
	 	* This is the chance to put it to an optimum speed for your nand
	 	* device
	 	*/
		fsbl_printf(DEBUG_GENERAL,"Boot mode is NAND\n");

		Status = InitNand();
		if (Status != XST_SUCCESS) {
			fsbl_printf(DEBUG_GENERAL,"NAND_INIT_FAIL \r\n");
			/*
			 * Error Handling here
			 */
			OutputStatus(NAND_INIT_FAIL);
			FsblFallback();
		}
		MoveImage = NandAccess;
		fsbl_printf(DEBUG_INFO,"NAND Init Done \r\n");
	} else
#endif

	/*
	 * NOR BOOT MODE
	 */
	if (BootModeRegister == NOR_FLASH_MODE) {
		fsbl_printf(DEBUG_GENERAL,"Boot mode is NOR\n\r");
		/*
		 * Boot ROM always initialize the nor at lower speed
		 * This is the chance to put it to an optimum speed for your nor
		 * device
		 */
		InitNor();
		fsbl_printf(DEBUG_INFO,"NOR Init Done \r\n");
		MoveImage = NorAccess;
	} else

	/*
	 * SD BOOT MODE
	 */
#ifdef XPAR_PS7_SD_0_S_AXI_BASEADDR
	if (BootModeRegister == SD_MODE) {
		fsbl_printf(DEBUG_GENERAL,"Boot mode is SD\r\n");

		/*
		 * SD initialization returns file open error or success
		 */
		Status = InitSD("BOOT.BIN");
		if (Status != XST_SUCCESS) {
			fsbl_printf(DEBUG_GENERAL,"SD_INIT_FAIL\r\n");
			OutputStatus(SD_INIT_FAIL);
			FsblFallback();
		}
		MoveImage = SDAccess;
		fsbl_printf(DEBUG_INFO,"SD Init Done \r\n");
	} else
#endif

	/*
	 * JTAG  BOOT MODE
	 */
	if (BootModeRegister == JTAG_MODE) {
		fsbl_printf(DEBUG_GENERAL,"Boot mode is JTAG\r\n");
		/*
		 * Stop the Watchdog before JTAG handoff
		 */
#ifdef	XPAR_XWDTPS_0_BASEADDR
		XWdtPs_Stop(&Watchdog);
#endif
		/*
		 * Clear our mark in reboot status register
		 */
		ClearFSBLIn();

		/*
		 * SLCR lock
		 */
		SlcrLock();

		FsblHandoffJtagExit();
	} else {
		fsbl_printf(DEBUG_GENERAL,"ILLEGAL_BOOT_MODE \r\n");
		OutputStatus(ILLEGAL_BOOT_MODE);
		/*
		 * fallback starts, no return
		 */
		FsblFallback();
	}

	fsbl_printf(DEBUG_INFO,"Flash Base Address: 0x%08x\r\n", FlashReadBaseAddress);

	if ((FlashReadBaseAddress != XPS_QSPI_LINEAR_BASEADDR) &&
			(FlashReadBaseAddress != XPS_NAND_BASEADDR) &&
			(FlashReadBaseAddress != XPS_NOR_BASEADDR) &&
			(FlashReadBaseAddress != XPS_SDIO0_BASEADDR)) {
		fsbl_printf(DEBUG_GENERAL,"INVALID_FLASH_ADDRESS \r\n");
		OutputStatus(INVALID_FLASH_ADDRESS);
		FsblFallback();
	}

	/*
	 * NOR and QSPI (parallel) are linear boot devices
	 */
	if ((FlashReadBaseAddress == XPS_NOR_BASEADDR) ||
			(FlashReadBaseAddress == XPS_QSPI_LINEAR_BASEADDR)) {
		fsbl_printf(DEBUG_INFO, "Linear Boot Device\r\n");
		LinearBootDeviceFlag = 1;
	}

	RebootStatusRegister = Xil_In32(REBOOT_STATUS_REG);
	fsbl_printf(DEBUG_INFO,
			"Reboot status register: 0x%08x\r\n",RebootStatusRegister);

#ifdef	XPAR_XWDTPS_0_BASEADDR
	/*
	 * Prevent WDT reset
	 */
	XWdtPs_RestartWdt(&Watchdog);
#endif

	if (Silicon_Version == SILICON_VERSION_1) {
		/*
		 * Clear out fallback mask from previous run
		 * We start from the first partition again
		 */
		if ((RebootStatusRegister & FSBL_FAIL_MASK) ==
					FSBL_FAIL_MASK) {
			fsbl_printf(DEBUG_INFO,
					"Reboot status shows previous run falls back\r\n");
			RebootStatusRegister &= ~(FSBL_FAIL_MASK);
			Xil_Out32(REBOOT_STATUS_REG, RebootStatusRegister);
		}

		/*
		 * Read the image start address
		 */
		ImageStartAddress = *(u32 *)BASEADDR_HOLDER;
	} else {
		/*
		 * read the multiboot register
		 */
		MultiBootReg =  XDcfg_ReadReg(DcfgInstPtr->Config.BaseAddr,
				XDCFG_MULTIBOOT_ADDR_OFFSET);

		fsbl_printf(DEBUG_INFO,"Multiboot Register: 0x%08x\r\n",MultiBootReg);

		/*
		 * Compute the image start address
		 */
		ImageStartAddress = (MultiBootReg & PCAP_MBOOT_REG_REBOOT_OFFSET_MASK)
								* GOLDEN_IMAGE_OFFSET;
	}

	fsbl_printf(DEBUG_INFO,"Image Start Address: 0x%08x\r\n",ImageStartAddress);

	/*
	 * Get partitions header information
	 */
	Status = GetPartitionHeaderInfo(ImageStartAddress);
	if (Status != XST_SUCCESS) {
		fsbl_printf(DEBUG_GENERAL, "Partition Header Load Failed\r\n");
		OutputStatus(GET_HEADER_INFO_FAIL);
		FsblFallback();
	}

    /*
     * First partition header was ignored by FSBL
     * As it contain FSBL partition information
     */
	for (PartitionNum = 1; PartitionNum < PartitionCount; PartitionNum++) {

		fsbl_printf(DEBUG_INFO, "Partition Number: %d\r\n", PartitionNum);

		HeaderPtr = &PartitionHeader[PartitionNum];

		/*
		 * Print partition header information
		 */
        HeaderDump(HeaderPtr);

		/*
		 * Validate partition header
		 */
		Status = ValidateHeader(HeaderPtr);
		if (Status != XST_SUCCESS) {
			fsbl_printf(DEBUG_GENERAL, "INVALID_HEADER_FAIL\r\n");
			OutputStatus(INVALID_HEADER_FAIL);
			FsblFallback();
		}

		/*
		 * Load partition header information in to local variables
		 */
		PartitionDataLength = HeaderPtr->DataWordLen;
		PartitionImageLength = HeaderPtr->ImageWordLen;
		PartitionExecAddr = HeaderPtr->ExecAddr;
		PartitionAttr = HeaderPtr->PartitionAttr;

#ifdef RSA_SUPPORT
		PartitionTotalSize = HeaderPtr->PartitionWordLen;
		PartitionLoadAddr = HeaderPtr->LoadAddr;
		PartitionStartAddr = HeaderPtr->PartitionStart;
#endif

		if (PartitionAttr & ATTRIBUTE_PL_IMAGE_MASK) {
			fsbl_printf(DEBUG_INFO, "Bitstream\r\n");
			PLPartitionFlag = 1;
			PSPartitionFlag = 0;
			BitstreamFlag = 1;
		}

		if (PartitionAttr & ATTRIBUTE_PS_IMAGE_MASK) {
			fsbl_printf(DEBUG_INFO, "Application\r\n");
			PSPartitionFlag = 1;
			PLPartitionFlag = 0;
		}

		/*
		 * Encrypted partition will have different value
		 * for Image length and data length
		 */
		if (PartitionDataLength != PartitionImageLength) {
			fsbl_printf(DEBUG_INFO, "Encrypted\r\n");
			EncryptedPartitionFlag = 1;
		} else {
			EncryptedPartitionFlag = 0;
		}

		/*
		 * RSA signature check
		 */
		if (PartitionAttr & ATTRIBUTE_RSA_PRESENT_MASK) {
			fsbl_printf(DEBUG_INFO, "RSA Signed\r\n");
			SignedPartitionFlag = 1;
		} else {
			SignedPartitionFlag = 0;
		}

		/*
		 * FSBL user hook call before bitstream download
		 */
		if (PLPartitionFlag) {
			Status = FsblHookBeforeBitstreamDload();
			if (Status != XST_SUCCESS) {
				fsbl_printf(DEBUG_GENERAL,"FSBL_BEFORE_BSTREAM_HOOK_FAILED\r\n");
				OutputStatus(FSBL_BEFORE_BSTREAM_HOOK_FAIL);
				FsblFallback();
			}
		}

    	/*
	 	 * Move partitions from boot device
	 	 */
		Status = PartitionMove(ImageStartAddress, HeaderPtr);
		if (Status != XST_SUCCESS) {
			fsbl_printf(DEBUG_GENERAL,"PARTITION_MOVE_FAIL\r\n");
			OutputStatus(PARTITION_MOVE_FAIL);
			FsblFallback();
		}

		/*
		 * FSBL user hook call after bitstream download
		 */
		if (PLPartitionFlag) {
			Status = FsblHookAfterBitstreamDload();
			if (Status != XST_SUCCESS) {
				fsbl_printf(DEBUG_GENERAL,"FSBL_AFTER_BSTREAM_HOOK_FAIL\r\n");
				OutputStatus(FSBL_AFTER_BSTREAM_HOOK_FAIL);
				FsblFallback();
			}
		}

        /*
         * Load execution address of first PS partition
         */
        if (PSPartitionFlag && (!ExecAddrFlag)) {
        	ExecAddrFlag++;
        	HandoffAddress = PartitionExecAddr;
        }

#ifdef RSA_SUPPORT
		if (SignedPartitionFlag) {
			if(PLPartitionFlag) {
				/*
				 * PL partition loaded in to DDR temporary address
				 * for authentication
				 */
				PartitionStartAddr = DDR_TEMP_START_ADDR;
			} else {
				PartitionStartAddr = PartitionLoadAddr;
			}

			/*
	 	 	 * Authentication Partition
	 	 	 */
			Status = AuthenticateParition((u8*)PartitionStartAddr,
							(PartitionTotalSize << WORD_LENGTH_SHIFT));
			if (Status != XST_SUCCESS) {
				fsbl_printf(DEBUG_GENERAL,"AUTHENTICATION_FAIL\r\n");
				OutputStatus(AUTHENTICATION_FAIL);
				FsblFallback();
			}

			/*
			 * Decrypt PS partition
			 */
			if (EncryptedPartitionFlag && PSPartitionFlag) {
				Status = DecryptPartition(PartitionStartAddr,
							PartitionDataLength,
							PartitionImageLength);
				if (Status != XST_SUCCESS) {
					fsbl_printf(DEBUG_GENERAL,"DECRYPTION_FAIL\r\n");
					OutputStatus(DECRYPTION_FAIL);
					FsblFallback();
				}
			}
		}
#endif
	}

	fsbl_printf(DEBUG_INFO,"Handoff Address: 0x%08x\r\n",HandoffAddress);

	/*
	 * Fix for CR #663277
	 * FSBL does't support DDR remap
	 * For ELF with execution address below 1M
	 * FSBL do JTAG exit
	 */
	if (HandoffAddress < DDR_1MB_ADDR) {
		/*
		 * Stop the Watchdog before JTAG handoff
		 */
#ifdef	XPAR_XWDTPS_0_BASEADDR
		XWdtPs_Stop(&Watchdog);
#endif

		fsbl_printf(DEBUG_INFO,"No Execution Address JTAG handoff \r\n");

		ClearFSBLIn();

		/*
		 * Enable level shifter
		 */
		if(BitstreamFlag) {
			EnablePLtoPSLevelShifter();
		}

		/*
		 * FSBL user hook call before handoff to the application
		 */
		Status = FsblHookBeforeHandoff();
		if (Status != XST_SUCCESS) {
			fsbl_printf(DEBUG_GENERAL,"FSBL_HANDOFF_HOOK_FAIL\r\n");
			OutputStatus(FSBL_HANDOFF_HOOK_FAIL);
			FsblFallback();
		}

		/*
		 * SLCR lock
		 */
		SlcrLock();

		/*
		 * JTAG mode exit
		 */
		FsblHandoffJtagExit();
	}

	/*
	 * Enable level shifter
	 */
	if(BitstreamFlag) {
		EnablePLtoPSLevelShifter();
	}

	/*
	 * FSBL user hook call before handoff to the application
	 */
	Status = FsblHookBeforeHandoff();
	if (Status != XST_SUCCESS) {
		fsbl_printf(DEBUG_GENERAL,"FSBL_HANDOFF_HOOK_FAIL\r\n");
 		OutputStatus(FSBL_HANDOFF_HOOK_FAIL);
		FsblFallback();
	}

#ifdef XPAR_PS7_SD_0_S_AXI_BASEADDR
	/*
	 * If using SD, close the file
	 */
	if (BootModeRegister == SD_MODE) {
		ReleaseSD();
	}
#endif

#ifdef XPAR_XWDTPS_0_BASEADDR
	XWdtPs_Stop(&Watchdog);
#endif

	/*
	 * For Performance measurement
	 */
#ifdef FSBL_PERF
	XTime tEnd = 0;
	fsbl_printf(DEBUG_GENERAL,"Total Execution time is ");
	FsblMeasurePerfTime(tCur,tEnd);
#endif

	FsblHandoff(HandoffAddress);
	/*
	 * Should not come over here
	 */
	OutputStatus(ILLEGAL_RETURN);
	FsblFallback();

#else
	OutputStatus(NO_DDR);
	FsblFallback();
#endif

	return Status;
}


/******************************************************************************/
/**
*
* This function reset the CPU and goes for Boot ROM fallback handling
*
* @param	None
*
* @return	None
*
* @note		None
*
****************************************************************************/
void FsblFallback(void)
{
	u32 RebootStatusReg;

	/*
	 * update the Multiboot Register for Golden search hunt
	 */
	Update_MultiBootRegister();

	/*
	 * Notify Boot ROM something is wrong
	 */
	RebootStatusReg =  Xil_In32(REBOOT_STATUS_REG);

	/*
	 * Set the FSBL Fail mask
	 */
	Xil_Out32(REBOOT_STATUS_REG, RebootStatusReg | FSBL_FAIL_MASK);

	/*
	 * Barrier for synchronization
	 */
		asm(
			"dsb\n\t"
			"isb"
		);

	/*
	 * Reset PS, so Boot ROM will restart
	 */
	Xil_Out32(PS_RST_CTRL_REG, PS_RST_MASK);
}


/******************************************************************************/
/**
*
* This function hands the A9/PS to the loaded user code.
*
* @param	none
*
* @return	none
*
* @note		This function does not return.
*
****************************************************************************/
void FsblHandoff(u32 FsblStartAddr) {
	fsbl_printf(DEBUG_GENERAL,"SUCCESSFUL_HANDOFF\r\n");

	OutputStatus(SUCCESSFUL_HANDOFF);

	/*
	 * Clear our mark in reboot status register
	 */
	ClearFSBLIn();

	/*
	 * SLCR lock
	 */
	SlcrLock();

	FsblHandoffExit(FsblStartAddr);

	OutputStatus(ILLEGAL_RETURN);

	FsblFallback();
}

/******************************************************************************/
/**
*
* This function outputs the status for the provided State in the boot process.
*
* @param	State is where in the boot process the output is desired.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void OutputStatus(u32 State)
{
#ifdef STDOUT_BASEADDRESS
	u32 UartReg = 0;

	fsbl_printf(DEBUG_GENERAL,"FSBL Status = 0x%.4x\r\n", State);
	/*
	 * The TX buffer needs to be flushed out
	 * If this is not done some of the prints will not appear on the
	 * serial output
	 */
	UartReg = Xil_In32(STDOUT_BASEADDRESS + XUARTPS_SR_OFFSET);
	while ((UartReg & XUARTPS_SR_TXEMPTY) != XUARTPS_SR_TXEMPTY) {
		UartReg = Xil_In32(STDOUT_BASEADDRESS + XUARTPS_SR_OFFSET);
	}
#endif
}

/******************************************************************************/
/**
*
* This function handles the error and lockdown processing and outputs the status
* for the provided State in the boot process.
*
* This function is called upon exceptions.
*
* @param	State - where in the boot process the error occured.
*
* @return	None.
*
* @note		This function does not return, the PS block is reset
*
****************************************************************************/
void ErrorLockdown(u32 State) 
{
	/*
	 * Store the error status
	 */
	OutputStatus(State);

	/*
	 * Fall back
	 */
	FsblFallback();
}

/******************************************************************************/
/**
*
* This function copies a memory region to another memory region
*
* @param 	s1 is starting address for destination
* @param 	s2 is starting address for the source
* @param 	n is the number of bytes to copy
*
* @return	Starting address for destination
*
****************************************************************************/
void *(memcpy_rom)(void * s1, const void * s2, u32 n)
{
	char *dst = (char *)s1;
	const char *src = (char *)s2;

	/*
	 * Loop and copy
	 */
	while (n-- != 0)
		*dst++ = *src++;
	return s1;
}
/******************************************************************************/
/**
*
* This function copies a string to another, the source string must be null-
* terminated.
*
* @param 	Dest is starting address for the destination string
* @param 	Src is starting address for the source string
*
* @return	Starting address for the destination string
*
****************************************************************************/
char *strcpy_rom(char *Dest, const char *Src)
{
	unsigned i;
	for (i=0; Src[i] != '\0'; ++i)
		Dest[i] = Src[i];
	Dest[i] = '\0';
	return Dest;
}


/******************************************************************************/
/**
*
* This function sets FSBL is running mask in reboot status register
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void MarkFSBLIn(void)
{
	Xil_Out32(REBOOT_STATUS_REG,
		Xil_In32(REBOOT_STATUS_REG) | FSBL_IN_MASK);
}


/******************************************************************************/
/**
*
* This function clears FSBL is running mask in reboot status register
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void ClearFSBLIn(void) 
{
	Xil_Out32(REBOOT_STATUS_REG,
		(Xil_In32(REBOOT_STATUS_REG)) &	~(FSBL_FAIL_MASK));
}

/******************************************************************************/
/**
*
* This function Registers the Exception Handlers
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
static void RegisterHandlers(void) 
{
	Xil_ExceptionInit();

	 /*
	 * Initialize the vector table. Register the stub Handler for each
	 * exception.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_UNDEFINED_INT,
					(Xil_ExceptionHandler)Undef_Handler,
					(void *) 0);
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_SWI_INT,
					(Xil_ExceptionHandler)SVC_Handler,
					(void *) 0);
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_PREFETCH_ABORT_INT,
				(Xil_ExceptionHandler)PreFetch_Abort_Handler,
				(void *) 0);
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_DATA_ABORT_INT,
				(Xil_ExceptionHandler)Data_Abort_Handler,
				(void *) 0);
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
				(Xil_ExceptionHandler)IRQ_Handler,(void *) 0);
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_FIQ_INT,
			(Xil_ExceptionHandler)FIQ_Handler,(void *) 0);

	Xil_ExceptionEnable();

}

static void Undef_Handler (void)
{
	fsbl_printf(DEBUG_GENERAL,"UNDEFINED_HANDLER\r\n");
	ErrorLockdown (EXCEPTION_ID_UNDEFINED_INT);
}

static void SVC_Handler (void)
{
	fsbl_printf(DEBUG_GENERAL,"SVC_HANDLER \r\n");
	ErrorLockdown (EXCEPTION_ID_SWI_INT);
}

static void PreFetch_Abort_Handler (void)
{
	fsbl_printf(DEBUG_GENERAL,"PREFETCH_ABORT_HANDLER \r\n");
	ErrorLockdown (EXCEPTION_ID_PREFETCH_ABORT_INT);
}

static void Data_Abort_Handler (void)
{
	fsbl_printf(DEBUG_GENERAL,"DATA_ABORT_HANDLER \r\n");
	ErrorLockdown (EXCEPTION_ID_DATA_ABORT_INT);
}

static void IRQ_Handler (void)
{
	fsbl_printf(DEBUG_GENERAL,"IRQ_HANDLER \r\n");
	ErrorLockdown (EXCEPTION_ID_IRQ_INT);
}

static void FIQ_Handler (void)
{
	fsbl_printf(DEBUG_GENERAL,"FIQ_HANDLER \r\n");
	ErrorLockdown (EXCEPTION_ID_FIQ_INT);
}


/******************************************************************************/
/**
*
* This function Updates the Multi boot Register to enable golden image
* search for boot rom
*
* @param None
*
* @return
* return  none
*
****************************************************************************/
static void Update_MultiBootRegister(void)
{
	u32 MultiBootReg = 0;

	if (Silicon_Version != SILICON_VERSION_1) {
		/*
		 * Read the mulitboot register
		 */
		MultiBootReg =	XDcfg_ReadReg(DcfgInstPtr->Config.BaseAddr,
					XDCFG_MULTIBOOT_ADDR_OFFSET);

		/*
		 * Incrementing multiboot register by one
		 */
		MultiBootReg++;

		XDcfg_WriteReg(DcfgInstPtr->Config.BaseAddr,
				XDCFG_MULTIBOOT_ADDR_OFFSET,
				MultiBootReg);

		fsbl_printf(DEBUG_INFO,"Updated MultiBootReg = 0x%08x\r\n",
				MultiBootReg);
	}
}


/******************************************************************************
*
* This function reset the CPU and goes for Boot ROM fallback handling
*
* @param	None
*
* @return	None
*
* @note		None
*
*******************************************************************************/

u32 GetResetReason(void)
{
	u32 Regval;

	/* We are using REBOOT_STATUS_REG, we have to use bits 23:16 */
	/* for storing the RESET_REASON register value*/
	Regval = ((Xil_In32(REBOOT_STATUS_REG) >> 16) & 0xFF);

	return Regval;
}


/******************************************************************************
*
* This function Gets the ticks from the Global Timer
*
* @param	Current time
*
* @return
*			None
*
* @note		None
*
*******************************************************************************/
#ifdef FSBL_PERF
void FsblGetGlobalTime (XTime tCur)
{
	XTime_GetTime(&tCur);
}


/******************************************************************************
*
* This function Measures the execution time
*
* @param	Current time , End time
*
* @return
*			None
*
* @note		None
*
*******************************************************************************/
void FsblMeasurePerfTime (XTime tCur, XTime tEnd)
{
	double tDiff = 0.0;
	double tPerfSeconds;
	XTime_GetTime(&tEnd);
	tDiff  = (double)tEnd - (double)tCur;

	/*
	 * Convert tPerf into Seconds
	 */
	tPerfSeconds = tDiff/COUNTS_PER_SECOND;

	/*
	 * Convert tPerf into Seconds
	 */
	tPerfSeconds = tDiff/COUNTS_PER_SECOND;

#if defined(FSBL_DEBUG) || defined(FSBL_DEBUG_INFO)
	printf("%f seconds \r\n",tPerfSeconds);
#endif

}
#endif

/******************************************************************************
*
* This function initializes the Watchdog driver and starts the timer
*
* @param	None
*
* @return
*		- XST_SUCCESS if the Watchdog driver is initialized
*		- XST_FAILURE if Watchdog driver initialization fails
*
* @note		None
*
*******************************************************************************/
#ifdef XPAR_XWDTPS_0_BASEADDR
int InitWatchDog(void)
{
	u32 Status = XST_SUCCESS;
	XWdtPs_Config *ConfigPtr; 	/* Config structure of the WatchDog Timer */
	u32 CounterValue = 1;

	ConfigPtr = XWdtPs_LookupConfig(WDT_DEVICE_ID);
	Status = XWdtPs_CfgInitialize(&Watchdog,
				ConfigPtr,
				ConfigPtr->BaseAddress);
	if (Status != XST_SUCCESS) {
		fsbl_printf(DEBUG_INFO,"Watchdog Driver init Failed \n\r");
		return XST_FAILURE;
	}

	/*
	 * Setting the divider value
	 */
	XWdtPs_SetControlValue(&Watchdog,
			XWDTPS_CLK_PRESCALE,
			XWDTPS_CCR_PSCALE_4096);
	/*
	 * Convert time to  Watchdog counter reset value
	 */
	CounterValue = ConvertTime_WdtCounter(WDT_EXPIRE_TIME);

	/*
	 * Set the Watchdog counter reset value
	 */
	XWdtPs_SetControlValue(&Watchdog,
			XWDTPS_COUNTER_RESET,
			CounterValue);
	/*
	 * enable reset output, as we are only using this as a basic counter
	 */
	XWdtPs_EnableOutput(&Watchdog, XWDTPS_RESET_SIGNAL);

	/*
	 * Start the Watchdog timer
	 */
	XWdtPs_Start(&Watchdog);

	XWdtPs_RestartWdt(&Watchdog);

	return XST_SUCCESS;
}


/******************************************************************************/
/**
*
* This function checks whether WDT reset has happened during FSBL run
*
* If WDT reset happened during FSBL run, then need to fallback
*
* @param	None.
*
* @return
*		None
*
* @note		None
*
****************************************************************************/
void CheckWDTReset(void)
{
	u32 ResetReason;
	u32 RebootStatusRegister;

	RebootStatusRegister = Xil_In32(REBOOT_STATUS_REG);

	/*
	 *  For 1.0 Silicon the reason for Reset is in the ResetReason Register
	 * Hence this register can be read to know the cause for previous reset
	 * that happened.
	 * Check if that reset is a Software WatchDog reset that happened
	 */
	if (Silicon_Version == SILICON_VERSION_1) {
		ResetReason = Xil_In32(RESET_REASON_REG);
	} else {
		ResetReason = GetResetReason();
	}
	/*
	 * If the FSBL_IN_MASK Has not been cleared, WDT happened
	 * before FSBL exits
	 */
	if ((ResetReason & RESET_REASON_SWDT) == RESET_REASON_SWDT ) {
		if ((RebootStatusRegister & FSBL_FAIL_MASK) == FSBL_IN_MASK) {
			/*
			 * Clear the SWDT Reset bit
			 */
			ResetReason &= ~RESET_REASON_SWDT;
			if (Silicon_Version == SILICON_VERSION_1) {
				/*
				 * for 1.0 Silicon we need to write
				 * 1 to the RESET REASON Clear register 
				 */
				Xil_Out32(RESET_REASON_CLR, 1);
			} else {
				Xil_Out32(REBOOT_STATUS_REG, ResetReason);
			}

			fsbl_printf(DEBUG_GENERAL,"WDT_RESET_OCCURED \n\r");
		}
	}
}


/******************************************************************************
*
* This function converts time into Watchdog counter value
*
* @param	watchdog expire time in seconds
*
* @return
*			Counter value for Watchdog
*
* @note		None
*
*******************************************************************************/
u32 ConvertTime_WdtCounter(u32 seconds)
{
	double time = 0.0;
	double CounterValue;
	u32 Crv = 0;
	u32 Prescaler,PrescalerValue;

	Prescaler = XWdtPs_GetControlValue(&Watchdog, XWDTPS_CLK_PRESCALE);

	if (Prescaler == XWDTPS_CCR_PSCALE_0008)
		PrescalerValue = 8;
	if (Prescaler == XWDTPS_CCR_PSCALE_0064)
		PrescalerValue = 64;
	if (Prescaler == XWDTPS_CCR_PSCALE_4096)
		PrescalerValue = 4096;

	time = (double)(PrescalerValue) / (double)XPAR_PS7_WDT_0_WDT_CLK_FREQ_HZ;

	CounterValue = seconds / time;

	Crv = (u32)CounterValue;
	Crv >>= WDT_CRV_SHIFT;

	return Crv;
}

#endif


/******************************************************************************
*
* This function Gets the Silicon Version
*
* @param	None
*
* @return 	Silicon_Version
*
* @note		None
*
*******************************************************************************/
void GetSiliconVersion(void)
{
	/*
	 * Get the silicon version
	 */
	Silicon_Version = XDcfg_GetPsVersion(DcfgInstPtr);
	if(Silicon_Version == SILICON_VERSION_3_1) {
		fsbl_printf( DEBUG_GENERAL,"Silicon Version 3.1\r\n");
	} else {
		fsbl_printf( DEBUG_GENERAL,"Silicon Version %d.0\r\n", Silicon_Version + 1);
	}
}


