#ChipScope Core Generator Project File Version 3.0
#
################################################################################
##
## Copyright(C) 2010 - 2011 Xilinx, Inc. All rights reserved.
##
## This file contains confidential and proprietary information
## of Xilinx, Inc. and is protected under U.S. and
## international copyright and other intellectual property
## laws.
##
## DISCLAIMER
## This disclaimer is not a license and does not grant any
## rights to the materials distributed herewith. Except as
## otherwise provided in a valid license issued to you by
## Xilinx, and to the maximum extent permitted by applicable
## law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
## WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
## AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
## BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
## INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
## (2) Xilinx shall not be liable (whether in contract or tort,
## including negligence, or under any other theory of
## liability) for any loss or damage of any kind or nature
## related to, arising under or in connection with these
## materials, including for any direct, or any indirect,
## special, incidental, or consequential loss or damage
## (including loss of data, profits, goodwill, or any type of
## loss or damage suffered as a result of any action brought
## by a third party) even if such damage or loss was
## reasonably foreseeable or Xilinx had been advised of the
## possibility of the same.
##
## CRITICAL APPLICATIONS
## Xilinx products are not designed or intended to be fail-
## safe, or for use in any application requiring fail-safe
## performance, such as life-support or safety devices or
## systems, Class III medical devices, nuclear facilities,
## applications related to the deployment of airbags, or any
## other applications that could lead to death, personal
## injury, or severe property or environmental damage
## (individually and collectively, "Critical
## Applications"). Customer assumes the sole risk and
## liability of any use of Xilinx products in Critical
## Applications, subject only to applicable laws and
## regulations governing limitations on product liability.
##
## THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
## PART OF THIS FILE AT ALL TIMES. 
##
################################################################################
##
## CDC file
##
################################################################################

SignalExport.type=ila
SignalExport.clockChannel=CLK
SignalExport.dataEqualsTrigger=false

# triger ports

SignalExport.triggerPortCount=10 
SignalExport.triggerPortWidth<0000>=32
SignalExport.triggerPortWidth<0001>=5
SignalExport.triggerPortWidth<0002>=32
SignalExport.triggerPortWidth<0003>=5
SignalExport.triggerPortWidth<0004>=4
SignalExport.triggerPortWidth<0005>=1
SignalExport.triggerPortWidth<0006>=32
SignalExport.triggerPortWidth<0007>=4
SignalExport.triggerPortWidth<0008>=32
SignalExport.triggerPortWidth<0009>=6
 
SignalExport.triggerPort<0000>.name=MON_AXI_ARADDR
SignalExport.triggerPort<0001>.name=MON_AXI_ARADDRCONTROL
SignalExport.triggerPort<0002>.name=MON_AXI_AWADDR
SignalExport.triggerPort<0003>.name=MON_AXI_AWADDRCONTROL
SignalExport.triggerPort<0004>.name=MON_AXI_BRESP
SignalExport.triggerPort<0005>.name=MON_AXI_GLOBAL
SignalExport.triggerPort<0006>.name=MON_AXI_RDATA
SignalExport.triggerPort<0007>.name=MON_AXI_RDATACONTROL
SignalExport.triggerPort<0008>.name=MON_AXI_WDATA
SignalExport.triggerPort<0009>.name=MON_AXI_WDATACONTROL
 
SignalExport.triggerPortIsData<0000>=false
SignalExport.triggerPortIsData<0001>=false
SignalExport.triggerPortIsData<0002>=false
SignalExport.triggerPortIsData<0003>=false
SignalExport.triggerPortIsData<0004>=false
SignalExport.triggerPortIsData<0005>=false
SignalExport.triggerPortIsData<0006>=false
SignalExport.triggerPortIsData<0007>=false
SignalExport.triggerPortIsData<0008>=false
SignalExport.triggerPortIsData<0009>=false
 
