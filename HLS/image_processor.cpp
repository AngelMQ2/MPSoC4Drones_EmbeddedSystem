#include "ap_int.h"

#define IM_WIDTH 96
#define IM_DEPTH 128

//[IM_WIDTH][IM_DEPTH]

typedef ap_uint<8> pixel; // 8-bit pixel depth

void im_pros(pixel imageIn[IM_WIDTH][IM_DEPTH], pixel imageOut[IM_WIDTH][IM_DEPTH]){

//#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE s_axilite port=imageIn bundle=AXI_CPU
#pragma HLS INTERFACE s_axilite port=imageOut bundle=AXI_CPU

for (int i = 1; i < IM_WIDTH - 1; ++i) {
	for (int j = 1; j < IM_DEPTH - 1; ++j) {
		#pragma HLS pipeline II=1

		// Calculate the average of the center pixel and its 4 neighbors (top, bottom, left, right)
		imageOut[i][j] = (imageIn[i][j] + imageIn[i - 1][j] + imageIn[i + 1][j] + imageIn[i][j - 1] + imageIn[i][j + 1]) / 5;
	}
}
}
