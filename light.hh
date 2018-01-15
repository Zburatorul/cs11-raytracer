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
* @file light.hh Light class implementation.
*/

#ifndef LIGHT_HH
#define LIGHT_HH


/** An implementation of a light source.
*/
class Light
{
private:

/** The position of the light source */
  Vector3D Position;

/** The color of the light. */
  Color LightColor;

public:

/** The only constructor.
* @param Position_ The position of the light source in 3D.
* @param LightColor_ The color of the light.
*/
  Light(const Vector3D & Position_, const Color & LightColor_);

/** An accessor for the position of the light source */
  const Vector3D getPosition() const;

/** An accessor for the color of the light */
  const Color getColor() const;

};

inline Light::Light(const Vector3D & Position_, const Color & LightColor_)
{
  Position = Position_;
  LightColor = LightColor_;
}

inline const Vector3D Light::getPosition() const
{
  return Position;
}

inline const Color Light::getColor() const
{
  return LightColor;
}

//LIGHT_HH
#endif