SignalExport.triggerChannel<0000><0000>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[0]
SignalExport.triggerChannel<0000><0001>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[1]
SignalExport.triggerChannel<0000><0002>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[2]
SignalExport.triggerChannel<0000><0003>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[3]
SignalExport.triggerChannel<0000><0004>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[4]
SignalExport.triggerChannel<0000><0005>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[5]
SignalExport.triggerChannel<0000><0006>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[6]
SignalExport.triggerChannel<0000><0007>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[7]
SignalExport.triggerChannel<0000><0008>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[8]
SignalExport.triggerChannel<0000><0009>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[9]
SignalExport.triggerChannel<0000><0010>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[10]
SignalExport.triggerChannel<0000><0011>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[11]
SignalExport.triggerChannel<0000><0012>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[12]
SignalExport.triggerChannel<0000><0013>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[13]
SignalExport.triggerChannel<0000><0014>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[14]
SignalExport.triggerChannel<0000><0015>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[15]
SignalExport.triggerChannel<0000><0016>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[16]
SignalExport.triggerChannel<0000><0017>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[17]
SignalExport.triggerChannel<0000><0018>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[18]
SignalExport.triggerChannel<0000><0019>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[19]
SignalExport.triggerChannel<0000><0020>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[20]
SignalExport.triggerChannel<0000><0021>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[21]
SignalExport.triggerChannel<0000><0022>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[22]
SignalExport.triggerChannel<0000><0023>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[23]
SignalExport.triggerChannel<0000><0024>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[24]
SignalExport.triggerChannel<0000><0025>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[25]
SignalExport.triggerChannel<0000><0026>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[26]
SignalExport.triggerChannel<0000><0027>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[27]
SignalExport.triggerChannel<0000><0028>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[28]
SignalExport.triggerChannel<0000><0029>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[29]
SignalExport.triggerChannel<0000><0030>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[30]
SignalExport.triggerChannel<0000><0031>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[31]
SignalExport.triggerChannel<0001><0000>=axi_gpio_0.S_AXI/MON_AXI_ARPROT[0]
SignalExport.triggerChannel<0001><0001>=axi_gpio_0.S_AXI/MON_AXI_ARPROT[1]
SignalExport.triggerChannel<0001><0002>=axi_gpio_0.S_AXI/MON_AXI_ARPROT[2]
SignalExport.triggerChannel<0001><0003>=axi_gpio_0.S_AXI/MON_AXI_ARREADY
SignalExport.triggerChannel<0001><0004>=axi_gpio_0.S_AXI/MON_AXI_ARVALID
SignalExport.triggerChannel<0002><0000>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[0]
SignalExport.triggerChannel<0002><0001>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[1]
SignalExport.triggerChannel<0002><0002>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[2]
SignalExport.triggerChannel<0002><0003>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[3]
SignalExport.triggerChannel<0002><0004>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[4]
SignalExport.triggerChannel<0002><0005>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[5]
SignalExport.triggerChannel<0002><0006>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[6]
SignalExport.triggerChannel<0002><0007>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[7]
SignalExport.triggerChannel<0002><0008>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[8]
SignalExport.triggerChannel<0002><0009>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[9]
SignalExport.triggerChannel<0002><0010>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[10]
SignalExport.triggerChannel<0002><0011>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[11]
SignalExport.triggerChannel<0002><0012>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[12]
SignalExport.triggerChannel<0002><0013>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[13]
SignalExport.triggerChannel<0002><0014>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[14]
SignalExport.triggerChannel<0002><0015>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[15]
SignalExport.triggerChannel<0002><0016>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[16]
SignalExport.triggerChannel<0002><0017>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[17]
SignalExport.triggerChannel<0002><0018>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[18]
SignalExport.triggerChannel<0002><0019>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[19]
SignalExport.triggerChannel<0002><0020>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[20]
SignalExport.triggerChannel<0002><0021>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[21]
SignalExport.triggerChannel<0002><0022>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[22]
SignalExport.triggerChannel<0002><0023>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[23]
SignalExport.triggerChannel<0002><0024>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[24]
SignalExport.triggerChannel<0002><0025>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[25]
SignalExport.triggerChannel<0002><0026>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[26]
SignalExport.triggerChannel<0002><0027>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[27]
SignalExport.triggerChannel<0002><0028>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[28]
SignalExport.triggerChannel<0002><0029>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[29]
SignalExport.triggerChannel<0002><0030>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[30]
SignalExport.triggerChannel<0002><0031>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[31]
SignalExport.triggerChannel<0003><0000>=axi_gpio_0.S_AXI/MON_AXI_AWPROT[0]
SignalExport.triggerChannel<0003><0001>=axi_gpio_0.S_AXI/MON_AXI_AWPROT[1]
SignalExport.triggerChannel<0003><0002>=axi_gpio_0.S_AXI/MON_AXI_AWPROT[2]
SignalExport.triggerChannel<0003><0003>=axi_gpio_0.S_AXI/MON_AXI_AWREADY
SignalExport.triggerChannel<0003><0004>=axi_gpio_0.S_AXI/MON_AXI_AWVALID
SignalExport.triggerChannel<0004><0000>=axi_gpio_0.S_AXI/MON_AXI_BREADY
SignalExport.triggerChannel<0004><0001>=axi_gpio_0.S_AXI/MON_AXI_BRESP[0]
SignalExport.triggerChannel<0004><0002>=axi_gpio_0.S_AXI/MON_AXI_BRESP[1]
SignalExport.triggerChannel<0004><0003>=axi_gpio_0.S_AXI/MON_AXI_BVALID
SignalExport.triggerChannel<0005><0000>=axi_gpio_0.S_AXI/MON_AXI_ARESETN
SignalExport.triggerChannel<0006><0000>=axi_gpio_0.S_AXI/MON_AXI_RDATA[0]
SignalExport.triggerChannel<0006><0001>=axi_gpio_0.S_AXI/MON_AXI_RDATA[1]
SignalExport.triggerChannel<0006><0002>=axi_gpio_0.S_AXI/MON_AXI_RDATA[2]
SignalExport.triggerChannel<0006><0003>=axi_gpio_0.S_AXI/MON_AXI_RDATA[3]
SignalExport.triggerChannel<0006><0004>=axi_gpio_0.S_AXI/MON_AXI_RDATA[4]
SignalExport.triggerChannel<0006><0005>=axi_gpio_0.S_AXI/MON_AXI_RDATA[5]
SignalExport.triggerChannel<0006><0006>=axi_gpio_0.S_AXI/MON_AXI_RDATA[6]
SignalExport.triggerChannel<0006><0007>=axi_gpio_0.S_AXI/MON_AXI_RDATA[7]
SignalExport.triggerChannel<0006><0008>=axi_gpio_0.S_AXI/MON_AXI_RDATA[8]
SignalExport.triggerChannel<0006><0009>=axi_gpio_0.S_AXI/MON_AXI_RDATA[9]
SignalExport.triggerChannel<0006><0010>=axi_gpio_0.S_AXI/MON_AXI_RDATA[10]
SignalExport.triggerChannel<0006><0011>=axi_gpio_0.S_AXI/MON_AXI_RDATA[11]
SignalExport.triggerChannel<0006><0012>=axi_gpio_0.S_AXI/MON_AXI_RDATA[12]
SignalExport.triggerChannel<0006><0013>=axi_gpio_0.S_AXI/MON_AXI_RDATA[13]
SignalExport.triggerChannel<0006><0014>=axi_gpio_0.S_AXI/MON_AXI_RDATA[14]
SignalExport.triggerChannel<0006><0015>=axi_gpio_0.S_AXI/MON_AXI_RDATA[15]
SignalExport.triggerChannel<0006><0016>=axi_gpio_0.S_AXI/MON_AXI_RDATA[16]
SignalExport.triggerChannel<0006><0017>=axi_gpio_0.S_AXI/MON_AXI_RDATA[17]
SignalExport.triggerChannel<0006><0018>=axi_gpio_0.S_AXI/MON_AXI_RDATA[18]
SignalExport.triggerChannel<0006><0019>=axi_gpio_0.S_AXI/MON_AXI_RDATA[19]
SignalExport.triggerChannel<0006><0020>=axi_gpio_0.S_AXI/MON_AXI_RDATA[20]
SignalExport.triggerChannel<0006><0021>=axi_gpio_0.S_AXI/MON_AXI_RDATA[21]
SignalExport.triggerChannel<0006><0022>=axi_gpio_0.S_AXI/MON_AXI_RDATA[22]
SignalExport.triggerChannel<0006><0023>=axi_gpio_0.S_AXI/MON_AXI_RDATA[23]
SignalExport.triggerChannel<0006><0024>=axi_gpio_0.S_AXI/MON_AXI_RDATA[24]
SignalExport.triggerChannel<0006><0025>=axi_gpio_0.S_AXI/MON_AXI_RDATA[25]
SignalExport.triggerChannel<0006><0026>=axi_gpio_0.S_AXI/MON_AXI_RDATA[26]
SignalExport.triggerChannel<0006><0027>=axi_gpio_0.S_AXI/MON_AXI_RDATA[27]
SignalExport.triggerChannel<0006><0028>=axi_gpio_0.S_AXI/MON_AXI_RDATA[28]
SignalExport.triggerChannel<0006><0029>=axi_gpio_0.S_AXI/MON_AXI_RDATA[29]
SignalExport.triggerChannel<0006><0030>=axi_gpio_0.S_AXI/MON_AXI_RDATA[30]
SignalExport.triggerChannel<0006><0031>=axi_gpio_0.S_AXI/MON_AXI_RDATA[31]
SignalExport.triggerChannel<0007><0000>=axi_gpio_0.S_AXI/MON_AXI_RREADY
SignalExport.triggerChannel<0007><0001>=axi_gpio_0.S_AXI/MON_AXI_RRESP[0]
SignalExport.triggerChannel<0007><0002>=axi_gpio_0.S_AXI/MON_AXI_RRESP[1]
SignalExport.triggerChannel<0007><0003>=axi_gpio_0.S_AXI/MON_AXI_RVALID
SignalExport.triggerChannel<0008><0000>=axi_gpio_0.S_AXI/MON_AXI_WDATA[0]
SignalExport.triggerChannel<0008><0001>=axi_gpio_0.S_AXI/MON_AXI_WDATA[1]
SignalExport.triggerChannel<0008><0002>=axi_gpio_0.S_AXI/MON_AXI_WDATA[2]
SignalExport.triggerChannel<0008><0003>=axi_gpio_0.S_AXI/MON_AXI_WDATA[3]
SignalExport.triggerChannel<0008><0004>=axi_gpio_0.S_AXI/MON_AXI_WDATA[4]
SignalExport.triggerChannel<0008><0005>=axi_gpio_0.S_AXI/MON_AXI_WDATA[5]
SignalExport.triggerChannel<0008><0006>=axi_gpio_0.S_AXI/MON_AXI_WDATA[6]
SignalExport.triggerChannel<0008><0007>=axi_gpio_0.S_AXI/MON_AXI_WDATA[7]
SignalExport.triggerChannel<0008><0008>=axi_gpio_0.S_AXI/MON_AXI_WDATA[8]
SignalExport.triggerChannel<0008><0009>=axi_gpio_0.S_AXI/MON_AXI_WDATA[9]
SignalExport.triggerChannel<0008><0010>=axi_gpio_0.S_AXI/MON_AXI_WDATA[10]
SignalExport.triggerChannel<0008><0011>=axi_gpio_0.S_AXI/MON_AXI_WDATA[11]
SignalExport.triggerChannel<0008><0012>=axi_gpio_0.S_AXI/MON_AXI_WDATA[12]
SignalExport.triggerChannel<0008><0013>=axi_gpio_0.S_AXI/MON_AXI_WDATA[13]
SignalExport.triggerChannel<0008><0014>=axi_gpio_0.S_AXI/MON_AXI_WDATA[14]
SignalExport.triggerChannel<0008><0015>=axi_gpio_0.S_AXI/MON_AXI_WDATA[15]
SignalExport.triggerChannel<0008><0016>=axi_gpio_0.S_AXI/MON_AXI_WDATA[16]
SignalExport.triggerChannel<0008><0017>=axi_gpio_0.S_AXI/MON_AXI_WDATA[17]
SignalExport.triggerChannel<0008><0018>=axi_gpio_0.S_AXI/MON_AXI_WDATA[18]
SignalExport.triggerChannel<0008><0019>=axi_gpio_0.S_AXI/MON_AXI_WDATA[19]
SignalExport.triggerChannel<0008><0020>=axi_gpio_0.S_AXI/MON_AXI_WDATA[20]
SignalExport.triggerChannel<0008><0021>=axi_gpio_0.S_AXI/MON_AXI_WDATA[21]
SignalExport.triggerChannel<0008><0022>=axi_gpio_0.S_AXI/MON_AXI_WDATA[22]
SignalExport.triggerChannel<0008><0023>=axi_gpio_0.S_AXI/MON_AXI_WDATA[23]
SignalExport.triggerChannel<0008><0024>=axi_gpio_0.S_AXI/MON_AXI_WDATA[24]
SignalExport.triggerChannel<0008><0025>=axi_gpio_0.S_AXI/MON_AXI_WDATA[25]
SignalExport.triggerChannel<0008><0026>=axi_gpio_0.S_AXI/MON_AXI_WDATA[26]
SignalExport.triggerChannel<0008><0027>=axi_gpio_0.S_AXI/MON_AXI_WDATA[27]
SignalExport.triggerChannel<0008><0028>=axi_gpio_0.S_AXI/MON_AXI_WDATA[28]
SignalExport.triggerChannel<0008><0029>=axi_gpio_0.S_AXI/MON_AXI_WDATA[29]
SignalExport.triggerChannel<0008><0030>=axi_gpio_0.S_AXI/MON_AXI_WDATA[30]
SignalExport.triggerChannel<0008><0031>=axi_gpio_0.S_AXI/MON_AXI_WDATA[31]
SignalExport.triggerChannel<0009><0000>=axi_gpio_0.S_AXI/MON_AXI_WREADY
SignalExport.triggerChannel<0009><0001>=axi_gpio_0.S_AXI/MON_AXI_WSTRB[0]
SignalExport.triggerChannel<0009><0002>=axi_gpio_0.S_AXI/MON_AXI_WSTRB[1]
SignalExport.triggerChannel<0009><0003>=axi_gpio_0.S_AXI/MON_AXI_WSTRB[2]
SignalExport.triggerChannel<0009><0004>=axi_gpio_0.S_AXI/MON_AXI_WSTRB[3]
SignalExport.triggerChannel<0009><0005>=axi_gpio_0.S_AXI/MON_AXI_WVALID
 

