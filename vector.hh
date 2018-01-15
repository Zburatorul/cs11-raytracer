/**
* \file vector.hh  Contains the implementation of the Vector3D class 
* and several operator overloads.
*/

#ifndef VECTOR_HH
#define VECTOR_HH


#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

/** A shorter definition for an unsigned integer.
*/

typedef unsigned int uint;


/**
* An implementation of a 3-dimensional vector of floats.

* Can be used to represent both direction and position vectors.
* The basis for this vector space is formed by the unit vectors:
* (1, 0, 0), (0, 1, 0) and (0, 0, 1).
* The class lacks a desctructor because it makes no use of dynamically 
* allocated objects.
*/


class Vector3D
{
 private:
 

 
  /**
  * An array of floats holding the coordinates of the vector.
  * The coordinates are as follows:
  * vec[0] == x
  * vec[1] == y
  * vec[2] == z
  */
  
  float vec[3];
  
 public:
 
  //Constructors
  
  /** The default/copy constructor. 
  * Initializes all components to 0 (zero).
  * @see Vector3D(float x, float y, float z)
  * @return Has no return value.
  */
  Vector3D();

  /** Another constructor initializing the vector by componets.
  * @param x the x component
  * @param y the y component
  * @param z the z component
  * @see Vector3D()
  * @return Has no return value.
  */
  Vector3D(float x, float y, float z);
  Vector3D(float * vec_);
  
  //Compound operators  
  /** An overload of the += operator.
  * @param Other The right hand side argument.
  */
  Vector3D & operator+=(const Vector3D & Other);


  /** An overload of the -= operator.
  * @param Other The right hand side argument.
  */
  Vector3D & operator-=(const Vector3D & Other);

  /** An overload of the *= operator (scaling of a vector).
  */
  Vector3D & operator*=(float scalar);

  /** An overload of the /= operator (scaling of a vector).
  */
  Vector3D & operator/=(float scalar);

  
 //Accessor & Mutator overloads of []
  /** An overload of the [] operator.
  * @param index The index of the component to access.
  * @see vec
  * @see uint
  * @return Returns the corresponding component of the vector
  * as a constant float.
  * Used on the right hand side of any binary operation.
  */
  const float operator[](uint index) const;

  /** An overload of the [] operator.
  * @param index The index of the component to access.
  * @see vec
  * @see uint
  * @return Returns a reference to the corresponding component of the vector \
  * Used on the left hand side of any binary operation.
  */
  float & operator[](uint index);
  
  //Additional methods
  /** Returns the squared magnitude of the vector.
  */
  const float magn2() const;
  
  /** Returns the magnintude of the vector.
  */
  const float magn() const;

  /**  Normalizes the vector.
  */
  void normalize();
  
};



//Default constructor
inline Vector3D::Vector3D()
{
  vec[0] = 0;
  vec[1] = 0;
  vec[2] = 0;
}  
 
// Constructor with initialization componentwise 
inline Vector3D::Vector3D(float x, float y, float z)
{
  vec[0] = x;
  vec[1] = y;
  vec[2] = z;
}
  

inline Vector3D::Vector3D(float * vec_)
{
  vec[0] = vec_[0];
  vec[1] = vec_[1];
  vec[2] = vec_[2];
}

// [] operator overload, used on the RIGHT HAND SIDE,  
// returns a  "read-only" object
inline const float Vector3D::operator[](uint index) const
{
  assert(index < 3);
  return vec[index];
}
 
// [] operator overload, used on the  LEFT HAND SIDE , 
// return a "writable" object.  Supports chaining 
inline float & Vector3D::operator[](uint index)
{
  assert(index < 3);
  return vec[index];
}
  
  
inline Vector3D & Vector3D::operator+=(const Vector3D & Other)
{
  vec[0] += Other[0];
  vec[1] += Other[1];
  vec[2] += Other[2];
  
  return *this;
}
     
inline Vector3D & Vector3D::operator-=(const Vector3D & Other)
{
  vec[0] -= Other[0];
  vec[1] -= Other[1];
  vec[2] -= Other[2];
  
  return *this;
}
   

