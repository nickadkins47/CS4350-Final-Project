#New Module CMake Template written by Scott Nykl. This requires the engine is already built.
#Running "cmake ../src -LAH" from command line will list all CMake Variables. This is useful
#for extending and debugging CMake scripts.
cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)
get_filename_component(src_dir "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)
get_filename_component(proj_dir "${src_dir}" NAME)
PROJECT( "${proj_dir}" ) #This command populates CMAKE_SIZEOF_VOID_P and should be one of the first commands in the file
set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}" )
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

#These are the files that will appear in the output project (ie, in MSVC, this will be in the vcxproj)
#All cpp files that ought to be compiled in this project must be included here
FILE( GLOB sources ${CMAKE_SOURCE_DIR}/*.cpp ${CMAKE_SOURCE_DIR}/My/*.cpp )
FILE( GLOB headers ${CMAKE_SOURCE_DIR}/*.h  ${CMAKE_SOURCE_DIR}/My/*.h )
message( STATUS "HEADERS: ${headers}" )
message( STATUS "SOURCES: ${sources}" )

SET( aftrModuleCMakeHelperCmakeIncludePath "../../../include/cmake/aftrModuleCMakeHelper.cmake" )
include( ${aftrModuleCMakeHelperCmakeIncludePath} ) #sets ${AFTR_PATH_TO_CMAKE_SCRIPTS}, cmake_vars, and compiler_flags

#This will use the AftrConfig.h to determine which libraries AftrBurner was build against and
#then include those libraries to link against which compiling this modules exe.
#Let's include the default libraries and header include paths for libraries that were not found
#using the CMake FIND_PACKAGE method used inside of the file aftrModuleCMakeHelper.cmake.
#These other libraries and includes are added inside of aftrModuleCommonProjectIncludesAndLibs.cmake
SET( aftrModuleCommonProjectIncludesAndLibs "${AFTR_PATH_TO_CMAKE_SCRIPTS}/aftrModuleCommonProjectIncludesAndLibs.cmake" )
include( ${aftrModuleCommonProjectIncludesAndLibs} )

print_aftr_cmake_vars()

#Set CMAKE_CXX_FLAGS if any default flags need modification
#SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} ${cppFlags}" )
#SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${warnings}" )
MESSAGE( STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}" )
MESSAGE( STATUS "CMAKE_C_FLAGS  : ${CMAKE_C_FLAGS}" )

#Set any additional compiler flags -- by Default, usr/include/cmake/aftrModuleCMakeHelper.cmake sets AftrBurnerEngine-wide settings
if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
   #The following two variables (warnings and cppFlags) are set inside aftrModuleCMakeHelper.cmake).
   #This is where GNU/Clang specific compiler flags specifically for building this module are located.
   ###SET( warnings "${warnings} -Wall -Wextra -myWarningFlags" )
   ###SET( cppFlags "${cppFlags} -fpermissive -std=c++11 -myGNUCompilerFlag" )    #GNU/Clang specific CPP compiler flags
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
   #The following two variables (warnings and cppFlags) are set inside aftrModuleCMakeHelper.cmake).
   #This is where MSVC specific compiler flags specifically for building the engine are located.
   ###SET( warnings "${warnings} /W4 /EHsc" )
   ###SET( warnings "${warnings} /wd4100 /myWarningFlag" ) #disable warning: 'identifier' : unreferenced formal parameter   
   ###SET( cppFlags "${cppFlags} /std:c++latest" ) #MSVC Specific CPP compiler flags, MP=Multi Processor compilations 
endif()

#By default, modules use find_package for SDL and boost, every platform includes the headers and libraries the same way,
#but for packages that don't have the Find<MyLib>.cmake in the /engine/src/cmake folder, we have to manually add
#them per platform. The TARGET_LINK_LIBRARIES and TARGET_INCLUDE_DIRECTORIES below perform this function:

#This section is already populated with default values from: ../../../include/cmake/aftrModuleCommonProjectIncludesAndLibs.cmake
IF( WIN32 ) #MSVC Compiler library paths
   TARGET_LINK_LIBRARIES( ${PROJECT_NAME} PRIVATE
      #optimized "${AFTR_USERLAND_LIB_PATH}/mySampleLibraryNeededInThisModule.lib"
      #    debug "${AFTR_USERLAND_LIB_PATH}/mySampleLibraryNeededInThisModule_debug.lib"
      #optimized "${CMAKE_SOURCE_DIR}/lib${AFTR_NBITS}/myLocalLib.lib" #Located in ../lib64/ or ../lib32/
      #    debug "${CMAKE_SOURCE_DIR}/lib${AFTR_NBITS}/myLocalLib.lib"
      "C:/repos/aftr/usr/include/irrklang/lib/Winx64-visualStudio/irrKlang.lib" #IrrKlang
   )
ENDIF()

#This section is already populated with default values from: ../../../include/cmake/aftrModuleCommonProjectIncludesAndLibs.cmake
IF( UNIX ) #Linux, Apple, *NIX platforms (see ../../../include/cmake/aftrModuleCommonProjectIncludesAndLibs.cmake for more details)
   TARGET_LINK_LIBRARIES( ${PROJECT_NAME} PRIVATE
      #optimized "${AFTR_USERLAND_LIB_PATH}/mySampleLibraryNeededInThisModule.lib"
      #    debug "${AFTR_USERLAND_LIB_PATH}/mySampleLibraryNeededInThisModule_debug.lib"
      #optimized "${CMAKE_SOURCE_DIR}/lib${AFTR_NBITS}/myLocalLib.lib" #Located in ../lib64/ or ../lib32/
      #    debug "${CMAKE_SOURCE_DIR}/lib${AFTR_NBITS}/myLocalLib.lib"
      #          "mySystemInstalledlib" #called libMySystemInstalledlib.a (perhaps in /usr/lib64/)
   )
ENDIF()

#This section is already populated with default values from: ../../../include/cmake/aftrModuleCommonProjectIncludesAndLibs.cmake
#This can be made WIN32 or UNIX specific, depending on the platform, if desired.
TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME} PRIVATE 
   #"${AFTR_USR_INCLUDE_DIR}"
   #"${CMAKE_SOURCE_DIR}/../my3rdPartyLib/include/"
   "C:/repos/aftr/usr/include/irrklang/include" #IrrKlang
)

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} ${cppFlags}" )  #These two lines should be removed sln 3 aug 2022
SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${warnings}" )                  #These two lines should be removed sln 3 aug 2022
MESSAGE( STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}" )
MESSAGE( STATUS "CMAKE_C_FLAGS  : ${CMAKE_C_FLAGS}" )                          