# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

cmake_minimum_required (VERSION 3.14)

project (xberry LANGUAGES CXX)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/ThirdParty)

ExternalProject_Add(Timer
    GIT_REPOSITORY https://github.com/rafalfelczynski/timer
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

add_executable(xberry
  main.cpp
  ThreadPool.cpp
  Platform.cpp
  Sensor.cpp
  SensorController.cpp
  TemperatureSensor.cpp
  BloodPressureSensor.cpp
  HumiditySensor.cpp
)

include_directories(${EXTERNAL_INSTALL_LOCATION})
include_directories(${CMAKE_CURRENT_LIST_DIR})

add_dependencies(xberry Timer)
target_link_libraries(xberry ${EXTERNAL_INSTALL_LOCATION}/lib/Timer.lib)
