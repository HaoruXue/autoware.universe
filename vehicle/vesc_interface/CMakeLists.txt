cmake_minimum_required(VERSION 3.14)
project(vesc_interface)

find_package(autoware_cmake REQUIRED)
autoware_package()

set(INTERFACE_NODE base_interface_node)
ament_auto_add_library(${INTERFACE_NODE} SHARED
  include/base_interface/vesc_interface_node.hpp
  src/vesc_interface_node.cpp
)

if(BUILD_TESTING)
  set(INTERFACE_NODE_TEST test_base_interface_node)
  ament_add_ros_isolated_gtest(${INTERFACE_NODE_TEST}
    test/test_vesc_interface.cpp
  )
  ament_target_dependencies(${INTERFACE_NODE_TEST} fake_test_node)
  target_link_libraries(
    ${INTERFACE_NODE_TEST} ${INTERFACE_NODE})
endif()

ament_auto_package(
  INSTALL_TO_SHARE
  launch
  param
)
