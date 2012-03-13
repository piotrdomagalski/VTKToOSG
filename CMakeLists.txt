cmake_minimum_required(VERSION 2.8)
project(vtkToOSG)

find_package(OpenSceneGraph REQUIRED osg osgViewer)
find_package(VTK REQUIRED)

SET(CMAKE_CXX_FLAGS "-Wall -Wno-deprecated")

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${VTK_INCLUDE_DIRS}")
include_directories("${OPENSCENEGRAPH_INCLUDE_DIRS}")

file(GLOB VTKACTORTOOSG vtkActorToOSG.?pp)
add_library(vtkActorToOSG STATIC ${VTKACTORTOOSG})

add_executable(vtkCube vtkCube.cpp)
add_executable(vtkCubeModyfingData vtkCubeModyfingData.cpp)
#add_executable(vtkMedical vtkMedical.cpp)

target_link_libraries(vtkCube vtkActorToOSG vtkRendering ${OPENSCENEGRAPH_LIBRARIES})
target_link_libraries(vtkCubeModyfingData vtkActorToOSG vtkRendering ${OPENSCENEGRAPH_LIBRARIES})
#target_link_libraries(vtkMedical vtkActorToOSG vtkRendering ${OPENSCENEGRAPH_LIBRARIES})
