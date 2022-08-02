// Copyright 2022 The Autoware Foundation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <functional>
#include <string>

#include "vehicle_interface/vehicle_interface_node.hpp"
namespace autoware
{
namespace vehicle
{
namespace interface
{
using FeatureSet = BaseInterface::FeatureSet;

VehicleInterfaceNode::VehicleInterfaceNode(
  const std::string & node_name,
  const FeatureSet & features,
  const rclcpp::NodeOptions & options)
: rclcpp::Node(node_name, options)
{
  using std::placeholders::_1;
  using std::placeholders::_2;
  // Declare required sub and service
  m_command_sub = create_subscription<AckermannControlCommand>(
    "controller/output/control_cmd", 1, std::bind(
      &VehicleInterfaceNode::on_command, this,
      _1));
  m_mode_service = create_service<autoware_auto_vehicle_msgs::srv::AutonomyModeChange>(
    "autonomy_mode", std::bind(&VehicleInterfaceNode::on_mode_change_request, _1, _2));

  // Declare optional pubs and subs
  for (const auto & feat : features) {
    switch (feat) {
      case InterfaceFeature::GEAR:
        m_gear_pub = create_publisher<GearReport>("gear_report", 1);
        m_gear_sub =
          create_subscription<GearCommand>(
          "gear_cmd", 1, [this](GearCommand::SharedPtr msg) {
            send_gear_command(*msg);
          });
        break;
      case InterfaceFeature::HAND_BRAKE:
        m_hand_brake_pub = create_publisher<HandBrakeReport>("hand_brake_report", 1);
        m_hand_brake_sub =
          create_subscription<HandBrakeCommand>(
          "hand_brake_cmd", 1, [this](HandBrakeCommand::SharedPtr msg) {
            send_hand_brake_command(*msg);
          });
        break;
      case InterfaceFeature::HAZARD_LIGHTS:
        m_hazard_lights_pub = create_publisher<HazardLightsReport>("hazard_lights_report", 1);
        m_hazard_lights_sub =
          create_subscription<HazardLightsCommand>(
          "hazard_lights_cmd", 1, [this](HazardLightsCommand::SharedPtr msg) {
            send_hazard_lights_command(*msg);
          });
        break;
      case InterfaceFeature::HEADLIGHTS:
        m_headlights_pub = create_publisher<HeadlightsReport>("headlights_report", 1);
        m_headlights_sub =
          create_subscription<HeadlightsCommand>(
          "headlights_cmd", 1, [this](HeadlightsCommand::SharedPtr msg) {
            send_headlights_command(*msg);
          });
        break;
      case InterfaceFeature::HORN:
        m_horn_pub = create_publisher<HornReport>("horn_report", 1);
        m_horn_sub =
          create_subscription<HornCommand>(
          "horm_cmd", 1, [this](HornCommand::SharedPtr msg) {
            send_horn_command(*msg);
          });
        break;
      case InterfaceFeature::WIPERS:
        m_wipers_pub = create_publisher<WipersReport>("wipers_report", 1);
        m_wipers_sub =
          create_subscription<WipersCommand>(
          "wipers_cmd", 1, [this](WipersCommand::SharedPtr msg) {
            send_wipers_command(*msg);
          });
        break;
      case InterfaceFeature::TURN_INDICATORS:
        m_turn_indicators_pub = create_publisher<TurnIndicatorsReport>("turn_indicators_report", 1);
        m_turn_indicators_sub =
          create_subscription<TurnIndicatorsCommand>(
          "turn_indicator_cmd", 1, [this](TurnIndicatorsCommand::SharedPtr msg) {
            send_turn_indicators_command(*msg);
          });
        break;
      case InterfaceFeature::ODOMETRY:
        m_odometry_pub = create_publisher<VehicleOdometry>("odom", 1);
        break;
      default:
        throw std::runtime_error("Unknow vehicle interface feature.");
    }
  }
}

void VehicleInterfaceNode::on_command(AckermannControlCommand::SharedPtr msg)
{
  send_control_command(*msg);
  // TODO(haoru): handle send_control_command failures
}

void VehicleInterfaceNode::on_mode_change_request(
  ModeChangeRequest::SharedPtr request,
  ModeChangeResponse::SharedPtr response)
{
  handle_mode_change_request(request);
  // TODO(haoru): handle mode change failures
}
}  // namespace interface
}  // namespace vehicle
}  // namespace autoware
