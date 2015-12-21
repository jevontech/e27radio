# Toolchain file for crosscompiling for Intel Edison on development PC (Ubuntu Linux 14.04)
# Required: SDK build using the bitbake toolchain

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

set(edison_sdk_root /opt/poky-edison/1.7.2)
set(cross_compiler_sysroot ${edison_sdk_root}/sysroots/x86_64-pokysdk-linux)
set(CMAKE_SYSROOT ${edison_sdk_root}/sysroots/core2-32-poky-linux)

# specify the cross compiler
set(CMAKE_C_COMPILER ${cross_compiler_sysroot}/usr/bin/i586-poky-linux/i586-poky-linux-gcc)
set(CMAKE_CXX_COMPILER ${cross_compiler_sysroot}/usr/bin/i586-poky-linux/i586-poky-linux-g++)

#set this variable so the qt5 tools such as qmake can be found
set( OE_QMAKE_PATH_EXTERNAL_HOST_BINS ${cross_compiler_sysroot}/usr/bin/qt5 )

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

SET(CMAKE_C_FLAGS "-Os -g3 -Wall --sysroot=${CMAKE_SYSROOT} -m32 -march=i586 -ffunction-sections -fdata-sections -fPIC"  CACHE STRING "" FORCE)
SET(CMAKE_CXX_FLAGS "-Os -g3 -Wall --sysroot=${CMAKE_SYSROOT} -m32 -march=i586 -ffunction-sections -fdata-sections -fPIC"  CACHE STRING "" FORCE)

INCLUDE_DIRECTORIES(${CMAKE_SYSROOT}/usr/include)
INCLUDE_DIRECTORIES(${CMAKE_SYSROOT}/usr/include/c++)
INCLUDE_DIRECTORIES(${CMAKE_SYSROOT}/usr/include/c++/i586-poky-linux)
INCLUDE_DIRECTORIES(${CMAKE_SYSROOT}/usr/include/qt5)
INCLUDE_DIRECTORIES(${CMAKE_SYSROOT}/usr/include/upm)

link_directories(${CMAKE_SYSROOT}/usr/lib)
