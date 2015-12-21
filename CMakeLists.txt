cmake_minimum_required(VERSION 2.6)

PROJECT(E27-radio C CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5DBus REQUIRED)
include_directories(src/SMC)
set(exe_name E27radio)
file(GLOB cpp_files src/*.cpp)
file(GLOB h_files src/*.h)
set(extra_libraries -lmraa -lupm-i2clcd -lPocoFoundation -lPocoUtil -lQt5Core -lQt5DBus -lQt5Xml -lmpg123 -lao -lcurl )
#Compile and link
add_executable(${exe_name} ${cpp_files} ${h_files})
target_link_libraries(${exe_name} ${extra_libraries} )
