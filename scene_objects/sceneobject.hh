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
* @file sceneobject.hh The SceneObject abstract class definition.
*/

#ifndef SCENEOBJECT_HH
#define SCENEOBJECT_HH

#include "../color.hh"
#include "../ray.hh"

/** A base class for objects in 3D */
class SceneObject
{
protected:

/** The base color of the object. */
  Color BaseColor;
  float reflectivity;
  
public:

/** The only constructor */
  SceneObject(Color BaseColor_, float reflectivity_): 
  BaseColor(BaseColor_), reflectivity(reflectivity_) {}
  SceneObject() {}
  
/** The desctructor. 
* Does nothing.
*/
  virtual ~SceneObject() {} 
  
/** A method that determines intersections with rays.
* @param R A ray of light flying through the scene.
* @return The value of the so called "time parameter". If no intersection is
* detected, the return value is NO_INTERSECTION.
* @see NO_INTERSECTION
* @see Ray
*/
  virtual float Intersection(const Ray & R) const = 0;

/** Returns the normal to the surface of the object at a certain point. */
  virtual const Vector3D Normal(const Vector3D & Point) const = 0;

/** Determines whether a point belongs to the object (within an error). */
  virtual bool contains(const Vector3D & Point) const = 0;

/** An accessor for the color of the object at a certain point. */
  virtual const Color getColor(const Vector3D & Point) const 
  {
    return BaseColor;
  }

/** An mutator for the color of the object. */
 void setColor(Color Color_)
 {
   BaseColor = Color_;
 }

/** An accesor to the reflectivity of the object.*/
 float Reflectivity()
  {
   return reflectivity;
  }
};

#endif //SCENEOBJECT_HH

 
