############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project image_processor
set_top im_pros
add_files image_processor.cpp
add_files -tb Image_tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu3eg-sbva484-1-e}
create_clock -period 10 -name default
config_export -format ip_catalog -output /home/acerpc/OneDrive/SDU/EmbeddedSystems/MPSoC4Drones_EmbeddedSystem/im_pros.zip -rtl vhdl
source "./image_processor/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl vhdl -format ip_catalog -output /home/acerpc/OneDrive/SDU/EmbeddedSystems/MPSoC4Drones_EmbeddedSystem/im_pros.zip
