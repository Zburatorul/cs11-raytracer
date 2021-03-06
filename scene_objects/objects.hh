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
* @file objects.hh Contains the definition of Plane, Sphere and Cylinder
*/

#ifndef SceneObjects_HH
#define SceneObjects_HH

#include <iostream>
#include <cmath>
#include <cfloat>
#include "../color.hh"
#include "../scene.hh"

using namespace std;

// The multimple of the FLT_EPSILON constant to compare error with
/** The number within the multiple of which lies tracing error */
const short int ERROR_MULT = 3;


/** Describes a plane, extends SceneObject. */
class Plane : public SceneObject
{
private:

/** The distance to the origin of the coordinate system */
  float SDistance; 

/** The normal to the plane, in any point. */
  Vector3D NNormal, //The normalized copy
/** The normal to the plane, non-normalized. */
           PNormal; //The original copy
  
public:

/** The constructor.
* @param FromOrigin The distance to the origin.
* @param Normal_ The normal to the plane.
* @param Color_ The color of the plane.
* Sets NNormal to Normal_ and normalizes it.
*/

  Plane() {}

  Plane(float FromOrigin, Vector3D Normal_,
        const Color & Color_,
        float reflectivity_ = 0 ):SceneObject(Color_, reflectivity_)
  {
   SDistance = FromOrigin;
   PNormal = NNormal = Normal_;
   NNormal.normalize();
  }

/** The destructor. Does nothing */
  virtual ~Plane() {}
  
  //Accessors
/** Accessor to the distance from the origin */
  const float SDistanceFromOrigin() const;

/** Accessor to the surface normal */
  const Vector3D SurfaceNormal() const;

/** The overloaded method that determines intersection with a ray.
 * @return NO_INTERSECTION if no intersection takes place.
 */
  float Intersection(const Ray & R) const;

/** Returns the normal to the surface at a certain point */
  virtual const Vector3D Normal(const Vector3D & Point) const;

/** Determines whether a certain point belongs to the plane. */
  virtual bool contains(const Vector3D & Point) const;

/** Returns the color at a certain point. */
  virtual const Color getColor(const Vector3D & Point) const
  {
    
    return BaseColor;
  }
  
 //Mutators
 void setColor(const Color & Color_);
 void setNormal(const Vector3D & Normal_);
 void setDistance(float Distance);

};

inline void Plane::setDistance(float Distance)
{
  SDistance = Distance;
}

inline void Plane::setNormal(const Vector3D & Normal_)
{
   
  PNormal = NNormal = Normal_;
  NNormal.normalize();
}


inline void Plane::setColor(const Color & Color_)
{
  BaseColor = Color_;
}


inline bool Plane::contains(const Vector3D & Point) const
{
  return (cross(Point, NNormal).magn() > 0.001);
}

inline const float Plane::SDistanceFromOrigin() const
{
  return SDistance;
}

inline const Vector3D Plane::SurfaceNormal() const
{
  return NNormal;
}

inline float Plane::Intersection(const Ray & R) const
{
 Vector3D P = R.getOrigin();
 Vector3D D = R.getDirection();
 
 float t, dotprod = dot(PNormal,D);
 
 //If Normal dot  D = 0, then no intersection
 if (dotprod == 0) return NO_INTERSECTION;
 
 t = - (dot(P,PNormal) + SDistance) / dotprod;
 
 if (t <= 0) 
  return NO_INTERSECTION;
 else
  return t; 
}

inline const Vector3D Plane::Normal(const Vector3D & Point) const
{
  return PNormal;
}




/** Describes a sphere. Extends SceneObject. */
class Sphere : public SceneObject
{
private:

/** A vector to the center of the sphere. */
  Vector3D Center;
/** The radius of the sphere. */
  float Radius;

public:

/** The constructor.
* @param Center_ The position vector of the sphere.
* @param Radius_ The radius of the sphere.
* @param Color_ The color of the sphere.
*/
  Sphere ( const Vector3D & Center_, 
           float Radius_, 
           const Color & Color_,
           float reflectivity_ = 0 ):SceneObject(Color_, reflectivity_)
  {
  assert(Radius_ > 0);
  Radius = Radius_;
  Center = Center_;
  }
  
/** The destructor. Does nothing. */
  virtual ~Sphere() {}

/** An accessor to the position vector of the center of the sphere. */
  const Vector3D getCenter() const;

/** An accessor to the radius of the sphere. */
  const float getRadius() const;
  
/** The overloaded method that determines an intersection with a ray.
 * @return NO_INTERSECTION is returned if no intersection takes place.
 */
  float Intersection(const Ray & R) const;
  void AllIntersections(const Ray & R, vector<float> & vec) const;

/** Returns the normal to the surface at a certain point. */
  virtual const Vector3D Normal(const Vector3D & Point) const;

/** Determines whether a certain point belongs to the sphere. */
  virtual bool contains(const Vector3D & Point) const;

/** Returns the color of the sphere at a certain point. */
  virtual const Color getColor(const Vector3D & Point) const
  {
    if (!contains(Point)) 
    cerr << "Dist(Point, Edge_of_sphere)= " 
         << (Point - Center).magn() - Radius << endl;
    return BaseColor;
  }


};


inline bool Sphere::contains(const Vector3D & Point) const
{
  return ((Point - Center).magn() < Radius + 0.01);
}

inline const Vector3D Sphere::getCenter() const
{
  return Center;
}

