# Copyright © 2016 Lénaïc Bagnères, hnc@singularity.fr

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


cmake_minimum_required(VERSION 2.6)


# General C++ flags
	
	# General
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -Wlogical-op -Wdouble-promotion -std=c++14 -pedantic")# -Wfatal-errors")
	
	# Release
	if (CMAKE_BUILD_TYPE STREQUAL "")
		set(CMAKE_BUILD_TYPE "Debug")
	endif()
	
	# Release flags
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -march=native -ffast-math")
	
	# Debug flags
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")



# Project
	message(STATUS "---")
	set(project_INCLUDE "./include")
	include_directories("${project_INCLUDE}")
	message(STATUS "Include project = ${project_INCLUDE}")


# Sources
	
	file(GLOB_RECURSE project_sources src/*.cpp)

# Executables
	
	message(STATUS "---")
	add_executable(exe "${project_sources}")




