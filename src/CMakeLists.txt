# 1. Define source files
SET(DCSRC 
    "double-conversion/bignum.cc"
    "double-conversion/bignum-dtoa.cc"
    "double-conversion/cached-powers.cc"
    "double-conversion/diy-fp.cc"
    "double-conversion/double-conversion.cc"
    "double-conversion/fast-dtoa.cc"
    "double-conversion/fixed-dtoa.cc"
    "double-conversion/strtod.cc"
)

# Use GLOB carefully; it is better to list files explicitly, but keeping your logic:
FILE(GLOB_RECURSE SRC_minieigen "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 2. Create the library
# Note: For Python modules, 'MODULE' is often preferred over 'SHARED' 
# to prevent other C++ projects from linking against it.
ADD_LIBRARY(minieigen SHARED ${SRC_minieigen} ${DCSRC})

# 3. Modern target properties
SET_TARGET_PROPERTIES(minieigen PROPERTIES 
    OUTPUT_NAME minieigen 
    PREFIX "" 
    # Use $ORIGIN to allow the module to find shrunken Boost libs in ../lib/
    INSTALL_RPATH "$ORIGIN/../"
)

# 4. Modern Linking (Uses the variables from your top-level CMakeLists)
# This handles python310 or python312 based on what was found.
TARGET_LINK_LIBRARIES(minieigen PRIVATE 
    Boost::${BOOST_PY_COMPONENT} 
    Boost::system
    Python3::Python
)

# 5. Install to the directory defined in the top-level script
INSTALL(TARGETS minieigen DESTINATION ${LIBRARY_OUTPUT_PATH})
