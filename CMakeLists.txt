###########################################################################
# Copyright 2015-2023 IoT.bzh
#
# Author: "IoT.bzh dev-team" <team@iot.bzh>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###########################################################################


CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

project(can-config-generator
        VERSION 2.0.0
        DESCRIPTION "Generator that convert JSON file following OpenXC spec to configuration-generated.cpp file for the low level CAN binding."
        HOMEPAGE_URL https://github.com/redpesk-common/canbus-generator
        LANGUAGES CXX)

include(GNUInstallDirs)
include(FindPkgConfig)

pkg_check_modules(canbus REQUIRED canbus-binding>=1.1)
include_directories("${canbus_INCLUDEDIR}")

add_subdirectory(src)

