cmake_minimum_required(VERSION 2.8)
project(vtkToOSG)

set(CMAKE_CXX_FLAGS "-Wall -Wno-deprecated")

find_package(OpenSceneGraph REQUIRED osg osgViewer)
find_package(VTK REQUIRED)

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS python filesystem system)
find_package(PythonLibs)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${VTK_INCLUDE_DIRS})
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

file(GLOB VTKACTORTOOSG vtkActorToOSG.?pp)
add_library(vtkActorToOSG STATIC ${VTKACTORTOOSG})

add_executable(vtkCube vtkCube.cpp)
target_link_libraries(vtkCube vtkActorToOSG vtkRendering ${OPENSCENEGRAPH_LIBRARIES})

add_executable(vtkMedical vtkMedical.cpp)
target_link_libraries(vtkMedical vtkActorToOSG vtkRendering vtkIO ${OPENSCENEGRAPH_LIBRARIES})

if (Boost_FOUND AND PYTHONLIBS_FOUND)
	include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
	add_executable(vtkPython vtkPython.cpp)
	target_link_libraries(vtkPython vtkActorToOSG vtkRendering vtkPythonCore ${OPENSCENEGRAPH_LIBRARIES} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
else()
	message(WARNING "Boost and/or Python libraries were not found. vtkPython example will not be built.")
endif()
