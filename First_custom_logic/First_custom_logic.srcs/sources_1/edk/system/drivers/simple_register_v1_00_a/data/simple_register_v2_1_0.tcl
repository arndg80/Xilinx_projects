##############################################################################
## Filename:          /mnt/hgfs/Drive_E/Xilinx_projects/First_custom_logic/First_custom_logic.srcs/sources_1/edk/system/drivers/simple_register_v1_00_a/data/simple_register_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Mon Jul  8 21:44:50 2013 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "simple_register" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
