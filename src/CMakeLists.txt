SET(DCSRC "double-conversion/bignum.cc;double-conversion/bignum-dtoa.cc;double-conversion/cached-powers.cc;double-conversion/diy-fp.cc;double-conversion/double-conversion.cc;double-conversion/fast-dtoa.cc;double-conversion/fixed-dtoa.cc;double-conversion/strtod.cc")

FILE(GLOB_RECURSE SRC_minieigen "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
ADD_LIBRARY(minieigen SHARED ${SRC_minieigen} ${DCSRC})
SET_TARGET_PROPERTIES(minieigen PROPERTIES OUTPUT_NAME minieigen PREFIX "" INSTALL_RPATH "$ORIGIN/../")
TARGET_LINK_LIBRARIES(minieigen ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

INSTALL(TARGETS minieigen LIBRARY DESTINATION ${LIBRARY_OUTPUT_PATH})
