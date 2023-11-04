#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <opencv2/opencv.hpp> 
#include "xim_pros.h"


class ImageSubscriber : public rclcpp::Node
{
public:
  ImageSubscriber() : Node("image_subscriber")
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
    cv::Mat image_data(msg->height, msg->width, CV_8UC3, const_cast<uint8_t*>(msg->data.data()));
    cv::Mat gray;
    cv::cvtColor(image_data, gray, cv::COLOR_BGR2GRAY);

    int IM_WIDTH = 128; // 480/5
    int IM_DEPTH = 96; // 640/5
    cv::Size down_points(IM_WIDTH, IM_DEPTH);
    cv::Mat resized_down;
    cv::resize(gray, resized_down, down_points, 0, 0, cv::INTER_LINEAR);

    cv::imwrite("escaled.jpg", resized_down);
    cv::imwrite("not_scaled.jpg", image_data);
    RCLCPP_INFO(get_logger(), "Image received");

    cv::Mat written_image = resized_down;

    // Hardware Image Processing IP call:
    XIm_pros ip_inst;
    XIm_pros_Config *ip_cfg;
    
    // Initialize the IP core
    prinf("Starting Image Processing IP Inicialization\n");

    int status = XIm_pros_Initialize(&ip_inst, im_pros);
    if (status != XST_SUCCESS) {
      printf("Error: Could not initialize the IP core.\n");
      //cleanup_platform();
      return XST_FAILURE;
    }


    // Perform operations with the IP core
    word_type imageIn[IM_WIDTH*IM_DEPTH];
    word_type imageOut[IM_WIDTH*IM_DEPTH];
    
    // Copy pre-processed flatten image to the IP variable
    imageIn =  std::vector<uint32_t>(written_image.data, written_image.data + written_image.total());

    // Write the image data to the IP core
    XIm_pros_Write_imageIn_Words(&ip_inst, 0, imageIn, IMAGE_SIZE);

    // Start the image processing function of the IP core
    XIm_pros_Start(&ip_inst);

    // Wait for the image processing to be completed
    while (!XIm_pros_IsDone(&ip_inst));

    // Read the processed image data from the IP core
    XIm_pros_Read_imageOut_Words(&ip_inst, 0, imageOut, IMAGE_SIZE);

    printf("********** Finish Image Processing **********");


    // Copy processed image data from the IP:
    cv::Mat processed_image = imageOut;

    // Convert the processed image to ROS Image message
    auto processed_msg = std::make_shared<sensor_msgs::msg::Image>();
    processed_msg->header = msg->header;
    processed_msg->height = processed_image.rows;
    processed_msg->width = processed_image.cols;
    processed_msg->encoding = "mono8";
    processed_msg->is_bigendian = false;
    processed_msg->step = processed_image.step;
    processed_msg->data = std::vector<uint8_t>(processed_image.data, processed_image.data + processed_image.total());

    // Publish the processed image
    publisher_->publish(*processed_msg);
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