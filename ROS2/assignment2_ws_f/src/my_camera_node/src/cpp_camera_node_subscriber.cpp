#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <opencv2/opencv.hpp> 
#include "../include/xim_pros.h"
#include <cv_bridge/cv_bridge.h>


class ImageSubscriber : public rclcpp::Node
{
public:
  ImageSubscriber() : Node("image_processing")
  {
    subscription_ = create_subscription<sensor_msgs::msg::Image>(
      "camera_image",
      10,
      [this](const sensor_msgs::msg::Image::SharedPtr msg) -> void {
        image_callback(msg);
      });

    publisher_ = create_publisher<sensor_msgs::msg::Image>("/processed_image", 10);
  }

private:
  void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
  { 
    // cv::Mat image_data(msg->height, msg->width, CV_8UC3, const_cast<uint8_t*>(msg->data.data()));

    
    // Convert ROS Image message to OpenCV Mat using cv_bridge
    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception& e) {

    }

    // Extract the OpenCV Mat image
    cv::Mat cv_image = cv_ptr->image;

    cv::Mat gray;

    cv::imwrite("raw.jpg", cv_image);
    
    cv::cvtColor(cv_image, gray, cv::COLOR_BGR2GRAY);

    int IM_WIDTH = 128; // 480/5
    int IM_DEPTH = 96; // 640/5
    cv::Size down_points(IM_WIDTH, IM_DEPTH);
    cv::Mat resized_down;
    cv::resize(gray, resized_down, down_points, 0, 0, cv::INTER_LINEAR);

    cv::imwrite("escaled.jpg", resized_down);
    cv::imwrite("not_scaled.jpg", cv_image);
    RCLCPP_INFO(get_logger(), "Image received");

    cv::Mat written_image = resized_down;cv::imwrite("escaled.jpg", resized_down);

    // Hardware Image Processing IP call:
    XIm_pros ip_inst;
    //XIm_pros_Config *ip_cfg;
    
    // Initialize the IP core
    printf("Starting Image Processing IP Inicialization\n");

    int status = XIm_pros_Initialize(&ip_inst,"im_pros");
    if (status != XST_SUCCESS) {
      printf("Error: Could not initialize the IP core.\n");
      //cleanup_platform();
      //return XST_OPEN_DEVICE_FAILED;
    }
printf("Inicialization finished\n");
    XIm_pros_InterruptEnable(&ip_inst,1);
    XIm_pros_DisableAutoRestart(&ip_inst);
    XIm_pros_InterruptGlobalEnable(&ip_inst);
    

    // Perform operations with the IP core
    word_type* imageIn = new word_type[IM_WIDTH * IM_DEPTH];
    word_type* imageOut = new word_type[IM_WIDTH * IM_DEPTH];
printf("Variables defined\n");
    for (int i = 0; i < IM_WIDTH * IM_DEPTH; ++i) {
      imageIn[i] = static_cast<word_type>(written_image.data[i]);
    }
printf("Input Image adquired\n");
    // Copy pre-processed flatten image to the IP variable
    //imageIn =  std::vector<uint32_t>(written_image.data, written_image.data + written_image.total());
printf("Ini wrting Input Image on BRAM\n");
    // Write the image data to the IP core
    XIm_pros_Write_imageIn_Words(&ip_inst, 0, imageIn, IM_WIDTH*IM_DEPTH);
printf("Finish writing Input image on BRAM and starting IP proces\n");
    // Start the image processing function of the IP core
    XIm_pros_Start(&ip_inst);
printf("Executing Image processin, waiting to finish\n");
    // Wait for the image processing to be completed
    while (!XIm_pros_IsDone(&ip_inst));
printf("Finish processing, reading from BRAM\n");
    // Read the processed image data from the IP core
    XIm_pros_Read_imageOut_Words(&ip_inst, 0, imageOut, IM_WIDTH*IM_DEPTH);

    printf("********** Finish Image Processing **********");


    // Copy processed image data from the IP:
    //cv::Mat processed_image = imageOut;
    cv::Mat processed_image(IM_DEPTH, IM_WIDTH, CV_8UC1);
    for (int i = 0; i < IM_DEPTH; i++) {
        for (int j = 0; j < IM_WIDTH; j++) {
            processed_image.at<uint8_t>(i, j) = static_cast<uint8_t>(imageOut[i * IM_WIDTH + j]);
        }
    }


    cv::imwrite("final_save.jpg", processed_image);
    // Convert the processed image to ROS Image message
    auto processed_msg = std::make_shared<sensor_msgs::msg::Image>();
    processed_msg->header = msg->header;
    processed_msg->height = processed_image.rows;
    processed_msg->width = processed_image.cols;
    processed_msg->encoding = "mono8";
    processed_msg->is_bigendian = false;
    processed_msg->step = IM_WIDTH;
    // Create a byte vector from processed_image data
    processed_msg->data = std::vector<uint8_t>(processed_image.data, processed_image.data + processed_image.total());
    //processed_msg->data = std::vector<uint8_t>(processed_image.data, processed_image.data + processed_image.total());

    // Publish the processed image
    publisher_->publish(*processed_msg);

    // Don't forget to delete the dynamically allocated memory when done
    delete[] imageIn;
    delete[] imageOut;
  }

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
};

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ImageSubscriber>());
  rclcpp::shutdown();
  return 0;
}
