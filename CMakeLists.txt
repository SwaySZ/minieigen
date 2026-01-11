PROJECT(minieigen CXX)
# Updated to 3.12 for modern FindPython3 support
CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

# 1. Find the active Python (3.10, 3.12, etc.)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# 2. Dynamically determine the Boost Python component name (e.g., python310 or python312)
string(REPLACE "." "" BOOST_PY_SUFFIX ${Python3_VERSION_MINOR})
set(BOOST_PY_COMPONENT "python3${BOOST_PY_SUFFIX}")

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cMake")

# GCC Specific optimization flags
EXECUTE_PROCESS(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
IF (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)
  SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ftrack-macro-expansion=0 -save-temps")
ENDIF()

# Clang Specific flags
IF ("${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1}" MATCHES ".*clang")
  SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ftemplate-depth-512")
ENDIF()

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -fPIC")
ADD_DEFINITIONS("-DEIGEN_DONT_VECTORIZE -DEIGEN_DONT_ALIGN -DEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT")

# RPATH Settings
SET(CMAKE_INSTALL_RPATH "$ORIGIN;")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

# 3. Configure Boost to use your shrunken/local installation
set(Boost_NO_SYSTEM_PATHS TRUE)
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../HeaderLib")
# It tells CMake where to look for boost_system-config.cmake and boost_python-config.cmake
list(APPEND CMAKE_PREFIX_PATH "${BOOST_ROOT}")
# Note: Modern FindBoost uses BOOST_ROOT to find includes and libs automatically

find_package(Boost REQUIRED COMPONENTS ${BOOST_PY_COMPONENT} system)

# 4. Set Eigen3 paths
set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Eigen-3.3.5")

# 5. Output configurations for debugging
MESSAGE(STATUS "Found Python: ${Python3_VERSION} (Suffix: ${BOOST_PY_SUFFIX})")
MESSAGE(STATUS "Using Boost Component: ${BOOST_PY_COMPONENT}")
MESSAGE(STATUS "Boost Include: ${Boost_INCLUDE_DIRS}")
MESSAGE(STATUS "Boost Libraries: ${Boost_LIBRARIES}")

# Include directories (Standard for non-target-based dependencies)
INCLUDE_DIRECTORIES(${Python3_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

IF(NOT LIBRARY_OUTPUT_PATH)
  SET (LIBRARY_OUTPUT_PATH "lib")
ENDIF()

ADD_SUBDIRECTORY("${CMAKE_SOURCE_DIR}/src")
