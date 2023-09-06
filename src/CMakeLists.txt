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

# Define project Targets
add_executable(can-config-generator
	converter.cpp
	main.cpp
	openxc/message_set.cpp
	openxc/can_bus.cpp
	openxc/can_message.cpp
	openxc/command.cpp
	openxc/diagnostic_message.cpp
	openxc/mapping.cpp
	openxc/signal.cpp
	openxc/decoder.cpp
	)

target_include_directories(can-config-generator
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/json
)

# installation directory
install(TARGETS can-config-generator DESTINATION ${CMAKE_INSTALL_BINDIR})

