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

#include "objects.hh"


Cylinder::Cylinder(const Vector3D & Center,
                   const Vector3D & Orientation,
                   float Radius, float Height, 
                   const Color & Color, 
                   float Reflectivity) : SceneObject(Color, Reflectivity)
{
 assert(Orientation.magn2() > 0);
 assert(Radius >= 0);
 assert(Height >= 0);

 radius = Radius;
 height = Height;
 center = Center;
 orient = Orientation;
}


float Cylinder::Intersection(const Ray & R) const
{
 vector<float> vec;
 Vector3D Cpar, Cperp, Ppar, Pperp, Dpar, Dperp;
 
 Cpar = project(center, orient);
 Cperp = center - Cpar;

 Ppar = project(R.getOrigin(), orient);
 Pperp = R.getOrigin() - Ppar;

 Dpar = project(R.getDirection(), orient);
 Dperp = R.getDirection() - Dpar;

 Sphere S(Cperp, radius, Color(0,0,0));
 Ray newRay(Pperp, Dperp);
 
 S.AllIntersections(newRay, vec);
 if (vec[0] == NO_INTERSECTION) return vec[0];
 
 for (unsigned int i = 0; i < vec.size(); i++)
 {
  if ((Ppar + Dpar * vec[i] - Cpar).magn() < height / 2)
   return vec[i];
 }

 return NO_INTERSECTION;
}

const Vector3D Cylinder::Normal(const Vector3D & Point) const
{
  Vector3D V = Point - center;
  Vector3D Vperp = V - project(V, orient);
  Vperp.normalize();
  return Vperp;
}

bool Cylinder::contains(const Vector3D & Point) const
{
  Vector3D V = Point - center;
  Vector3D Vperp = V - project(V, orient);
  return (Vperp.magn() < radius + ERROR_MULT * FLT_EPSILON);
}



Cube::Cube(const Vector3D & v1,
		 const Vector3D & v2,
		 const Vector3D & v3,
		 const Color & Color_,
                 float reflectivity_) :SceneObject(Color_, reflectivity_)
{

//General
for (int i = 0; i < 6; i++) P[i].setColor(Color_);

P[0].setNormal(Vector3D(1,0,0));
P[0].setDistance(-1);

P[1].setNormal(Vector3D(-1,0,0));
P[1].setDistance(-1);

P[2].setNormal(Vector3D(0,1,0));
P[2].setDistance(-1);

P[3].setNormal(Vector3D(0,-1,0));
P[3].setDistance(-1);

P[4].setNormal(Vector3D(0,0,1));
P[4].setDistance(-1);

P[5].setNormal(Vector3D(0,0,-1));
P[5].setDistance(-1);

side_length = 2;
/*
assert(abs(dot(v3-v2, v2-v1)) > ERROR_MULT * FLT_EPSILON);
assert(abs((v3 - v1).magn() - (v2 - v1).magn()) < ERROR_MULT * FLT_EPSILON);

side_length = (v2 - v1).magn();

Vector3D Norm, T1, V1,V2,V3,V4,V5,V6,V7,V8;
float distance;

V1 = v1;
V2 = v2;


V3 = cross(v3 - V1, V2 - V1);
V3.normalize();
V3 = V2 + V3 * side_length;
V4 = V3 + V1 - V2;
V5 = v3;
V6 = V5 + V2 - V1;
V7 = V6 + V3 - V2;
V8 = V5 + V3 - V2;

T1 = V2 - V1; T1.normalize();
Center = V1 + 0.5 * T1 * side_length;
T1 = V4 - V1; T1.normalize();
Center += 0.5 * T1 * side_length;
T1 = V5 - V1; T1.normalize();
Center += 0.5 * side_length * T1;


cout << "\nSide length= " << side_length
     << "\nCube vertices:  "
     << "\n 1= " << V1
     << "\n 2= " << V2
     << "\n 3= " << V3
     << "\n 4= " << V4
     << "\n 5= " << V5
     << "\n 6= " << V6
     << "\n 7= " << V7
     << "\n 8= " << V8 
     << "\n Center= " << Center << endl; 


//Plane 1
Norm = V1 - V4;
T1 = Norm; T1.normalize();
distance = dot(V1, T1);

cout << "\n Norm1= " << Norm 
     << "\n dist1= " << distance;

P[0].setNormal(Norm);
P[0].setDistance(distance);

//Plane 2
P[1].setNormal(V2-V1);
T1 = V2 - V1;  T1.normalize();
P[1].setDistance(dot(V2, T1));

cout << "\n Norm2= " << V2 - V1 
     << "\n dist2= " << dot(V2,T1);

//Plane 3
T1 = Norm; T1.normalize();

P[2].setNormal(-Norm);
P[2].setDistance(dot(V4, -T1));

cout << "\n Norm3= " << -Norm
     << "\n dist3= " << dot(V4, -T1);

//Plane 4
T1 = V1 - V2; T1.normalize();

P[3].setNormal(V1 - V2);
P[3].setDistance(dot(V1, T1));

cout << "\n Norm4= " << V1 - V2
     << "\n dist4= " << dot(V1,T1);

//Plane 5
T1 = V5 - V1; T1.normalize();

P[4].setNormal(V5 - V1);
P[4].setDistance(dot(T1, V5));

cout << "\n Norm5= " << V5 - V1 
     << "\n dist5= " << dot(T1,V5);

//Plane 6
P[5].setNormal(V1 - V5);
P[5].setDistance(dot(V1, -T1));

cout << "\n Norm6= " << V1 - V5
     << "\n dist6= " << dot(V1,-T1) << endl;

*/

}
