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
* @file scene.cc Implementation of several methods of the Scene class
*/

#include "scene.hh"

/** Just a handy function */
float max(float f1, float f2)
{
  if (f1 > f2) 
  return f1;
  else 
  return f2;
}


/** The rendering function.
* @param cam The camera object describing the point of view from which the 
* scene is looked at.
* @param imgSize The size of the image in pixels.
* @param out The stream to which the output should be directed.
* @return No return value. It does however output an image to the provided stream.
* This method will shoot rays out of each pixel in order to determine their color.
* The color of the pixel is calculated by taking into account all the light objects
* in the scene. As a result, if the colors are too bright they might eventually get
* out of the [0,1] range in which color is defined by convention. In this case, the
* Render method will use the ceiling function to limit those color components which 
* exceed 1, to 1. The resulting image is directed to the out stream in the form of a
* ASCII PNM image.
* @see Camera
*/
void Scene::Render(const Camera & cam, int imgSize, ostream & out) const
{
  out << "P3 " << imgSize << " " << imgSize << " " << 255 << endl;
  short int k = 0;
  float R,G,B,T;
  
  for (int y = 0; y < imgSize; y++)
  {
   for (int x =0; x < imgSize; x++)
    {
      Ray pixelRay = cam.getRayForPixel(x,y,imgSize);
      Color pixelColor = traceRay(pixelRay);
      //Output 4 pixels per line
      if (k == 4) 
      { 
       out << endl;
       k = 0;
      }
      k++; 
      
      R = pixelColor.get_red();
      G = pixelColor.get_green();
      B = pixelColor.get_blue();
      
      //Let's ceil them
      R = ceil(((R > 1) ? 1 : R) * 255);
      G = ceil(((G > 1) ? 1 : G) * 255);
      B = ceil(((B > 1) ? 1 : B) * 255);
          
      
      out << R << " " 
          << G << " "
          << B << " ";
         
    }
  }
}


/** Traces one ray and determines the color of a certain pixel.
* @param R The ray to be traced.
* @return The color of the point of intersection with the closest object.
 
* This method will check for intersections with all the objects in the
* scene and determine the color of the object at the point of intersection
* taking into account all the light source in the scene. If no intersections are
* detected, the color returned is the background color of the scene.
* If the color ends up being too bright and gets out of range, the traceRay
* method will not signal this.
* @see Ray
*/ 

Color Scene::traceRay(const Ray & R, unsigned int depth) const
{
  int i,k = 0;
  float temp, t = 10e6;
  int Ssize = SObjects.size(); 
  int Lsize = Lights.size();
  Color Result(0,0,0), TempColor;
  Vector3D L,N, Intersection;
  Ray reflected_ray(L,L);
    
  for(i = 0; i < Ssize; i++)
  {
   temp = SObjects[i]->Intersection(R);
   if ((t > temp) && (temp != -1))
   {
    t = temp;
    k = i; 
   }
  }
  
  if(t == 10e6)  return BACKGROUND_CLR;
  
  //if (!SObjects[k]->contains(R.getPoint(t)))
   //cerr << "False intersect with object k=" << k << " (t=" << t << ") at " << R.getPoint(t);
  Intersection = R.getPoint(t);

  for(i = 0; i < Lsize; i++)
  {
    L = Lights[i]->getPosition() - Intersection;
    N = SObjects[k]->Normal(Intersection);
    TempColor = Lights[i]->getColor();
    TempColor *= SObjects[k]->getColor(Intersection);
    TempColor *= max(dot(N,L),0);
    Result += TempColor;
  }

   //Check if object is reflective or if we've reached max depth
   if ((depth < 6) && (SObjects[k]->Reflectivity() > 0))
   { 
     reflected_ray = R.reflect(Intersection, SObjects[k]->Normal(Intersection));
     TempColor = traceRay(reflected_ray, depth + 1);
     Result += SObjects[k]->Reflectivity() * TempColor;
   }

  return Result;
}

void Scene::Describe()
{
  int Ssize = SObjects.size(); 
  int Lsize = Lights.size();
 
  cout << "\t Scene Description: \n"; 
  cout << " * Total of " << Ssize << " scene objects. \n"
       << " * Total of " << Lsize << " light objects. \n";

  for(short int i = 0; i < Ssize; i++)
  {
   // cout << " * Object.color= " << SObjects[i];
  }

  cout << "\t End Scene Description. \n";
}



