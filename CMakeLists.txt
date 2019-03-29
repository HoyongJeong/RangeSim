################################################################################
#   CMakeLists.txt for RangeSim                                                #
#                                                                              #
#                      - 26. Mar. 2019. Hoyong Jeong (hyjeong@hep.korea.ac.kr) #
################################################################################

#------------------------------------------------------------------------------#
#   Setup the project                                                          #
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(RANGESIM)

#------------------------------------------------------------------------------#
#   Find Geant4 package, activating all available UI and Vis drivers by        #
# default. You can set WITH_GEANT4_UIVIS to OFF via the command line or        #
# ccmake/cmake-gui to build a batch mode only executable.                      #
#------------------------------------------------------------------------------#
option(WITH_GEANT4_UIVIS "Build wmc4 with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
	find_package(Geant4 REQUIRED ui_all vis_all)
else()
	find_package(Geant4 REQUIRED)
endif()

#------------------------------------------------------------------------------#
#   Setup Geant4 include directories and compile definitions                   #
#   Setup include directory for this project                                   #
#------------------------------------------------------------------------------#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#------------------------------------------------------------------------------#
#   Locate sources and headers for this project                                #
#   NB: headers are included so they will show up in IDEs                      #
#------------------------------------------------------------------------------#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#------------------------------------------------------------------------------#
#   Add the executable, and link it to the Geant4 libraries                    #
#------------------------------------------------------------------------------#
add_executable(rangesim rangesim.cc ${sources} ${headers})
target_link_libraries(rangesim ${Geant4_LIBRARIES})

#------------------------------------------------------------------------------#
#   Copy all scripts to the build directory, i.e. the directory in which we    #
# build RangeSim. This is so that we can run the executable directly because   #
# it relies on these scripts being in the current working directory.           #
#------------------------------------------------------------------------------#
set(RANGESIM_SCRIPTS
	README.md
	config.cfg
	init_vis.mac
	vis.mac
)

foreach(_script ${RANGESIM_SCRIPTS})
	configure_file(
		${PROJECT_SOURCE_DIR}/${_script}
		${PROJECT_BINARY_DIR}/${_script}
		COPYONLY
	)
endforeach()

file(COPY ${PROJECT_SOURCE_DIR}/scripts DESTINATION ${PROJECT_BINARY_DIR})

#------------------------------------------------------------------------------#
#   For internal Geant4 use - but has no effect if you build this RangeSim     #
# standalone                                                                   #
#------------------------------------------------------------------------------#
add_custom_target(RANGESIM DEPENDS rangesim)

#------------------------------------------------------------------------------#
#   Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX       #
#------------------------------------------------------------------------------#
install(TARGETS rangesim DESTINATION bin)

#------------------------------------------------------------------------------#
#   Flag setting                                                               #
#------------------------------------------------------------------------------#
set (CMAKE_CXX_FLAGS "-std=gnu++11")
