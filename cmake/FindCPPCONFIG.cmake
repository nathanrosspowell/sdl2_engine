# FindCPPCONFIG - attempts to locate the cppconfig matrix/vector library.
#
# This module defines the following variables (on success):
#   CPPCONFIG_INCLUDE_DIRS  - where to find cppconfig/cppconfig.hpp
#   CPPCONFIG_FOUND         - if the library was successfully located
#
# It is trying a few standard installation locations, but can be customized
# with the following variables:
#   CPPCONFIG_ROOT_DIR      - root directory of a cppconfig installation
#                       Headers are expected to be found in either:
#                       <CPPCONFIG_ROOT_DIR>/cppconfig/cppconfig.hpp           OR
#                       <CPPCONFIG_ROOT_DIR>/include/cppconfig/cppconfig.hpp
#                       This variable can either be a cmake or environment
#                       variable. Note however that changing the value
#                       of the environment varible will NOT result in
#                       re-running the header search and therefore NOT
#                       adjust the variables set by this module.

#=============================================================================
# Copyright 2012 Carsten Neumann
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

# default search dirs
SET(_cppconfig_HEADER_SEARCH_DIRS
    "/usr/include"
    "/usr/local/include"
    "/usr/include/i386-linux-gnu/c++/4.8/")

# check environment variable
SET(_cppconfig_ENV_ROOT_DIR "$ENV{CPPCONFIG_ROOT_DIR}")

IF(NOT CPPCONFIG_ROOT_DIR AND _cppconfig_ENV_ROOT_DIR)
    SET(CPPCONFIG_ROOT_DIR "${_cppconfig_ENV_ROOT_DIR}")
ENDIF(NOT CPPCONFIG_ROOT_DIR AND _cppconfig_ENV_ROOT_DIR)

# put user specified location at beginning of search
IF(CPPCONFIG_ROOT_DIR)
    SET(_cppconfig_HEADER_SEARCH_DIRS "${CPPCONFIG_ROOT_DIR}"
                                "${CPPCONFIG_ROOT_DIR}/include"
                                 ${_cppconfig_HEADER_SEARCH_DIRS})
ENDIF(CPPCONFIG_ROOT_DIR)

# locate header
FIND_PATH(CPPCONFIG_INCLUDE_DIR "bits/c++config.h"
    PATHS ${_cppconfig_HEADER_SEARCH_DIRS})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CPPCONFIG DEFAULT_MSG
    CPPCONFIG_INCLUDE_DIR)

IF(CPPCONFIG_FOUND)
    SET(CPPCONFIG_INCLUDE_DIRS "${CPPCONFIG_INCLUDE_DIR}")

    MESSAGE(STATUS "CPPCONFIG_INCLUDE_DIR = ${CPPCONFIG_INCLUDE_DIR}")
ENDIF(CPPCONFIG_FOUND)
