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

#ifndef BASE_INTERFACE__BASE_INTERFACE_NODE_HPP_
#define BASE_INTERFACE__BASE_INTERFACE_NODE_HPP_

#include <base_interface/base_interface.hpp>
#include <rclcpp/rclcpp.hpp>

#include <string>

namespace autoware
{
namespace vehicle
{
namespace interface
{
class VescInterfaceNode : public BaseInterface
{
public:
  explicit VescInterfaceNode(const rclcpp::NodeOptions & options);
  
  
private:

};
}  // namespace interface
}  // namespace vehicle
}  // namespace autoware

#endif  // BASE_INTERFACE__BASE_INTERFACE_NODE_HPP_
