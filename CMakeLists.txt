cmake_minimum_required(VERSION 3.0.2)
project(human_make_photo)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

###########################################
# Human_make_photo adding libraries START #
###########################################

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

FILE(GLOB_RECURSE SRC_FILES src/*.c*)
FILE(GLOB_RECURSE TEST_SRC_FILES test_src/*.c*)
FILE(GLOB_RECURSE HDR_FILES include/*.h*)

#add_library(dlib SHARED IMPORTED)
#set_property(TARGET dlib PROPERTY IMPORTED_LOCATION /home/humanoid/dlib/dlib/build/libdlib.so)

#FILE(GLOB_RECURSE DLIBHDR /home/humanoid/dlib/*.h*)
#message("sciezki = " ${DLIBHDR})

#set(ALL_INCLUDE_DIRS "")
#foreach (_headerFile ${DLIBHDR})
#    get_filename_component(_dir ${_headerFile} PATH)
#    list(APPEND ALL_INCLUDE_DIRS ${_dir})
#endforeach()
#list(REMOVE_DUPLICATES ALL_INCLUDE_DIRS)

###########################################
# Human_make_photo adding libraries END #
###########################################

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  roscpp
  roslib
  std_msgs
  zed_nodelets
  human_vision_exchange
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  CATKIN_DEPENDS cv_bridge roscpp roslib std_msgs zed_nodelets human_vision_exchange
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

############################
# List INCLUDE_DIRECTORIES # 
############################

#get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#foreach(dir ${dirs})
#  message(STATUS "dir='${dir}'")
#endforeach()

##################################
# Human_localization build START #
##################################

#add_executable(${PROJECT_NAME} ${HDR_FILES} ${SRC_FILES} ${ALL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${HDR_FILES} ${SRC_FILES} main_src/main.cpp)
#add_executable(${PROJECT_NAME}_tests ${HDR_FILES} ${SRC_FILES} ${TEST_SRC_FILES} )
add_definitions(-std=c++14)

target_link_libraries(${PROJECT_NAME}
                        ${OpenCV_LIBRARIES}
                        ${catkin_LIBRARIES})

#target_link_libraries(${PROJECT_NAME}_tests
#                        ${SPECIAL_OS_LIBS}
#                        ${ZED_LIBS}
#                        ${OPENGL_LIBRARIES}
#                        ${GLUT_LIBRARY}
#                        ${GLEW_LIBRARIES}
#                        ${OpenCV_LIBRARIES}
#                        ${catkin_LIBRARIES}
#                        dlib::dlib)
