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

# Explicitly list source files for predictability (preferred over GLOB)
FILE(GLOB_RECURSE SRC_minieigen "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 2. Create the library
# Python modules should typically be 'MODULE' (loadable at runtime)
ADD_LIBRARY(minieigen MODULE ${SRC_minieigen} ${DCSRC})

# 3. Target properties
SET_TARGET_PROPERTIES(minieigen PROPERTIES 
    OUTPUT_NAME minieigen 
    PREFIX "" 
    # Ensure the suffix matches what Python expects (e.g., .so or .pyd)
    SUFFIX "${Python3_SOSUFFIX}"
    # Use $ORIGIN to allow the module to find shrunken Boost libs in ../lib/
    INSTALL_RPATH "$ORIGIN/../"
)

# 4. Modern Target Linking
# In Boost Config mode, targets are typically named Boost::<component>
# Boost::headers (or Boost::boost) provides the necessary include paths automatically.
TARGET_LINK_LIBRARIES(minieigen PRIVATE 
    Boost::${BOOST_PY_COMPONENT} 
    Boost::system
    Boost::headers
    Python3::Python
)

# 5. Target Include Directories
# target_link_libraries handles most includes, but we add Eigen and local dirs here.
TARGET_INCLUDE_DIRECTORIES(minieigen PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${EIGEN3_INCLUDE_DIR}"
)

# 6. Install to the directory defined in the top-level script
INSTALL(TARGETS minieigen DESTINATION ${LIBRARY_OUTPUT_PATH})
