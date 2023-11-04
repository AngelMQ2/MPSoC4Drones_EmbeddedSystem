// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xim_pros.h"

extern XIm_pros_Config XIm_pros_ConfigTable[];

XIm_pros_Config *XIm_pros_LookupConfig(u16 DeviceId) {
	XIm_pros_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XIM_PROS_NUM_INSTANCES; Index++) {
		if (XIm_pros_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XIm_pros_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XIm_pros_Initialize(XIm_pros *InstancePtr, u16 DeviceId) {
	XIm_pros_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XIm_pros_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XIm_pros_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

