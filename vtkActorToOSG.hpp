// Copyright (C) 2002-2003 Michael Gronager, UNI-C
//
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.

#ifndef VTKACTORTOOSG_HPP
#define VTKACTORTOOSG_HPP

#include <osg/Geode>
#include <osg/ref_ptr>

#include <vtkActor.h>

osg::ref_ptr<osg::Geode> vtkActorToOSG(vtkActor *actor, osg::ref_ptr<osg::Geode> geode = NULL, int verbose = 0);

#endif
