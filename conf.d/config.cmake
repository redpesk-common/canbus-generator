###########################################################################
# Copyright 2015, 2016, 2017 IoT.bzh
#
# author: Fulup Ar Foll <fulup@iot.bzh>
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

# Project Info
# ------------------
set(PROJECT_NAME can-config-generator)
set(PROJECT_VERSION "1.5")
set(PROJECT_PRETTY_NAME "CAN configuration generator")
set(PROJECT_DESCRIPTION "Generator that convert JSON file following OpenXC spec to configuration-generated.cpp file for the low level CAN binding.")
set(PROJECT_URL "https://gerrit.automotivelinux.org/gerrit/src/low-level-can-generator")
set(PROJECT_ICON "icon.png")
set(PROJECT_AUTHOR "Loïc Collignon")
set(PROJECT_AUTHOR_MAIL "loic.collignon@iot.bzh")
set(PROJECT_ICON "icon.png")
set(PROJECT_LICENCE "APL2.0")
set(PROJECT_LANGUAGES,"CXX")

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES ${PROJECT_LANGUAGES})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMP0048 1)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "RELEASE")
endif()

# Static constante definition
# -----------------------------
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-std=c++11>
		    -Wall
		    -Wextra
		    -Wconversion
		    -Wno-unused-parameter
		    -Wno-sign-compare
		    -Wno-sign-conversion
		    -Werror=implicit-function-declaration
		    -ffunction-sections
		    -fdata-sections
		    -fPIC
		    -Werror=maybe-uninitialized
		   )

if(${CMAKE_BUILD_TYPE} STREQUAL "RELEASE")
	add_compile_options(-O2 -D_FORTIFY_SOURCE=2)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
	add_compile_options(-g -ggdb -O0)
endif()

# (BUG!!!) as PKG_CONFIG_PATH does not work [should be an env variable]
# ---------------------------------------------------------------------
# set(CMAKE_INSTALL_PREFIX $ENV{HOME}/opt)
set(CMAKE_PREFIX_PATH ${CMAKE_INSTALL_PREFIX}/lib64/pkgconfig ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
set(LD_LIBRARY_PATH ${CMAKE_INSTALL_PREFIX}/lib64 ${CMAKE_INSTALL_PREFIX}/lib)
