##### CMake entry point

cmake_minimum_required (VERSION 2.6)

set(PROJ_NAME "mld_crf")
project (${PROJ_NAME} )

##### make release version
#set(CMAKE_BUILD_TYPE Release)

set(ignoreMe "${CMAKE_C_COMPILER} ${QT_QMAKE_EXECUTABLE}")

include(CheckIncludeFileCXX)
include(CheckCXXCompilerFlag)

# Enable C++11 standard
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS Off)       # Disable -std=gnu++11 and enable -std=c++11
    message(STATUS "==============================================================")
    message(STATUS "= Using c++ 11 features")
    message(STATUS "==============================================================")
else()
    message(FATAL_ERROR "This compiler does not support c++11")
endif()

# Always be pedantic about your code. Compilation warrnings should be treated as ERRORS!!!! Fix it...
#set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra -Wunused-parameter -Wformat-security -Wunreachable-code -fdata-sections -ffunction-sections -Wcast-align -Wunused-function -Wempty-body -Wpointer-arith -Wwrite-strings")
#set(CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wunused-parameter -Wformat-security -Wunreachable-code -fdata-sections -ffunction-sections -Wcast-align -Wunused-function -Wempty-body -Wpointer-arith -Wwrite-strings")

find_package(OpenCV) # 3.1.0

if(OpenCV_FOUND)
    include_directories( ${OpenCV_INCLUDE_DIRS} )
else(OpenCV_FOUND)
    message(STATUS "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
    if(APPLE)
        message(STATUS "brew install opencv")
        message(STATUS "brew link opencv")
    else(APPLE)
        message(STATUS "Follow https://help.ubuntu.com/community/OpenCV")
        message(FATAL_ERROR "You need to compile opencv >= v3.1.0 library first")
    endif(APPLE)
endif(OpenCV_FOUND)

find_package(cxxopts)

if (cxxopts_FOUND)
    message(STATUS "cxxopts - Found")
else(cxxopts_FOUND)
    message(STATUS "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
    message(STATUS "You need to install cxxopt")
    message(STATUS " git clone --depth 1 -b v2.0.0 https://github.com/jarro2783/cxxopts.git")
    message(STATUS " cd cxxopts; git checkout v2.0.0")
    message(STATUS " mkdir build; cd build")
    message(STATUS " cmake ..; make; sudo make install")
    message(STATUS "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
    message(FATAL_ERROR " You need to install cxxopts library")
endif(cxxopts_FOUND)

########################## NO CHANGES BEYOND THIS POINT ##########################


FILE(GLOB MLD_CRF_SRC_FILES "src/*.cpp"
                            "src/*.c"
                            "src/*.h")

# build demo program

add_executable(${PROJ_NAME} ${MLD_CRF_SRC_FILES})

# link cv to demo
target_link_libraries(${PROJ_NAME} ${OpenCV_LIBS})




  


