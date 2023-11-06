// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// AXI_CPU
// 0x0000 : Control signals
//          bit 0  - ap_start (Read/Write/COH)
//          bit 1  - ap_done (Read/COR)
//          bit 2  - ap_idle (Read)
//          bit 3  - ap_ready (Read)
//          bit 7  - auto_restart (Read/Write)
//          others - reserved
// 0x0004 : Global Interrupt Enable Register
//          bit 0  - Global Interrupt Enable (Read/Write)
//          others - reserved
// 0x0008 : IP Interrupt Enable Register (Read/Write)
//          bit 0  - enable ap_done interrupt (Read/Write)
//          bit 1  - enable ap_ready interrupt (Read/Write)
//          others - reserved
// 0x000c : IP Interrupt Status Register (Read/TOW)
//          bit 0  - ap_done (COR/TOW)
//          bit 1  - ap_ready (COR/TOW)
//          others - reserved
// 0x4000 ~
// 0x7fff : Memory 'imageIn' (12288 * 8b)
//          Word n : bit [ 7: 0] - imageIn[4n]
//                   bit [15: 8] - imageIn[4n+1]
//                   bit [23:16] - imageIn[4n+2]
//                   bit [31:24] - imageIn[4n+3]
// 0x8000 ~
// 0xbfff : Memory 'imageOut' (12288 * 8b)
//          Word n : bit [ 7: 0] - imageOut[4n]
//                   bit [15: 8] - imageOut[4n+1]
//                   bit [23:16] - imageOut[4n+2]
//                   bit [31:24] - imageOut[4n+3]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XIM_PROS_AXI_CPU_ADDR_AP_CTRL       0x0000
#define XIM_PROS_AXI_CPU_ADDR_GIE           0x0004
#define XIM_PROS_AXI_CPU_ADDR_IER           0x0008
#define XIM_PROS_AXI_CPU_ADDR_ISR           0x000c
#define XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE  0x4000
#define XIM_PROS_AXI_CPU_ADDR_IMAGEIN_HIGH  0x7fff
#define XIM_PROS_AXI_CPU_WIDTH_IMAGEIN      8
#define XIM_PROS_AXI_CPU_DEPTH_IMAGEIN      12288
#define XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE 0x8000
#define XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_HIGH 0xbfff
#define XIM_PROS_AXI_CPU_WIDTH_IMAGEOUT     8
#define XIM_PROS_AXI_CPU_DEPTH_IMAGEOUT     12288

