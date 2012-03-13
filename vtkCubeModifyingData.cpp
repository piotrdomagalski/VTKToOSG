#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkSmartPointer.h>

#include <vtkActorToOSG.hpp>

#include <osg/Geode>
#include <osgViewer/Viewer>

static vtkSmartPointer<vtkActor> getActor(void);

int main(int argc, char **argv)
{
	osg::ArgumentParser arguments(&argc, argv);
	osgViewer::Viewer viewer(arguments);

	vtkSmartPointer<vtkActor> actor = getActor();
	osg::ref_ptr<osg::Geode> geode = vtkActorToOSG(actor);

	viewer.setSceneData(geode);

	return viewer.run();
}

static vtkSmartPointer<vtkActor> getActor(void)
{
	float x[8][3] = {{0,0,0}, {1,0,0}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}};
	vtkIdType pts[6][4] = {{0,1,2,3}, {4,5,6,7}, {0,1,5,4}, {1,2,6,5}, {2,3,7,6}, {3,0,4,7}};

	vtkSmartPointer<vtkPolyData> cube = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
	vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();

	// Load the point, cell, and data attributes.
	for (int i = 0; i < 8; i++) points->InsertPoint(i, x[i]);
	for (int i = 0; i < 6; i++) polys->InsertNextCell(4, pts[i]);
	for (int i = 0; i < 8; i++) scalars->InsertTuple1(i, i);

	// We now assign the pieces to the vtkPolyData.
	cube->SetPoints(points);
	cube->SetPolys(polys);
	cube->GetPointData()->SetScalars(scalars);

	vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInput(cube);
	cubeMapper->SetScalarRange(0, 7);

	vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);

	return cubeActor;
}
