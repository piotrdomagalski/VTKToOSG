#include <vtkActor.h>
#include <vtkObjectBase.h>

#include <VTKActorToOSG.hpp>

#include <boost/python.hpp>
#include <PyVTKObject.h>

#include <osg/Geode>
#include <osgViewer/Viewer>

#include <boost/filesystem.hpp>

#include <string>
#include <sstream>
#include <iostream>

namespace py = boost::python;
namespace fs = boost::filesystem;

static void *extract_vtk_wrapped_pointer(PyObject *obj)
{
	if (!PyVTKObject_Check(obj))
		return NULL;

	return ((PyVTKObject *)obj)->vtk_ptr;
}

#define VTK_PYTHON_CONVERSION(type) \
    /* register the from-python converter */ \
    boost::python::converter::registry::insert(&extract_vtk_wrapped_pointer, boost::python::type_id<type>());

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cerr << "Usage: " << argv[0] << " <path to python script> [script arguments...]" << endl;
		return -1;
	}

	fs::path pathname(argv[1]);

	if (!fs::exists(pathname)) {
		cerr << "File " << argv[1] << " does not exist!" << endl;
		return -1;
	}

	Py_Initialize();
	VTK_PYTHON_CONVERSION(vtkActor);

	py::tuple actors;

	try {
		py::object global = py::import("__main__").attr("__dict__");

		std::ostringstream import_code;
		import_code << "import sys\n";
		import_code << "sys.path.append('" << pathname.parent_path().string() << "')\n";
		import_code << "from " << pathname.stem().string() << " import get_actors\n";

		py::exec(import_code.str().c_str(), global, global);

		py::list args;

		if (argc > 2) {
			for (int i = 2; i < argc; i++)
				args.append((const char *) argv[i]);
		}

		py::object result = global["get_actors"](args);
		actors = py::extract<py::tuple>(result);

	} catch (py::error_already_set) {
		PyErr_Print();
		return -1;
	}

	osgViewer::Viewer viewer;

	osg::ref_ptr<osg::Group> group = new osg::Group;

	for (int i = 0; i < py::len(actors); i++)
		group->addChild(VTKActorToOSG(py::extract<vtkActor *>(actors[i])));

	viewer.setSceneData(group);

	return viewer.run();
}
