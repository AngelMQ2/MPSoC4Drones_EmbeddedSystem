// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// AXI_CPU
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

#define XIM_PROS_AXI_CPU_ADDR_IMAGEIN_BASE  0x4000
#define XIM_PROS_AXI_CPU_ADDR_IMAGEIN_HIGH  0x7fff
#define XIM_PROS_AXI_CPU_WIDTH_IMAGEIN      8
#define XIM_PROS_AXI_CPU_DEPTH_IMAGEIN      12288
#define XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_BASE 0x8000
#define XIM_PROS_AXI_CPU_ADDR_IMAGEOUT_HIGH 0xbfff
#define XIM_PROS_AXI_CPU_WIDTH_IMAGEOUT     8
#define XIM_PROS_AXI_CPU_DEPTH_IMAGEOUT     12288

