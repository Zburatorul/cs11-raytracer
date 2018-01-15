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
* @file color.hh Color class implementation and several operator overloads.
*/


#ifndef COLOR_HH
#define COLOR_HH


#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;


/** An RGB color class.
*/
class Color
{
 private:
 
 /**
  * The vector used for storing the color magnitudes.
  * vec[0] == RED \n
  * vec[1] == GREEN
  * vec[2] == BLUE
  * All magnitudes are supposed to be in the interval [0,1]
  */
  float vec[3];
  
 public:
 
  //Constructors
  /** The default constructor.
  * Initializes color components to 0 (zero).
  */
  Color();
  
  /** A constructor that initilizes the color by components.
  * @param R The red component.
  * @param G The green component.
  * @param B The blue component.
  */
  Color(float R, float G, float B);
  Color(float * vec_);
  
  //Compound operators  
  /** The += operator overload.
  * @param Other The right hand argument.
  */
  Color & operator+=(const Color & Other);

  /** The -= operator overload.
  * @param Other The right hand argument.
  */
  Color & operator-=(const Color & Other);

  /** The *= operator overload.
  * @param Other The right hand argument.
  * Does a component-wise multiplication.
  */
  Color & operator*=(const Color & Other);

  /** The *= operator overload.
  * @param scalar The degree by which the colors are to be magnified.
  */
  Color & operator*=(const float scalar);
 

  
  //Accessors 
  /** Accessor to the red color component. */
  const float get_red() const;

  /** Accessor to the green color component. */
  const float get_green() const;

  /** Accessor to the blue color component. */
  const float get_blue() const;
  
  //Mutators
  /** Mutator of the red color component. 
  * @param val Should be in the [0,1] interval.
  */
  void set_red(float val);

  /** Mutator of the green color component. 
  * @param val Should be in the [0,1] interval.
  */
  void set_green(float val);

  /** Mutator of the blue color component. 
  * @param val Should be in the [0,1] interval.
  */
  void set_blue(float val);
  

};

//Default constructor
inline Color::Color()
{
  vec[0] = 0;
  vec[1] = 0;
  vec[2] = 0;
}


inline Color::Color(float * vec_)
{
  vec[0] = vec_[0];
  vec[1] = vec_[1];
  vec[2] = vec_[2];
}


//Costructor with basic initialization by components
//Initialization with other color not implemented due to a priori support
inline Color::Color(float R, float G, float B)
{
  vec[0] = R;
  vec[1] = G;
  vec[2] = B;
}

// Compound addition, supports chaining
inline Color & Color::operator+=(const Color & Other)
{
  vec[0] += Other.get_red();
  vec[1] += Other.get_green();
  vec[2] += Other.get_blue();
  
  return *this;
}

// Compound -, supports chaining
inline Color & Color::operator-=(const Color & Other)
{
  vec[0] -= Other.get_red();
  vec[1] -= Other.get_green();
  vec[2] -= Other.get_blue();
  
  // Check that colors are positive
  //assert(vec[0] >= 0);
  //assert(vec[1] >= 0);
  //assert(vec[2] >= 0);
  
  return *this;
}

// Compound multiplication, supports chaining
inline Color & Color::operator*=(const Color & Other)
{
  vec[0] *= Other.get_red();
  vec[1] *= Other.get_green();
  vec[2] *= Other.get_blue();
  
  return *this;
}

// Compound multiplication with a (float) scalar, supports chaining
inline Color & Color::operator*=(const float scalar)
{ 
  //assert(scalar > 0);
  
  vec[0] *= scalar;
  vec[1] *= scalar;
  vec[2] *= scalar;
  
  return *this;
}



inline const float Color::get_red() const
{
  return vec[0];
}

inline const float Color::get_green() const
{
  return vec[1];
}

inline const float Color::get_blue() const
{
  return vec[2];
}

inline void Color::set_red(float val)
{ 
  //assert(val >= 0);   // Disallow negative values
  vec[0] = val;
}

inline void Color::set_green(float val)
{ 
  //assert(val >= 0);   // Disallow negative values
  vec[1] = val;
}

inline void Color::set_blue(float val)
{ 
  //assert(val >= 0);   // Disallow negative values
  vec[2] = val;
}




// OPERATIONS/OPERATORS WITH COLORS
/** Component-wise addition of two colors */
inline const Color operator+(const Color & RHS, const Color & LHS)
{
  Color NewColor = RHS;
  return NewColor += LHS;
}

/** Component-wise subtraction of two colors */
inline const Color operator-(const Color & RHS, const Color & LHS)
{
  Color NewColor = RHS;
  return NewColor -= LHS;
}

/** Component-wise multiplication of two colors */
inline const Color operator*(const Color & RHS, const Color & LHS)
{
  Color NewColor = RHS;
  return NewColor *= LHS;
}


/** Componentwise multiplication of color by a scalar */
inline const Color operator*(float scalar, const Color & LHS)
{ 
  Color NewColor = LHS;
  return NewColor *= scalar;
}

/** Left shift operator for output to streams in the (R, G, B) form. */
inline ostream & operator<<(ostream & os, const Color & Clr)
{
  os << "(" 
     << Clr.get_red()   << ","
     << Clr.get_green() << ","
     << Clr.get_blue()
     << ")";
  return os;
}  



#endif //COLOR_HH

