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

void XIm_pros_Start(XIm_pros *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIm_pros_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_AP_CTRL) & 0x80;
    XIm_pros_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_AP_CTRL, Data | 0x01);
}

u32 XIm_pros_IsDone(XIm_pros *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIm_pros_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XIm_pros_IsIdle(XIm_pros *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIm_pros_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XIm_pros_IsReady(XIm_pros *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIm_pros_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XIm_pros_EnableAutoRestart(XIm_pros *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIm_pros_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_AP_CTRL, 0x80);
}

void XIm_pros_DisableAutoRestart(XIm_pros *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIm_pros_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_AP_CTRL, 0);
}

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

void XIm_pros_InterruptGlobalEnable(XIm_pros *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIm_pros_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_GIE, 1);
}

void XIm_pros_InterruptGlobalDisable(XIm_pros *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIm_pros_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_GIE, 0);
}

void XIm_pros_InterruptEnable(XIm_pros *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XIm_pros_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_IER);
    XIm_pros_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_IER, Register | Mask);
}

void XIm_pros_InterruptDisable(XIm_pros *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XIm_pros_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_IER);
    XIm_pros_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_IER, Register & (~Mask));
}

void XIm_pros_InterruptClear(XIm_pros *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIm_pros_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_ISR, Mask);
}

u32 XIm_pros_InterruptGetEnabled(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIm_pros_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_IER);
}

u32 XIm_pros_InterruptGetStatus(XIm_pros *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIm_pros_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XIM_PROS_AXI_CPU_ADDR_ISR);
}

