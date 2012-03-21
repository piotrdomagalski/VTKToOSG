What is it?
===========

VTKToOSG is a simple project that demonstrates the usage of [vtkActorToOSG
class](http://archive.ncsa.illinois.edu/prajlich/vtkActorToPF/) created by
Michael Gronager.

Besides simple integration on C++ level (VTKCube and VTKMedical), it also
contains an example of how one might extract VTK actor constructed in Python
and visualize it in OSG viewer (VTKPython).

Dependencies
============

The project depends on some external libraries. I tested it with:

* VTK 5.8
* OpenSceneGraph 3.0.1
* Boost 1.48
* Python 2.7.3
* CMake 2.8.7

Please beware that `CMakeLists.txt` does not check for particular versions of
(apart from CMake) so in case of some older versions the compilation might fail
with magical errors.

Compilation
===========

Thanks to CMake the compilation should be extremely simple:

1. `cd VTKToOSG`
2. `mkdir build && cd build`
3. `cmake ../src && make`

Running the examples
====================

* `./VTKCube`
* `./VTKMedical ../data/headsq/quarter`
* `./VTKPython ../scripts/CSpline.py`
* `./VTKPython ../scripts/Medical2.py ../data/headsq/quarter`
