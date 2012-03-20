#!/usr/bin/env python

import vtk

def get_actor():
	cone = vtk.vtkConeSource()
	cone.SetHeight(3.0)
	cone.SetRadius(1.0)
	cone.SetResolution(10)

	coneMapper = vtk.vtkPolyDataMapper()
	coneMapper.SetInputConnection(cone.GetOutputPort())

	actor = vtk.vtkActor()
	actor.SetMapper(coneMapper)

	return actor

def main():
	ren = vtk.vtkRenderer()
	ren.AddActor(get_actor())
	ren.SetBackground(0.1, 0.2, 0.4)

	renWin = vtk.vtkRenderWindow()
	renWin.AddRenderer(ren)
	renWin.SetSize(300, 300)

	iren = vtk.vtkRenderWindowInteractor()
	iren.SetRenderWindow(renWin)

	style = vtk.vtkInteractorStyleTrackballCamera()
	iren.SetInteractorStyle(style)

	iren.Initialize()
	iren.Start()
