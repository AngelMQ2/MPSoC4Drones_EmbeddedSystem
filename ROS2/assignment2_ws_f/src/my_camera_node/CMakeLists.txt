cmake_minimum_required(VERSION 3.5)
project(my_camera_node)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package( OpenCV REQUIRED )
find_package(cv_bridge REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(include)
#add_library(xim_pros STATIC include/xim_pros.c)
add_library(xim_pros STATIC include/xim_pros.c)
add_library(xim_pros2 STATIC include/xim_pros_linux.c)
#target_link_libraries(listener xim_pros)  # Link "xim_pros" library directly

#set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/include/xim_pros.h)
 
add_executable(listener src/cpp_camera_node_subscriber.cpp)

target_link_libraries(listener xim_pros xim_pros2)  # Link "xim_pros" library directly
#target_link_libraries(listener PRIVATE /src/my_camera_node/include)
ament_target_dependencies(listener rclcpp std_msgs sensor_msgs OpenCV cv_bridge)

#add_library(xim_pros STATIC include/xim_pros.c)
#target_link_libraries(listener xim_pros)  # Link "xim_pros" library directly

# Add these lines to link your executable with the ROS 2 libraries


install(TARGETS
  listener
  DESTINATION lib/${PROJECT_NAME})
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
