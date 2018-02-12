cmake_minimum_required(VERSION 2.8.3)

project(elir_stereo_camera)

set(APP_NAME elir_stereo_camera_node)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread -w")

set(MSGS_REQUIRED
  std_msgs
  message_generation
)

set(ELP_CATKIN_DEPENDS 
  roscpp 
  rospy  
  image_transport
  cv_bridge
)

file(GLOB_RECURSE ELP_HEADERS  "include/*.h*")
file(GLOB_RECURSE ELP_SOURCES  "src/*.c*")
file(GLOB_RECURSE ELP_MAIN     "src/main.cpp")

list(REMOVE_ITEM  ELP_SOURCES  "${ELP_MAIN}")
set(ELP_NODE_SOURCES ${ELP_MAIN} ${ELP_SOURCES} )

find_package(PkgConfig)

find_package(OpenCV 3 REQUIRED)
find_package(Threads  REQUIRED)
find_package(catkin  REQUIRED COMPONENTS  ${ELP_CATKIN_DEPENDS} ${MSGS_REQUIRED} cmake_modules)

catkin_package(
  INCLUDE_DIRS   ${INCLUDE_DIR}
  LIBRARIES      ${PROJECT_NAME} 
  CATKIN_DEPENDS ${DATHOMIR_CATKIN_DEPENDS} 
  DEPENDS        OpenCV Threads
)

include_directories(${CATKIN_DEVEL_PREFIX}/include)
include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}")

include_directories(
)

link_directories(
)

set(SHARED_LIBRARIES stdc++ )

add_executable(${APP_NAME} ${ELP_NODE_SOURCES} ${ELP_HEADERS})
target_link_libraries(${APP_NAME} ${catkin_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${SHARED_LIBRARIES} ${OpenCV_LIBS})
add_dependencies(${APP_NAME} ${catkin_EXPORTED_TARGETS})