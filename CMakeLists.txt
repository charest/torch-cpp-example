#------------------------------------------------------------------------------#
# Set the minimum CMake version
#------------------------------------------------------------------------------#

cmake_minimum_required(VERSION 3.11)

#------------------------------------------------------------------------------#
# Setup the project
#------------------------------------------------------------------------------#

project(TorchTest VERSION 0.1.0)

# We need C++ 17
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

# cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
include(BuildType)

add_executable( torch_test main.cpp )

#------------------------------------------------------------------------------#
# Hip
#------------------------------------------------------------------------------#

set(HIP_PLATFORM "amd")
find_package(hip REQUIRED)
message(STATUS "**** HIP Configuration:")
message(STATUS "  VERSION: ${hip_VERSION}")
message(STATUS "  INCLUDE: ${hip_INCLUDE_DIRS}")
message(STATUS "  LIBRARIES: ${hip_LIBRARIES}")
message(STATUS "  GPU_TARGETS: ${GPU_TARGETS}")

find_package(hiprtc REQUIRED)
find_package(hipblas REQUIRED)
find_package(rocblas REQUIRED)
find_package(hipfft REQUIRED)
find_package(hiprand REQUIRED)
find_package(hipsparse REQUIRED)
find_package(hipsolver REQUIRED)
find_package(hipblaslt REQUIRED)
find_package(rocsolver REQUIRED)
find_package(miopen REQUIRED)

target_link_libraries(torch_test PRIVATE ${hip_LIBRARIES})

#------------------------------------------------------------------------------#
# Torch
#------------------------------------------------------------------------------#

find_package(Torch REQUIRED)
message(STATUS "**** LibTorch Configuration:")
message(STATUS "  VERSION: ${Torch_VERSION}")
message(STATUS "  INCLUDE: ${TORCH_INCLUDE_DIRS}")
message(STATUS "  LIBRARIES: ${TORCH_LIBRARIES}")

target_link_libraries(torch_test PRIVATE ${TORCH_LIBRARIES})

