#include <iostream>
#include "ap_int.h"
#include <random>

#define IM_WIDTH 96
#define IM_DEPTH 128
//

void im_pros(ap_uint<8> imageIn[IM_WIDTH][IM_DEPTH], ap_uint<8> imageOut[IM_WIDTH][IM_DEPTH]);

// Function to generate random positive numbers
unsigned int generateRandomPositiveNumber() {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator

    // Define the range of positive numbers you want to generate
    std::uniform_int_distribution<unsigned int> distrib(1, std::numeric_limits<unsigned int>::max());

    return distrib(gen);  // Generate a random positive number
}

int main() {
	ap_uint<8> inputImage[IM_WIDTH][IM_DEPTH];
    ap_uint<8> outputImage[IM_WIDTH][IM_DEPTH];

    // Initialize input image with some sample data
    for (int i = 0; i < IM_WIDTH; ++i) {
        for (int j = 0; j < IM_DEPTH; ++j) {
            //inputImage[i][j] = static_cast<char>(generateRandomPositiveNumber());  // Example: Filling image with simple data
        	if (j%3==0) {
        		inputImage[i][j] = 1;
        	}
        	else if(i%2==0){
        		inputImage[i][j] = 5;
        	}
        	else{
        		inputImage[i][j] = 0;
        	}
        }
    }

    // Display a few pixels from the output image for verification
   std::cout << "Input Image (few pixels):" << std::endl;
   for (int i = 0; i < 10; ++i) {
	   for (int j = 0; j < 10; ++j) {
		   std::cout << static_cast<int>(inputImage[i][j]) << " ";
	   }
	   std::cout << std::endl;
   }

    // Call the image processing function
    im_pros(inputImage, outputImage);

    // Display a few pixels from the output image for verification
    std::cout << "Output Image (few pixels):" << std::endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << static_cast<int>(outputImage[i][j]) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
