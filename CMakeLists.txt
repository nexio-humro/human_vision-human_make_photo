cmake_minimum_required(VERSION 3.0.2)
project(human_make_photo)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

###########################################
# Human_make_photo adding libraries START #
###########################################

option(LINK_SHARED_ZED "Link with the ZED SDK shared executable" ON)

if(COMMAND cmake_policy)
        cmake_policy(SET CMP0003 OLD)
        cmake_policy(SET CMP0004 OLD)
        cmake_policy(SET CMP0015 OLD)
endif(COMMAND cmake_policy)

find_package(ZED 3 REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)

IF(NOT WIN32)
    SET(SPECIAL_OS_LIBS "pthread" "X11")
    add_definitions(-Wno-write-strings)
ENDIF()

include_directories(${ZED_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIR})
include_directories(${CUDA_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# write correct path to dlib library
add_subdirectory(/home/kamil/Dlib/dlib/dlib dlib_build)

link_directories(${ZED_LIBRARY_DIR})
link_directories(${GLEW_LIBRARY_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
link_directories(${CUDA_LIBRARY_DIRS})

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

if (LINK_SHARED_ZED)
    SET(ZED_LIBS ${ZED_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_CUDART_LIBRARY} ${CUDA_DEP_LIBRARIES_ZED})
else()
    SET(ZED_LIBS ${ZED_STATIC_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_LIBRARY})
endif()

target_link_libraries(${PROJECT_NAME}
                        ${SPECIAL_OS_LIBS}
                        ${ZED_LIBS}
                        ${OPENGL_LIBRARIES}
                        ${GLUT_LIBRARY}
                        ${GLEW_LIBRARIES}
                        ${OpenCV_LIBRARIES}
                        ${catkin_LIBRARIES}
                        dlib::dlib)
                        #dlib)

#target_link_libraries(${PROJECT_NAME}_tests
#                        ${SPECIAL_OS_LIBS}
#                        ${ZED_LIBS}
#                        ${OPENGL_LIBRARIES}
#                        ${GLUT_LIBRARY}
#                        ${GLEW_LIBRARIES}
#                        ${OpenCV_LIBRARIES}
#                        ${catkin_LIBRARIES}
#                        dlib::dlib)
