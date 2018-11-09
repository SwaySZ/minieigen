PROJECT(minieigen CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
set(Python_ADDITIONAL_VERSIONS 2.7)

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cMake")


EXECUTE_PROCESS(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
IF (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)
  MESSAGE(STATUS "GCC Version >= 4.8. Adding -ftrack-macro-expansion=0 and -save-temps")
  SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ftrack-macro-expansion=0 -save-temps")
ENDIF()

#===========================================================

IF ("${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1}" MATCHES ".*clang")
  SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ftemplate-depth-512")
ENDIF()

#===========================================================

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -fPIC")
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")#sway


ADD_DEFINITIONS("-DEIGEN_DONT_VECTORIZE -DEIGEN_DONT_ALIGN -DEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT")

#===========================================================


# Add possibility to use local boost installation (e.g. -DLocalBoost=1.46.1)
#set(CMAKE_MODULE_PATH "/scratch/softwares/boostinstall/lib/;${CMAKE_MODULE_PATH}")
set(Boost_NO_SYSTEM_PATHS TRUE)
#if (Boost_NO_SYSTEM_PATHS)
  #set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../3rdlib/boost167")
  set(BOOST_ROOT "/home/swayzhao/software/DEM/3rdlib/boost167")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
  #set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
  set(BOOST_LIBRARYDIR "/opt/SudoDEM/lib/3rdlibs/")
  #set(BOOST_LIBRARYDIR "$ORIGIN/../../../../../3rdlibs")

#endif (Boost_NO_SYSTEM_PATHS)
FIND_PACKAGE(Boost 1.67 COMPONENTS python27 system REQUIRED)

INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS})
#LINK_DIRECTORIES( ${BOOST_LIBRARYDIR} )
# for checking purpose
MESSAGE("--   Boost_VERSION: " ${Boost_VERSION})
MESSAGE("--   Boost_LIB_VERSION: " ${Boost_LIB_VERSION})
MESSAGE("--   BOOST_LIBRARYDIR: " ${BOOST_LIBRARYDIR})
MESSAGE("--   Boost_INCLUDE_DIRS: " ${Boost_INCLUDE_DIRS})
MESSAGE("--   Boost_LIBRARIES: " ${Boost_LIBRARIES})
#FIND_PACKAGE(Boost COMPONENTS system python REQUIRED)
FIND_PACKAGE(PythonInterp REQUIRED)
#FIND_PACKAGE(Eigen3 REQUIRED)

set(EIGEN3_INCLUDE_DIR "/home/swayzhao/software/DEM/3rdlib/eigen3.3.5")
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
MESSAGE(STATUS "Found Eigen3, at: ${EIGEN3_INCLUDE_DIR}")

IF(NOT LIBRARY_OUTPUT_PATH)   #For packaging
  SET (LIBRARY_OUTPUT_PATH "lib")
ENDIF(NOT LIBRARY_OUTPUT_PATH)   #For packaging

MESSAGE(STATUS "Library output path is: ${LIBRARY_OUTPUT_PATH}")

INCLUDE(FindPythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

ADD_SUBDIRECTORY("${CMAKE_SOURCE_DIR}/src")
