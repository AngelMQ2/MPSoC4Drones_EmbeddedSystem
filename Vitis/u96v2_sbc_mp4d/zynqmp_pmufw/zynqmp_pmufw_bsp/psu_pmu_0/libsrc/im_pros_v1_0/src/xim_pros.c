// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xim_pros.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XIm_pros_CfgInitialize(XIm_pros *InstancePtr, XIm_pros_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Axi_cpu_BaseAddress = ConfigPtr->Axi_cpu_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

u32 XIm_pros_Get_imageIn_BaseAddress(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE);
}

u32 XIm_pros_Get_imageIn_HighAddress(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEIN_HIGH);
}

u32 XIm_pros_Get_imageIn_TotalBytes(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XIM_PROS_AXI_CPU_ADDR_IMAGEIN_HIGH - XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE + 1);
}

u32 XIm_pros_Get_imageIn_BitWidth(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIM_PROS_AXI_CPU_WIDTH_IMAGEIN;
}

u32 XIm_pros_Get_imageIn_Depth(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIM_PROS_AXI_CPU_DEPTH_IMAGEIN;
}

u32 XIm_pros_Write_imageIn_Words(XIm_pros *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XIM_PROS_AXI_CPU_ADDR_IMAGEIN_HIGH - XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XIm_pros_Read_imageIn_Words(XIm_pros *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XIM_PROS_AXI_CPU_ADDR_IMAGEIN_HIGH - XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE + (offset + i)*4);
    }
    return length;
}

u32 XIm_pros_Write_imageIn_Bytes(XIm_pros *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XIM_PROS_AXI_CPU_ADDR_IMAGEIN_HIGH - XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XIm_pros_Read_imageIn_Bytes(XIm_pros *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XIM_PROS_AXI_CPU_ADDR_IMAGEIN_HIGH - XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE + offset + i);
    }
    return length;
}

u32 XIm_pros_Get_imageOut_BaseAddress(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE);
}

u32 XIm_pros_Get_imageOut_HighAddress(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_HIGH);
}

u32 XIm_pros_Get_imageOut_TotalBytes(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_HIGH - XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE + 1);
}

u32 XIm_pros_Get_imageOut_BitWidth(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIM_PROS_AXI_CPU_WIDTH_IMAGEOUT;
}

u32 XIm_pros_Get_imageOut_Depth(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIM_PROS_AXI_CPU_DEPTH_IMAGEOUT;
}

u32 XIm_pros_Write_imageOut_Words(XIm_pros *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_HIGH - XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XIm_pros_Read_imageOut_Words(XIm_pros *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_HIGH - XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE + (offset + i)*4);
    }
    return length;
}

u32 XIm_pros_Write_imageOut_Bytes(XIm_pros *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_HIGH - XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XIm_pros_Read_imageOut_Bytes(XIm_pros *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_HIGH - XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axi_cpu_BaseAddress + XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE + offset + i);
    }
    return length;
}

