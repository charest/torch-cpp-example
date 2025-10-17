#------------------------------------------------------------------------------#
# Set the minimum CMake version
#------------------------------------------------------------------------------#

cmake_minimum_required(VERSION 3.11)

#------------------------------------------------------------------------------#
# Setup the project
#------------------------------------------------------------------------------#

project(TorchTest VERSION 0.1.0)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

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

#file(GLOB ROCM_DLLS "${ROCM_INSTALL_PREFIX}/lib/*.dll")
#MESSAGE(${ROCM_DLLS})

#MESSAGE(${PYTORCH_FOUND_HIP})

target_link_libraries(torch_test PRIVATE ${hip_LIBRARIES})

#------------------------------------------------------------------------------#
# Torch
#------------------------------------------------------------------------------#

find_package(Torch REQUIRED)
message(STATUS "**** LibTorch Configuration:")
message(STATUS "  VERSION: ${Torch_VERSION}")
message(STATUS "  INCLUDE: ${TORCH_INCLUDE_DIRS}")
message(STATUS "  LIBRARIES: ${TORCH_LIBRARIES}")

find_library(C10_HIP_LIBRARY c10_hip PATHS "${TORCH_INSTALL_PREFIX}/lib")
find_library(TORCH_HIP_LIBRARY torch_hip PATHS "${TORCH_INSTALL_PREFIX}/lib")
#target_link_libraries(torch_test PRIVATE "-Xlinker /WHOLEARCHIVE ${C10_HIP_LIBRARY}")
MESSAGE(${C10_HIP_LIBRARY})

file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
add_custom_command(TARGET torch_test
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${TORCH_DLLS}
                    $<TARGET_FILE_DIR:torch_test>)


MESSAGE(${TORCH_LIBRARIES})
#target_link_libraries(torch_test PRIVATE -WHOLEARCHIVE:${TORCH_HIP_LIBRARY} -WHOLEARCHIVE:${C10_HIP_LIBRARY} torch c10)
target_link_libraries(torch_test PRIVATE ${TORCH_LIBRARIES})
target_include_directories(torch_test PRIVATE ${TORCH_INCLUDE_DIRS})

