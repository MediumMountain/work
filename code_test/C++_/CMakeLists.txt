# CMakeLists.txt
#
# CMake export file for the Paho C++ library.
#
#*******************************************************************************
# This is part of the Paho MQTT C++ client library.
#
# Copyright (c) 2017-2023, Frank Pagliughi
#
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v2.0
# and Eclipse Distribution License v1.0 which accompany this distribution.
# 
# The Eclipse Public License is available at
#   http://www.eclipse.org/legal/epl-v20.html
# and the Eclipse Distribution License is available at
#   http://www.eclipse.org/org/documents/edl-v10.php.
#*******************************************************************************/

cmake_minimum_required(VERSION 3.5)

# プロジェクト名、バージョン
project(test CXX)

set(test_SRC
   examples/sync_publish.cpp
#  src/my_class.cpp
#  src/my_main.cpp
)

add_executable(main 
    ${test_SRC}
)

# target_link_libraries

target_include_directories(test PUBLIC include/mqtt
)