import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import Header
import cv2
import numpy as np
import termios, sys, tty


class CameraNode(Node):
    def __init__(self):
        super().__init__('camera_node')
        self.publisher = self.create_publisher(Image, 'camera_image', 10)
        self.subscription = self.create_subscription(Image, 'image_raw', self.image_callback, 10)
        self.subscription
    def capture_image(self):
        ret, frame = self.capture.read()
        if ret:
            img_msg = Image()
            img_msg.header = Header()
            img_msg.header.stamp = self.get_clock().now().to_msg()
            img_msg.header.frame_id = 'camera_frame'
            img_msg.height = frame.shape[0]
            img_msg.width = frame.shape[1]
            img_msg.encoding = 'bgr8'
            img_msg.is_bigendian = 0
            img_msg.step = len(frame.tobytes()) // frame.shape[0]
            img_msg.data = np.array(frame).tobytes()
            self.publisher.publish(img_msg)

    def image_callback(self, msg):
        self.publisher.publish(msg)
        print("Recieved")


def main(args=None):
    rclpy.init(args=args)
    camera_node = CameraNode()
    print("Press space for new picture, press o for out")
    rclpy.spin(camera_node)

    camera_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