inline Vector3D & Vector3D::operator*=(const float scalar)
{
  vec[0] *= scalar;
  vec[1] *= scalar;
  vec[2] *= scalar;
  
  return *this; 
}


// Compound division by a non-zero scalar
inline Vector3D & Vector3D::operator/=(const float scalar)
{
  assert(scalar != 0);
   
  vec[0] /= scalar;
  vec[1] /= scalar;
  vec[2] /= scalar;
  
  return *this; 
} 


// The unary - operator.
/** An implementation of the subtraction operation for vectors.
*/
inline const Vector3D operator-(const Vector3D & Vec)
{
  Vector3D NewVector = Vec;
  return NewVector *=  -1;
} 

// Vector * Scalar multiplication
/** Scaling a vector by multiplication.
* Usage:  vector * scalar
*/
inline const Vector3D operator*(const Vector3D & RHS, const float scalar)
{
  Vector3D NewVector = RHS;
  return NewVector *= scalar;
}  

// Scalar * Vector multiplication  
/** Scaling a vector by multiplication.
* Usage: scalar * vector
*/
inline const Vector3D operator*(const float scalar, const Vector3D & Other)
{
  return Other * scalar;
}
  
//The binary - operator between 2 vectors
//Could be implemented as   A + (-B)
/** Substraction of two vectors.
*/
inline const Vector3D operator-(const Vector3D & RHS, const Vector3D & LHS)
{
  Vector3D NewVector = RHS;
  return NewVector -= LHS;
}  

//Addition of 2 vectors
/** Addition of two vectors.
*/
inline const Vector3D operator+(const Vector3D & RHS, const Vector3D & LHS)
{
  Vector3D NewVector = RHS;
  return NewVector += LHS;
} 

// Vector * 1 / Scalar
// Could be implemented as Vector * (1 / Scalar)
/** Scaling a vector by division.
*/
inline const Vector3D operator/(const Vector3D & RHS, const float scalar)
{  
  // The non-nullity of the scalar is checked in /=
  
  Vector3D NewVector = RHS;
  return NewVector /= scalar;
}

 

//Vector dot product
/** The dot product of two vectors.
* @param V1 The first vector.
* @param V2 The second vector.
* @return The result is invariant of the order of V1 and V2.
*/
inline const float dot(const Vector3D &V1, const Vector3D &V2)
{
  return V1[0] * V2[0] + V1[1] * V2[1] + V1[2] * V2[2];
}

//Vector cross product
// Convention  X * Y = Z

/**
* The cross product of two vectors.
* @param Left The left hand side argument of the operation.
* @param Right The right hand side argument of the operation.
* @return A constant 3-dimensional vector.
* Convetion: cross(x, y) = z  (Right hand sided coordinate system)
*/
inline const Vector3D cross(const Vector3D &Left, const Vector3D &Right)
{
  Vector3D NewVector;
  NewVector[0] = Left[1] * Right[2] - Left[2] * Right[1];
  NewVector[1] = Left[2] * Right[0] - Left[0] * Right[2];
  NewVector[2] = Left[0] * Right[1] - Left[1] * Right[0];
  return NewVector;
}

inline const Vector3D project(const Vector3D & Left, const Vector3D & Right)
{
  return Right * dot(Left, Right) / dot(Right, Right);
}


// The squared magnintude of the vector
inline const float Vector3D::magn2() const
{ 
  return dot(*this,*this);
}

//The mangintude of the vector
inline const float Vector3D::magn() const
{
  return sqrt(magn2());
}

// Normalizes the vector
inline void Vector3D::normalize()
{
  float magnitude = magn();

  vec[0] /= magnitude;
  vec[1] /= magnitude;
  vec[2] /= magnitude;  
}

// Left shift operator for output to streams  
/** An overload of the shift-left operator
* Outputs the components of the vector to the stream in the form (x, y, z).
* No newline at the end.
*/
inline ostream & operator<<(ostream & os, const Vector3D & Vec)
{
  os << "(" 
     << Vec[0] << ", "
     << Vec[1] << ", "
     << Vec[2] 
     << ")";
  return os;
}  


#endif // VECTOR_HH