# data ports
SignalExport.dataPortWidth=153
 
SignalExport.dataChannel<0000>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[0]
SignalExport.dataChannel<0001>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[1]
SignalExport.dataChannel<0002>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[2]
SignalExport.dataChannel<0003>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[3]
SignalExport.dataChannel<0004>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[4]
SignalExport.dataChannel<0005>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[5]
SignalExport.dataChannel<0006>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[6]
SignalExport.dataChannel<0007>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[7]
SignalExport.dataChannel<0008>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[8]
SignalExport.dataChannel<0009>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[9]
SignalExport.dataChannel<0010>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[10]
SignalExport.dataChannel<0011>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[11]
SignalExport.dataChannel<0012>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[12]
SignalExport.dataChannel<0013>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[13]
SignalExport.dataChannel<0014>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[14]
SignalExport.dataChannel<0015>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[15]
SignalExport.dataChannel<0016>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[16]
SignalExport.dataChannel<0017>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[17]
SignalExport.dataChannel<0018>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[18]
SignalExport.dataChannel<0019>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[19]
SignalExport.dataChannel<0020>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[20]
SignalExport.dataChannel<0021>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[21]
SignalExport.dataChannel<0022>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[22]
SignalExport.dataChannel<0023>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[23]
SignalExport.dataChannel<0024>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[24]
SignalExport.dataChannel<0025>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[25]
SignalExport.dataChannel<0026>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[26]
SignalExport.dataChannel<0027>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[27]
SignalExport.dataChannel<0028>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[28]
SignalExport.dataChannel<0029>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[29]
SignalExport.dataChannel<0030>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[30]
SignalExport.dataChannel<0031>=axi_gpio_0.S_AXI/MON_AXI_ARADDR[31]
SignalExport.dataChannel<0032>=axi_gpio_0.S_AXI/MON_AXI_ARPROT[0]
SignalExport.dataChannel<0033>=axi_gpio_0.S_AXI/MON_AXI_ARPROT[1]
SignalExport.dataChannel<0034>=axi_gpio_0.S_AXI/MON_AXI_ARPROT[2]
SignalExport.dataChannel<0035>=axi_gpio_0.S_AXI/MON_AXI_ARREADY
SignalExport.dataChannel<0036>=axi_gpio_0.S_AXI/MON_AXI_ARVALID
SignalExport.dataChannel<0037>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[0]
SignalExport.dataChannel<0038>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[1]
SignalExport.dataChannel<0039>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[2]
SignalExport.dataChannel<0040>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[3]
SignalExport.dataChannel<0041>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[4]
SignalExport.dataChannel<0042>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[5]
SignalExport.dataChannel<0043>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[6]
SignalExport.dataChannel<0044>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[7]
SignalExport.dataChannel<0045>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[8]
SignalExport.dataChannel<0046>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[9]
SignalExport.dataChannel<0047>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[10]
SignalExport.dataChannel<0048>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[11]
SignalExport.dataChannel<0049>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[12]
SignalExport.dataChannel<0050>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[13]
SignalExport.dataChannel<0051>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[14]
SignalExport.dataChannel<0052>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[15]
SignalExport.dataChannel<0053>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[16]
SignalExport.dataChannel<0054>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[17]
SignalExport.dataChannel<0055>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[18]
SignalExport.dataChannel<0056>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[19]
SignalExport.dataChannel<0057>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[20]
SignalExport.dataChannel<0058>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[21]
SignalExport.dataChannel<0059>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[22]
SignalExport.dataChannel<0060>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[23]
SignalExport.dataChannel<0061>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[24]
SignalExport.dataChannel<0062>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[25]
SignalExport.dataChannel<0063>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[26]
SignalExport.dataChannel<0064>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[27]
SignalExport.dataChannel<0065>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[28]
SignalExport.dataChannel<0066>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[29]
SignalExport.dataChannel<0067>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[30]
SignalExport.dataChannel<0068>=axi_gpio_0.S_AXI/MON_AXI_AWADDR[31]
SignalExport.dataChannel<0069>=axi_gpio_0.S_AXI/MON_AXI_AWPROT[0]
SignalExport.dataChannel<0070>=axi_gpio_0.S_AXI/MON_AXI_AWPROT[1]
SignalExport.dataChannel<0071>=axi_gpio_0.S_AXI/MON_AXI_AWPROT[2]
SignalExport.dataChannel<0072>=axi_gpio_0.S_AXI/MON_AXI_AWREADY
SignalExport.dataChannel<0073>=axi_gpio_0.S_AXI/MON_AXI_AWVALID
SignalExport.dataChannel<0074>=axi_gpio_0.S_AXI/MON_AXI_BREADY
SignalExport.dataChannel<0075>=axi_gpio_0.S_AXI/MON_AXI_BRESP[0]
SignalExport.dataChannel<0076>=axi_gpio_0.S_AXI/MON_AXI_BRESP[1]
SignalExport.dataChannel<0077>=axi_gpio_0.S_AXI/MON_AXI_BVALID
SignalExport.dataChannel<0078>=axi_gpio_0.S_AXI/MON_AXI_ARESETN
SignalExport.dataChannel<0079>=axi_gpio_0.S_AXI/MON_AXI_RDATA[0]
SignalExport.dataChannel<0080>=axi_gpio_0.S_AXI/MON_AXI_RDATA[1]
SignalExport.dataChannel<0081>=axi_gpio_0.S_AXI/MON_AXI_RDATA[2]
SignalExport.dataChannel<0082>=axi_gpio_0.S_AXI/MON_AXI_RDATA[3]
SignalExport.dataChannel<0083>=axi_gpio_0.S_AXI/MON_AXI_RDATA[4]
SignalExport.dataChannel<0084>=axi_gpio_0.S_AXI/MON_AXI_RDATA[5]
SignalExport.dataChannel<0085>=axi_gpio_0.S_AXI/MON_AXI_RDATA[6]
SignalExport.dataChannel<0086>=axi_gpio_0.S_AXI/MON_AXI_RDATA[7]
SignalExport.dataChannel<0087>=axi_gpio_0.S_AXI/MON_AXI_RDATA[8]
SignalExport.dataChannel<0088>=axi_gpio_0.S_AXI/MON_AXI_RDATA[9]
SignalExport.dataChannel<0089>=axi_gpio_0.S_AXI/MON_AXI_RDATA[10]
SignalExport.dataChannel<0090>=axi_gpio_0.S_AXI/MON_AXI_RDATA[11]
SignalExport.dataChannel<0091>=axi_gpio_0.S_AXI/MON_AXI_RDATA[12]
SignalExport.dataChannel<0092>=axi_gpio_0.S_AXI/MON_AXI_RDATA[13]
SignalExport.dataChannel<0093>=axi_gpio_0.S_AXI/MON_AXI_RDATA[14]
SignalExport.dataChannel<0094>=axi_gpio_0.S_AXI/MON_AXI_RDATA[15]
SignalExport.dataChannel<0095>=axi_gpio_0.S_AXI/MON_AXI_RDATA[16]
SignalExport.dataChannel<0096>=axi_gpio_0.S_AXI/MON_AXI_RDATA[17]
SignalExport.dataChannel<0097>=axi_gpio_0.S_AXI/MON_AXI_RDATA[18]
SignalExport.dataChannel<0098>=axi_gpio_0.S_AXI/MON_AXI_RDATA[19]
SignalExport.dataChannel<0099>=axi_gpio_0.S_AXI/MON_AXI_RDATA[20]
SignalExport.dataChannel<0100>=axi_gpio_0.S_AXI/MON_AXI_RDATA[21]
SignalExport.dataChannel<0101>=axi_gpio_0.S_AXI/MON_AXI_RDATA[22]
SignalExport.dataChannel<0102>=axi_gpio_0.S_AXI/MON_AXI_RDATA[23]
SignalExport.dataChannel<0103>=axi_gpio_0.S_AXI/MON_AXI_RDATA[24]
SignalExport.dataChannel<0104>=axi_gpio_0.S_AXI/MON_AXI_RDATA[25]
SignalExport.dataChannel<0105>=axi_gpio_0.S_AXI/MON_AXI_RDATA[26]
SignalExport.dataChannel<0106>=axi_gpio_0.S_AXI/MON_AXI_RDATA[27]
SignalExport.dataChannel<0107>=axi_gpio_0.S_AXI/MON_AXI_RDATA[28]
SignalExport.dataChannel<0108>=axi_gpio_0.S_AXI/MON_AXI_RDATA[29]
SignalExport.dataChannel<0109>=axi_gpio_0.S_AXI/MON_AXI_RDATA[30]
SignalExport.dataChannel<0110>=axi_gpio_0.S_AXI/MON_AXI_RDATA[31]
SignalExport.dataChannel<0111>=axi_gpio_0.S_AXI/MON_AXI_RREADY
SignalExport.dataChannel<0112>=axi_gpio_0.S_AXI/MON_AXI_RRESP[0]
SignalExport.dataChannel<0113>=axi_gpio_0.S_AXI/MON_AXI_RRESP[1]
SignalExport.dataChannel<0114>=axi_gpio_0.S_AXI/MON_AXI_RVALID
SignalExport.dataChannel<0115>=axi_gpio_0.S_AXI/MON_AXI_WDATA[0]
SignalExport.dataChannel<0116>=axi_gpio_0.S_AXI/MON_AXI_WDATA[1]
SignalExport.dataChannel<0117>=axi_gpio_0.S_AXI/MON_AXI_WDATA[2]
SignalExport.dataChannel<0118>=axi_gpio_0.S_AXI/MON_AXI_WDATA[3]
SignalExport.dataChannel<0119>=axi_gpio_0.S_AXI/MON_AXI_WDATA[4]
SignalExport.dataChannel<0120>=axi_gpio_0.S_AXI/MON_AXI_WDATA[5]
SignalExport.dataChannel<0121>=axi_gpio_0.S_AXI/MON_AXI_WDATA[6]
SignalExport.dataChannel<0122>=axi_gpio_0.S_AXI/MON_AXI_WDATA[7]
SignalExport.dataChannel<0123>=axi_gpio_0.S_AXI/MON_AXI_WDATA[8]
SignalExport.dataChannel<0124>=axi_gpio_0.S_AXI/MON_AXI_WDATA[9]
SignalExport.dataChannel<0125>=axi_gpio_0.S_AXI/MON_AXI_WDATA[10]
SignalExport.dataChannel<0126>=axi_gpio_0.S_AXI/MON_AXI_WDATA[11]
SignalExport.dataChannel<0127>=axi_gpio_0.S_AXI/MON_AXI_WDATA[12]
SignalExport.dataChannel<0128>=axi_gpio_0.S_AXI/MON_AXI_WDATA[13]
SignalExport.dataChannel<0129>=axi_gpio_0.S_AXI/MON_AXI_WDATA[14]
SignalExport.dataChannel<0130>=axi_gpio_0.S_AXI/MON_AXI_WDATA[15]
SignalExport.dataChannel<0131>=axi_gpio_0.S_AXI/MON_AXI_WDATA[16]
SignalExport.dataChannel<0132>=axi_gpio_0.S_AXI/MON_AXI_WDATA[17]
SignalExport.dataChannel<0133>=axi_gpio_0.S_AXI/MON_AXI_WDATA[18]
SignalExport.dataChannel<0134>=axi_gpio_0.S_AXI/MON_AXI_WDATA[19]
SignalExport.dataChannel<0135>=axi_gpio_0.S_AXI/MON_AXI_WDATA[20]
SignalExport.dataChannel<0136>=axi_gpio_0.S_AXI/MON_AXI_WDATA[21]
SignalExport.dataChannel<0137>=axi_gpio_0.S_AXI/MON_AXI_WDATA[22]
SignalExport.dataChannel<0138>=axi_gpio_0.S_AXI/MON_AXI_WDATA[23]
SignalExport.dataChannel<0139>=axi_gpio_0.S_AXI/MON_AXI_WDATA[24]
SignalExport.dataChannel<0140>=axi_gpio_0.S_AXI/MON_AXI_WDATA[25]
SignalExport.dataChannel<0141>=axi_gpio_0.S_AXI/MON_AXI_WDATA[26]
SignalExport.dataChannel<0142>=axi_gpio_0.S_AXI/MON_AXI_WDATA[27]
SignalExport.dataChannel<0143>=axi_gpio_0.S_AXI/MON_AXI_WDATA[28]
SignalExport.dataChannel<0144>=axi_gpio_0.S_AXI/MON_AXI_WDATA[29]
SignalExport.dataChannel<0145>=axi_gpio_0.S_AXI/MON_AXI_WDATA[30]
SignalExport.dataChannel<0146>=axi_gpio_0.S_AXI/MON_AXI_WDATA[31]
SignalExport.dataChannel<0147>=axi_gpio_0.S_AXI/MON_AXI_WREADY
SignalExport.dataChannel<0148>=axi_gpio_0.S_AXI/MON_AXI_WSTRB[0]
SignalExport.dataChannel<0149>=axi_gpio_0.S_AXI/MON_AXI_WSTRB[1]
SignalExport.dataChannel<0150>=axi_gpio_0.S_AXI/MON_AXI_WSTRB[2]
SignalExport.dataChannel<0151>=axi_gpio_0.S_AXI/MON_AXI_WSTRB[3]
SignalExport.dataChannel<0152>=axi_gpio_0.S_AXI/MON_AXI_WVALID


