#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xim_pros.h"

#define IMAGE_SIZE 1000 // Change this according to the image size

int main() {
    init_platform();
    print("Testing XIm_pros IP Core for Image Processing\n");

    XIm_pros ip_inst;
    XIm_pros_Config *ip_cfg;

    // Initialize the IP core
    ip_cfg = XIm_pros_LookupConfig(0); // Replace '0' with your desired Device ID
    if (ip_cfg == NULL) {
        printf("Error: Could not find the IP core configuration.\n");
        cleanup_platform();
        return XST_FAILURE;
    }

    int status = XIm_pros_CfgInitialize(&ip_inst, ip_cfg);
    if (status != XST_SUCCESS) {
        printf("Error: Could not initialize the IP core.\n");
        cleanup_platform();
        return XST_FAILURE;
    }

    // Perform operations with the IP core here

    // Test the IP core functionality for image processing
    word_type imageIn[IMAGE_SIZE];
    word_type imageOut[IMAGE_SIZE];

    // Initialize image input array
    for (int i = 0; i < IMAGE_SIZE; i++) {
        imageIn[i] = 1; // Initialize with some example data
    }

    // Write the image data to the IP core
    XIm_pros_Write_imageIn_Words(&ip_inst, 0, imageIn, IMAGE_SIZE);

    // Start the image processing function of the IP core
    XIm_pros_Start(&ip_inst);

    // Wait for the image processing to be completed
    while (!XIm_pros_IsDone(&ip_inst));

    // Read the processed image data from the IP core
    XIm_pros_Read_imageOut_Words(&ip_inst, 0, imageOut, IMAGE_SIZE);

    // Display the ImageOut:
    for (int i = 0; i < IMAGE_SIZE; i++){
    	printf("%d",imageOut[i]);
    }

    printf("Finish process");
    // Cleanup
    cleanup_platform();
    return XST_SUCCESS;
}
