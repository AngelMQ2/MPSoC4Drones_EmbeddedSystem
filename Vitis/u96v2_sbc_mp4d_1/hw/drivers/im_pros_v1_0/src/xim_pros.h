// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XIM_PROS_H
#define XIM_PROS_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xim_pros_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
    u32 Axi_cpu_BaseAddress;
} XIm_pros_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u64 Axi_cpu_BaseAddress;
    u32 IsReady;
} XIm_pros;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XIm_pros_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XIm_pros_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XIm_pros_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XIm_pros_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XIm_pros_Initialize(XIm_pros *InstancePtr, u16 DeviceId);
XIm_pros_Config* XIm_pros_LookupConfig(u16 DeviceId);
int XIm_pros_CfgInitialize(XIm_pros *InstancePtr, XIm_pros_Config *ConfigPtr);
#else
int XIm_pros_Initialize(XIm_pros *InstancePtr, const char* InstanceName);
int XIm_pros_Release(XIm_pros *InstancePtr);
#endif

void XIm_pros_Start(XIm_pros *InstancePtr);
u32 XIm_pros_IsDone(XIm_pros *InstancePtr);
u32 XIm_pros_IsIdle(XIm_pros *InstancePtr);
u32 XIm_pros_IsReady(XIm_pros *InstancePtr);
void XIm_pros_EnableAutoRestart(XIm_pros *InstancePtr);
void XIm_pros_DisableAutoRestart(XIm_pros *InstancePtr);

u32 XIm_pros_Get_imageIn_BaseAddress(XIm_pros *InstancePtr);
u32 XIm_pros_Get_imageIn_HighAddress(XIm_pros *InstancePtr);
u32 XIm_pros_Get_imageIn_TotalBytes(XIm_pros *InstancePtr);
u32 XIm_pros_Get_imageIn_BitWidth(XIm_pros *InstancePtr);
u32 XIm_pros_Get_imageIn_Depth(XIm_pros *InstancePtr);
u32 XIm_pros_Write_imageIn_Words(XIm_pros *InstancePtr, int offset, word_type *data, int length);
u32 XIm_pros_Read_imageIn_Words(XIm_pros *InstancePtr, int offset, word_type *data, int length);
u32 XIm_pros_Write_imageIn_Bytes(XIm_pros *InstancePtr, int offset, char *data, int length);
u32 XIm_pros_Read_imageIn_Bytes(XIm_pros *InstancePtr, int offset, char *data, int length);
u32 XIm_pros_Get_imageOut_BaseAddress(XIm_pros *InstancePtr);
u32 XIm_pros_Get_imageOut_HighAddress(XIm_pros *InstancePtr);
u32 XIm_pros_Get_imageOut_TotalBytes(XIm_pros *InstancePtr);
u32 XIm_pros_Get_imageOut_BitWidth(XIm_pros *InstancePtr);
u32 XIm_pros_Get_imageOut_Depth(XIm_pros *InstancePtr);
u32 XIm_pros_Write_imageOut_Words(XIm_pros *InstancePtr, int offset, word_type *data, int length);
u32 XIm_pros_Read_imageOut_Words(XIm_pros *InstancePtr, int offset, word_type *data, int length);
u32 XIm_pros_Write_imageOut_Bytes(XIm_pros *InstancePtr, int offset, char *data, int length);
u32 XIm_pros_Read_imageOut_Bytes(XIm_pros *InstancePtr, int offset, char *data, int length);

void XIm_pros_InterruptGlobalEnable(XIm_pros *InstancePtr);
void XIm_pros_InterruptGlobalDisable(XIm_pros *InstancePtr);
void XIm_pros_InterruptEnable(XIm_pros *InstancePtr, u32 Mask);
void XIm_pros_InterruptDisable(XIm_pros *InstancePtr, u32 Mask);
void XIm_pros_InterruptClear(XIm_pros *InstancePtr, u32 Mask);
u32 XIm_pros_InterruptGetEnabled(XIm_pros *InstancePtr);
u32 XIm_pros_InterruptGetStatus(XIm_pros *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
