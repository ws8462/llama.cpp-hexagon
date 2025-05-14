# Install script for directory: /home/kws/llama.cpp-hexagon/ggml

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/kws/android-sdk/ndk/26.3.11579264/toolchains/llvm/prebuilt/linux-x86_64/bin/llvm-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/kws/llama.cpp-hexagon/android/ggml/src/cmake_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/kws/llama.cpp-hexagon/android/ggml/src/libggml.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-cpu.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-alloc.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-backend.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-blas.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-cann.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-cpp.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-cuda.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-kompute.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-opt.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-metal.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-rpc.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-sycl.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/ggml-vulkan.h"
    "/home/kws/llama.cpp-hexagon/ggml/include/gguf.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/kws/llama.cpp-hexagon/android/ggml/src/libggml-base.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ggml" TYPE FILE FILES
    "/home/kws/llama.cpp-hexagon/android/ggml/ggml-config.cmake"
    "/home/kws/llama.cpp-hexagon/android/ggml/ggml-version.cmake"
    )
endif()

