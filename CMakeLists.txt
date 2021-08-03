# $Id: CMakeLists.txt 86065 2014-11-07 08:51:15Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.10 FATAL_ERROR)
project(Plume)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

#---------------------------------------------------------------------------
# Find Pythia8
#
# set(PYTHIA8_FOUND 0)

# set(_pythia8dirs
#     ${PYTHIA8}
#     $ENV{PYTHIA8}
#     ${PYTHIA8_DIR}
#     $ENV{PYTHIA8_DIR}
#     /usr
#     /opt/pythia8)

# find_path(PYTHIA8_INCLUDE_DIR Pythia.h
#     ${PYTHIA8_DIR}/include
#     /opt/pythia8/include
#     /usr/local/include
#     /usr/include
#     /usr/include/pythia
#     DOC "Specify the directory containing Pythia.h."
#     )

# find_library(PYTHIA8_LIBRARY NAMES Pythia8 pythia8 PATHS
#     $ENV{PYTHIA8_DIR}/lib
#     /opt/pythia8/lib
#     /usr/local/lib
#     /usr/lib
#     DOC "Specify the Pythia8 library here."
#     )

# if(PYTHIA8_INCLUDE_DIR AND PYTHIA8_LIBRARY)
#     set(PYTHIA8_FOUND 1 )
#     message(STATUS "Found Pythia8 library at ${PYTHIA8_LIBRARY}")
# endif()

# foreach(_lib PYTHIA8_LIBRARY)
#     if(${_lib})
#         set(PYTHIA8_LIBRARIES ${PYTHIA8_LIBRARIES} ${${_lib}})
#     endif()
# endforeach()

# set(PYTHIA8_INCLUDE_DIRS ${PYTHIA8_INCLUDE_DIR} ${PYTHIA8_INCLUDE_DIR}/Pythia8 )

# #include(${PYTHIA8_LIBRARIES})
# include_directories(${PYTHIA8_INCLUDE_DIRS})

#include(FindPackageHandleStandardArgs)
#FIND_PACKAGE_HANDLE_STANDARD_ARGS(Pythia8 DEFAULT_MSG PYTHIA8_INCLUDE_DIR PYTHIA8_LIBRARIES )
#mark_as_advanced(PYTHIA8_INCLUDE_DIR PYTHIA8_LIBRARY PYTHIA8_hepmcinterface_LIBRARY PYTHIA8_lhapdfdummy_LIBRARY)


#----------------------------------------------------------------------------
# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)

set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#ROOT_GENERATE_DICTIONARY(G__Plume Plume.h LINKDEF PlumeLinkDef.h)

#---Create a shared library with geneated dictionary
#add_library(Plume SHARED Plume.cc G__Plume.cc)
#target_link_libraries(Plume ${ROOT_LIBRARIES})




#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${ROOT_INCLUDE_DIRS})





#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h*)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(Plume Plume.cc ${sources} ${headers})
target_link_libraries(Plume ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${PYTHIA8_LIBRARIES})
#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(Plume_SCRIPTS
    #  Plume.in
    #  Plume.out
    init_vis.mac
    gui.mac
    run.mac
    Plume.cc
    vis.mac
    vis_file.mac
    PythiaSettings.cmnd
    HistPlotter/PhotonCounter.C
    )

foreach(_script ${Plume_SCRIPTS})
    configure_file(
        ${PROJECT_SOURCE_DIR}/${_script}
        ${PROJECT_BINARY_DIR}/${_script}
        COPYONLY
        )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(L DEPENDS Plume)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS Plume DESTINATION bin)
