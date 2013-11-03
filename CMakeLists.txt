# CMake compatibility
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

# Project name
PROJECT( fractalexpr CXX )

# Project version

# Build configuration (DEBUG|RELEASE|RELWITHDEBINFO|MINSIZEREL)
SET(CMAKE_BUILD_TYPE Debug)

# Environment variables

# Project variables

SET(FRACTAL_SRC_DIR # Fractal Source Files
        "${PROJECT_SOURCE_DIR}/src")

SET(FRACTAL_TYPES_DIR   # Fractal Types
        "${FRACTAL_SRC_DIR}/types" )

SET(FRACTAL_UTILS_DIR   # Fractal Utils
        "${FRACTAL_SRC_DIR}/utils" )

SET(FRACTAL_TEST_DIR    # Fractal Tests 
        "${FRACTAL_SRC_DIR}/test" )


# Building shared libraries -- CPPUnit fails otherwise
OPTION( BUILD_SHARED_LIBS "Set to OFF to build static libraries" ON )

# Include 
INCLUDE_DIRECTORIES( "${FRACTAL_SRC_DIR}" )
# Flags
ADD_DEFINITIONS( "-Wall -W -Werror" )

# Adding module sub directories
ADD_SUBDIRECTORY( ${FRACTAL_TYPES_DIR} )
ADD_SUBDIRECTORY( ${FRACTAL_UTILS_DIR} )

# Main executable
#

ADD_EXECUTABLE(fractalgenerator "${FRACTAL_TEST_DIR}/fractalgeneratortest.cpp" )
TARGET_LINK_LIBRARIES(fractalgenerator
                fractaltypes
                fractalutils)


