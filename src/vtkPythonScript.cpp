#include <vtkActor.h>
#include <vtkObjectBase.h>

#include <vtkActorToOSG.hpp>

#include <boost/python.hpp>
#include <PyVTKObject.h>

#include <osg/Geode>
#include <osgViewer/Viewer>

using namespace boost::python;

void *extract_vtk_wrapped_pointer(PyObject *obj)
{
	if (!PyVTKObject_Check(obj))
		return NULL;

	return ((PyVTKObject *)obj)->vtk_ptr;
}

#define VTK_PYTHON_CONVERSION(type) \
    /* register the from-python converter */ \
    converter::registry::insert(&extract_vtk_wrapped_pointer, type_id<type>());

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cerr << "Usage: " << argv[0] << " cone.py" << endl;
		return -1;
	}

	Py_Initialize();

	VTK_PYTHON_CONVERSION(vtkActor);

	vtkObjectBase *vtkObject;
	vtkActor *actor;

	object main_module, global, ignored, result;

	try {
		main_module = import("__main__");
		global = main_module.attr("__dict__");
		ignored = exec_file(argv[1], global, global);

		result = global["get_actor"]();

		actor = extract<vtkActor *>(result);

		cout << actor->GetClassName() << endl;
	} catch (error_already_set) {
		PyErr_Print();
		return -1;
	}

	osg::ArgumentParser arguments(&argc, argv);
	osgViewer::Viewer viewer(arguments);

	osg::ref_ptr<osg::Geode> geode = vtkActorToOSG(actor);

	viewer.setSceneData(geode);

	return viewer.run();
}
