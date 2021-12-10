cmake_minimum_required(VERSION 3.12)
project(image_retrieval)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")

# Where to find CMake modules and OpenCV
# Windows
set(OpenCV_DIR "C:lib\\opencv\\mingw-build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
message(STATUS "opencv Include:${OpenCV_INCLUDE_DIRS}")
message(STATUS "opencv Library:${OpenCV_LIBRARIES}")


# Configure Project
file(GLOB SOURCES
        include/*.h
        lib/*.cpp
        )
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:/Users/15988/OneDrive/works/1201 - Image retrieval of wool fabric/image_retrieval/build/debug")
add_executable(app test/main.cpp ${SOURCES})
#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)
# linking
target_link_libraries(app ${OpenCV_LIBS})