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
* @file camera.hh The Camera class and its methods
*/

#ifndef CAMERA_HH
#define CAMERA_HH

#include <iostream>
#include <cmath>
#include "vector.hh"


/** Describes the behaviour of a camera */
class Camera
{
private:



public:

/** The position of the camera in 3D */
  Vector3D Pos;

/** The direction at which the camera points */
  Vector3D Dir;

/** The Field of View of the camera, in radians */
  float fov;

/** The upwards direction vector */
  Vector3D Up;

/** The right-ward direction vector */
  Vector3D Right;

/** The distance from the camera that the rays can reach */
  float Dist;


/** The only constructor.
* @param Position The position vector of the camera.
* @param LookAt The position vector of the point to look at.
* @param UpReference The upwards direction vector.
* @param fov_ The Field of View
*/
  Camera(Vector3D Position, 
         Vector3D LookAt, 
         Vector3D UpReference, float fov_);

/** Returns the ray which passes through a certain pixel.
* @param x The x coordinate of the pixel. Boundary: Abs(x) < imgSize.
* @param y The y coordinate of the pixel Boundary: Abs(y) < imgSize.
* @param imgSize The size of the image, in pixels.
* @return Ray The ray passing through that pixel.
*/

  Ray getRayForPixel(int x, int y, int imgSize) const;
};

inline Camera::Camera(Vector3D Position,
                      Vector3D LookAt,
                      Vector3D UpReference,
                      float fov_)
{
  fov = fov_; 
  Pos = Position;
  Dir = LookAt - Position;
  Dir.normalize();
  
  Right = cross(Dir, UpReference);
  Right.normalize();
  
  //Shouldn't this be 0 always because cross(Dir,Dir)=0?
  Up = cross(Right, Dir); 
  Up.normalize();
  
  Dist = 0.5 / tan(fov / 2);
}

inline Ray Camera::getRayForPixel(int x, int y, int imgSize) const
{
  assert(x >= 0);
  assert(y >= 0);
  assert(imgSize >= 0);
  assert((x < imgSize) && (y < imgSize));
    
  Vector3D pixelDir;
  pixelDir = Dist * Dir;
  pixelDir += (0.5 - (float) y / (float) (imgSize - 1) ) * Up;
  pixelDir += ((float) x / (float) (imgSize - 1) - 0.5) * Right;
  
  Ray pixelRay(Pos, pixelDir);
  return pixelRay;
}


#endif //CAMERA_HH
