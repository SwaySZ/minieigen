PROJECT(minieigen CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

# 1. Resolve CMP0167 (Modern Boost behavior for CMake 3.30+)
# Setting this to NEW tells CMake to use BoostConfig.cmake instead of the old FindBoost module.
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

# 2. Find the active Python
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# 3. Determine Boost Python component name
string(REPLACE "." "" BOOST_PY_SUFFIX ${Python3_VERSION_MINOR})
set(BOOST_PY_COMPONENT "python3${BOOST_PY_SUFFIX}")

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cMake")

# Compiler Optimization Flags
EXECUTE_PROCESS(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
IF (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)
  SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ftrack-macro-expansion=0 -save-temps")
ENDIF()

IF ("${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1}" MATCHES ".*clang")
  SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ftemplate-depth-512")
ENDIF()

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -fPIC")
ADD_DEFINITIONS("-DEIGEN_DONT_VECTORIZE -DEIGEN_DONT_ALIGN -DEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT")

# RPATH Settings
SET(CMAKE_INSTALL_RPATH "$ORIGIN;")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

# 4. Configure Modern Boost Search
# Use Boost_ROOT (case-sensitive) and CMAKE_PREFIX_PATH for Config mode.
set(Boost_NO_SYSTEM_PATHS TRUE)
set(Boost_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../HeaderLib")
list(APPEND CMAKE_PREFIX_PATH "${Boost_ROOT}")

# Force CONFIG mode to ensure it finds the boost_system-config.cmake files
find_package(Boost REQUIRED CONFIG COMPONENTS ${BOOST_PY_COMPONENT})

# 5. Set Eigen3 paths
set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Eigen-3.3.5")

# 6. Output configurations for debugging
MESSAGE(STATUS "Found Python: ${Python3_VERSION}")
MESSAGE(STATUS "Using Boost Component: ${BOOST_PY_COMPONENT}")
# Note: Modern Boost targets use names like Boost::python310 instead of variables
MESSAGE(STATUS "Boost Include: ${Boost_INCLUDE_DIRS}")

# 7. Include directories and build
INCLUDE_DIRECTORIES(${Python3_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

IF(NOT LIBRARY_OUTPUT_PATH)
  SET (LIBRARY_OUTPUT_PATH "lib")
ENDIF()

ADD_SUBDIRECTORY("${CMAKE_SOURCE_DIR}/src")
