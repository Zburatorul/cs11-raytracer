/***************************************************************************
 *   Copyright (C) 2007 by Eugeniu Plamadeala   *
 *   eugeniu@caltech.edu   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/**
* @file scene.hh The Scene class and implementation of several methods
*/
#ifndef SCENE_HH
#define SCENE_HH

#include <iostream>
#include <vector>
/**  
* @include Needed in order for the shared_ptr container
*/
#include <boost/shared_ptr.hpp>
#include "scene_objects/sceneobject.hh"
#include "color.hh"
#include "ray.hh"
#include "camera.hh"
#include "light.hh"


using namespace std;

//Returned by Intersection(const Ray &) if there's no intersection.
/** The result of the Intersection function if no intersection is detected 
* @see SceneClass::Intersection()
*/
const int NO_INTERSECTION = -1;

/** The background color of the scene.
* @see Color
 */
const Color BACKGROUND_CLR = Color(0.1,0.1,0.5);

/** A shorter definition for a shared_pt<SceneObject> object */
typedef boost::shared_ptr<SceneObject> SPSceneObject; 
/** A shorter definition for a shared_pt<Light> object*/
typedef boost::shared_ptr<Light> SPLight;



/** Describes the scene.
* Has information about the surroundings:
* light source, objects.
* Needs a camera object in order to render a scene.
* @see Camera
*/
class Scene
{


public:

/** An STL vector holding the Scene Objects */
  vector<SPSceneObject> SObjects;

/** An STL vector holding Light objects */
  vector<SPLight> Lights;  

/** Default constructor. Does nothing. */
  Scene() {};

/** Destructor. Does nothing. */
  ~Scene() {};

/** Adds a new SceneObject to the scene */
  void AddSceneObject(SPSceneObject SObject);

/** Adds a new Light object to the scene */
  void AddLight(SPLight LObject);

/** Renders the scene. */
  void Render(const Camera & cam, int imgSize, ostream & out) const;

/** Returns the color of the object that the ray falls on. */ 
  Color traceRay(const Ray & R, unsigned int depth = 0) const;

/** Prints information about the scene. 
* Mostly used for debugging.
**/
  void Describe();

};


inline void Scene::AddSceneObject(SPSceneObject SObject)
{ 
  //Check valid pointer
  assert(SObject != 0);
  
  //Should check for enough memory if the vector is resized?
  SObjects.push_back(SObject);
}



inline void Scene::AddLight(SPLight LObject)
{
  //Check valid pointer
  assert(LObject != 0);
  
  //Should check for enough memory in case of resizing?
  Lights.push_back(LObject);
}




#endif  //SCENE_HH