inline const float Sphere::getRadius() const
{
  return Radius;
}

inline float Sphere::Intersection(const Ray & R) const
{
  Vector3D D = R.getDirection();
  Vector3D P = R.getOrigin();
  
  float double_a,b,c, delta, t1, t2;
  
  // "a" is calculated as twice as much as needed, to save calculations later
  double_a = 2 * dot(D,D);
  b = 2 * (dot(P,D) - dot(D,Center));
  c = dot(P,P) + dot(Center,Center) - 2 * dot(P,Center) - Radius * Radius;
  delta = b * b - 2 * double_a * c;
  
  //If the discriminant is closer to zero than the error, return 1p
  if (abs(delta) < ERROR_MULT * FLT_EPSILON) 
  {
   t1 =  -b / double_a;
   if (t1 > 0)
    return t1;    
   else  
    return NO_INTERSECTION;
  }
  
  if (delta < 0) return NO_INTERSECTION;
  
  delta = sqrt(delta);
  
  t1 = (-b - delta) /  double_a;
  if ( t1 > 0)    
   return t1;    
 
  t2 = (-b + delta) /  double_a;
  if ( t2 > 0) 
    return t2;    
  else
    return NO_INTERSECTION;  
}

inline void Sphere::AllIntersections(const Ray & R, vector<float> & vec) const
{
  Vector3D D = R.getDirection();
  Vector3D P = R.getOrigin();
  
  float double_a,b,c, delta, t1, t2;
  
  // "a" is calculated as twice as much as needed, to save calculations later
  double_a = 2 * dot(D,D);
  b = 2 * (dot(P,D) - dot(D,Center));
  c = dot(P,P) + dot(Center,Center) - 2 * dot(P,Center) - Radius * Radius;
  delta = b * b - 2 * double_a * c;
  
  //If the discriminant is closer to zero than the error, return 1p
  if (abs(delta) < ERROR_MULT * FLT_EPSILON) 
  {
   t1 =  -b / double_a;
   if (t1 > 0)
    vec.push_back(t1);    
   else  
    vec.push_back(NO_INTERSECTION);
  
  return;
  }
  
  if (delta < 0) 
  {
   vec.push_back(NO_INTERSECTION);
   return;
  }
  
  delta = sqrt(delta);
  
  t1 = (-b - delta) /  double_a;
  t2 = (-b + delta) /  double_a;
  
  vec.push_back(t1);
  vec.push_back(t2);
}

inline const Vector3D Sphere::Normal(const Vector3D & Point) const
{
  Vector3D N = Point - Center;
  N.normalize();
  return N;
}


class Cylinder : public SceneObject
{
 private:
  Vector3D center;
  Vector3D orient;
  float radius;
  float height;

 public:
  Cylinder(const Vector3D & Center,
           const Vector3D & Orientation,
           float Radius, float Height, 
           const Color & Color, 
           float Reflectivity);
  ~Cylinder() {};

  virtual float Intersection(const Ray & R) const;

/** Returns the normal to the surface of the object at a certain point. */
  virtual const Vector3D Normal(const Vector3D & Point) const;

/** Determines whether a point belongs to the object (within an error). */
  virtual bool contains(const Vector3D & Point) const; 

};


class Cube : public SceneObject
{
private:

Plane P[6];
float side_length;
Vector3D Center;

public:

 Cube(const Vector3D & v1,
      const Vector3D & v2,
      const Vector3D & v3,
      const Color & Color_,
      float reflectivity_ = 0 ); 

 ~Cube() {};

  virtual float Intersection(const Ray & R) const;

/** Returns the normal to the surface of the object at a certain point. */
  virtual const Vector3D Normal(const Vector3D & Point) const;

/** Determines whether a point belongs to the object (within an error). */
  virtual bool contains(const Vector3D & Point) const;


};



inline bool Cube::contains(const Vector3D & Point) const
{ 
  //cout << "dist (p - c)= " << (Point - Center).magn() << endl;
  return ((Point - Center).magn() < side_length * sqrt(0.75) + ERROR_MULT * FLT_EPSILON);
}


inline float Cube::Intersection(const Ray & R) const
{ 
  int i;
  float temp, t = 10e6;

  for(i = 0; i < 6; i++)
  {
   temp = P[i].Intersection(R);
   if ((t > temp) && (temp != -1))
   {
    t = temp;
   }
  }
  
 // cout << "Searching for cube t=" << t << endl; 
  
  if (t != 10e6)
  { 
  //cout << "Verifying inter at " << R.getPoint(t) << endl;
    if (contains(R.getPoint(t))) 
      return t;
    else 
      return NO_INTERSECTION;
  }
  else 
    return NO_INTERSECTION;  
}


inline const Vector3D Cube::Normal(const Vector3D & Point) const
{
  for (int i = 0; i < 6; i++)
 {
   if (P[i].contains(Point)) return P[i].Normal(Point);
 }
  assert(false); //Point contained by cube, but not by it's planes
}


inline ostream & operator<<(ostream & os, const Sphere & S)
{
  os << "Sphere at " 
     << S.getCenter()  
     << " with radius= " << S.getRadius()
     << endl;     

  return os;
}  


inline ostream & operator<<(ostream & os, const Plane & P)
{
  os << "Plane with normal " 
     << P.SurfaceNormal() 
     << " at distance " 
     << P.SDistanceFromOrigin()  
     << " from origin. "
     << endl;

  return os;
}  

//OBJECTS_HH
#endif
