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
* @file Contains the declaration and implementation of the Ray class.
*/

#ifndef RAY_HH
#define RAY_HH

#include <iostream>
#include "vector.hh"

/** A camera ray implementation.
 * Originates at the position of the camera.
 * Is shot at a certain point in space.
 * Has a maximal travelling distance.
 */
class Ray
{

private:
  Vector3D Origin, Direction;

public:  

/** The constructor.
* @param Origin_ The position vector of the origin of the ray.
* @param Direction_ The direction vector of the direction of the ray.
*/
  Ray(const Vector3D & Origin_, const Vector3D & Direction_);

/** Accessor for the position vector of the origin. */
  const Vector3D getOrigin() const;

/** Accessor for the direction vector of the origin. */
  const Vector3D getDirection() const;

/** Returns the position of the ray after a certain "time". 
* @param t The so-called "time" parameter.
* @return The position vector of the point.
*/
  const Vector3D getPoint(float t) const;
  const Ray reflect(const Vector3D & Intersection,
                         const Vector3D & Normal) const;
};



inline Ray::Ray(const Vector3D & Origin_, const Vector3D & Direction_)
{
  Origin = Origin_;
  Direction = Direction_;
  Direction.normalize();
}

inline const Vector3D Ray::getPoint(float t) const
{ 
  //assert(t >= 0);
  return Origin + t*Direction;
}

inline const Vector3D Ray::getOrigin() const
{
  return Origin;
}

inline const Vector3D Ray::getDirection() const
{
  return Direction;
}

inline const Ray Ray::reflect(const Vector3D & Intersection,
                                        const Vector3D & Normal) const
{
 Vector3D NewVector;
 
 //Compute the direction of the reflecteed ray using the incident
 NewVector = project(-Direction, Normal);
 NewVector = Direction + 2 * NewVector;
 
 //New reflected ray
 float delta = 0.0001; // Offset from original point
 
 return Ray(Intersection + NewVector * delta, NewVector);
}

#endif
