# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_AXI_CPU {
imageIn { 
	dir I
	width 8
	depth 12288
	mode ap_memory
	offset 16384
	offset_end 32767
}
imageOut { 
	dir O
	width 8
	depth 12288
	mode ap_memory
	offset 32768
	offset_end 49151
}
}
dict set axilite_register_dict AXI_CPU $port_AXI_CPU


set port_control {
ap_start { }
ap_done { }
ap_ready { }
ap_idle { }
}
dict set axilite_register_dict control $port_control


