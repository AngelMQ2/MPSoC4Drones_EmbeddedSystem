#include "ap_int.h"

#define IM_WIDTH 96
#define IM_DEPTH 128

//[IM_WIDTH][IM_DEPTH]

typedef ap_uint<8> pixel; // 8-bit pixel depth

void im_pros(pixel imageIn[IM_WIDTH][IM_DEPTH], pixel imageOut[IM_WIDTH][IM_DEPTH]){

//#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=return bundle=AXI_CPU
#pragma HLS INTERFACE s_axilite port=imageIn bundle=AXI_CPU
#pragma HLS INTERFACE s_axilite port=imageOut bundle=AXI_CPU

for (int i = 0; i < IM_WIDTH - 1; ++i) {
	for (int j = 0; j < IM_DEPTH - 1; ++j) {
		#pragma HLS pipeline II=1
		if(i == 0 and j == 0){
			// Calculate the average of the center pixel and its 2 neighbors (bottom, right)
			imageOut[i][j] = (imageIn[i][j] + imageIn[i + 1][j] + imageIn[i][j + 1]) / 3;
		}
		else if(i == 0){
			// Calculate the average of the center pixel and its 3 neighbors (bottom, right, left)
			imageOut[i][j] = (imageIn[i][j] + imageIn[i + 1][j] + imageIn[i][j - 1] + imageIn[i][j + 1]) / 4;
		}
		else if(j == 0){
			// Calculate the average of the center pixel and its 3 neighbors (top, bottom, right)
			imageOut[i][j] = (imageIn[i][j] + imageIn[i - 1][j] + imageIn[i + 1][j] + imageIn[i][j + 1]) / 4;
		}
		else{
			// Calculate the average of the center pixel and its 4 neighbors (top, bottom, left, right)
			imageOut[i][j] = (imageIn[i][j] + imageIn[i - 1][j] + imageIn[i + 1][j] + imageIn[i][j - 1] + imageIn[i][j + 1]) / 5;
		}
	}
}
}
