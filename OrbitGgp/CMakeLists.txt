# Copyright (c) 2020 The Orbit Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

project(OrbitGgp CXX)

add_library(OrbitGgp)

target_compile_options(OrbitGgp PRIVATE ${STRICT_COMPILE_FLAGS})

target_compile_features(OrbitBase PUBLIC cxx_std_17)

target_include_directories(OrbitGgp PUBLIC
          ${CMAKE_CURRENT_LIST_DIR}/include)

target_sources(OrbitGgp PUBLIC
          include/OrbitGgp/GgpClient.h
          include/OrbitGgp/GgpInstance.h
          include/OrbitGgp/GgpInstanceItemModel.h
          include/OrbitGgp/GgpSshInfo.h)

target_sources(OrbitGgp PRIVATE
          GgpClient.cpp
          GgpInstance.cpp
          GgpInstanceItemModel.cpp
          GgpSshInfo.cpp)

target_link_libraries(
  OrbitGgp
  PRIVATE OrbitBase
          Qt5::Core
)

set_target_properties(OrbitGgp PROPERTIES AUTOMOC ON)
set_target_properties(OrbitGgp PROPERTIES AUTOUIC ON)

# Tests
add_executable(OrbitGgpTests)

target_sources(OrbitGgpTests PRIVATE 
          GgpInstanceTests.cpp
          GgpInstanceItemModelTests.cpp
          GgpSshInfoTests.cpp
)

target_link_libraries(OrbitGgpTests PRIVATE 
          OrbitGgp
          OrbitBase
          GTest::Main
          Qt5::Core
)

set_target_properties(OrbitGgpTests PROPERTIES AUTOMOC ON)
set_target_properties(OrbitGgpTests PROPERTIES AUTOUIC ON)

register_test(OrbitGgpTests)
