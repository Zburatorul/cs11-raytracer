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
@file parser.cc Contains the parsing algorithm
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <exception>
#include <vector>
#include <stdexcept>

#include "scene.hh"
#include "scene_objects/objects.hh"
#include "boost/shared_ptr.hpp"

using namespace std;


void readFloats(istream &strm, float vec[]);
float  readOneFloat(istream &strm);


void Trim(string &str)
{
   // trim leading whitespace
   string::size_type  notwhite = str.find_first_not_of(" \t\n");
   str.erase(0,notwhite);

   // trim trailing whitespace
   notwhite = str.find_last_not_of(" \t\n"); 
   str.erase(notwhite+1); 
}


string getNextTag(istream & strm)
{
 string s;
 char tag[50];

 strm.getline(tag, 50, '>');
 s = tag;  s+= ">";
 Trim(s);

 cout << "\t tag= " << s << endl;

  //TODO: Convert to  lower/uppercase
 return s;
}



Camera * readCamera(istream &strm)
{
 string s;
 float vec[3];
 bool data[4];

 Vector3D Position, LookAt, Up;
 float fov;

 s = getNextTag(strm);

 while((s != "</camera>") && strm)
 {

 if (s == "<position>") 
  {
  readFloats(strm, vec);
  Position = Vector3D(vec);
  data[0] = true;
  }

 if (s == "<up>") 
  {
  readFloats(strm,vec);
  Up = Vector3D(vec);
  data[2] = true;
  }

 if (s == "<lookat>") 
 {
  readFloats(strm, vec);
  LookAt = Vector3D(vec);
  data[1] = true;
 }

 if (s == "<fieldofview>") 
 { 
  fov = readOneFloat(strm);
  data[3] = true;
 }

 //This will take care of the closing tag too,
 //even though its not really needed.
 s = getNextTag(strm);
}

for (int i =0; i < 4; i++)
{
 if (!data[i]) 
 {
  cerr << "Not enough information about the Camera Object\n"
       << "Missing field number " << i << endl;
  assert(false); 
 }
}

return new Camera(Position, LookAt, Up, fov);
}



Light * readLight(istream &strm)
{
 string s;
 char tag[50];
 float vec[3];
 bool data[2];

 Vector3D Position;
 Color Clr;


 s = getNextTag(strm);
 
 while((s != "</light>") && strm)
 {

 if (s == "<position>") 
  {
  readFloats(strm,vec);
  Position = Vector3D(vec);
  data[0] = true;
  }
 if (s == "<color>") 
 {
  readFloats(strm,vec);
  Clr = Color(vec);
  data[1] = true;
 }

 s = getNextTag(strm);
}

for (int i =0; i < 2; i++)
{
 if (!data[i]) 
 {
  cerr << "Not enough information about the Light Object\n"
       << "Missing field number " << i << endl;
  assert(false); 
 }
}
return new Light(Position, Clr);
}




Cube * readCube(istream &strm)
{
 string s;
 char tag[50];
 float vec[3], refl = 0;
 bool data[4];

 Vector3D v1,v2,v3;
 Color Clr;

 s = getNextTag(strm);
 while((s != "</cube>") && strm)
 {

 if (s == "<vertice1>") 
 {
  readFloats(strm,vec);
  v1 = Vector3D(vec);
  data[0] = true;
 }

 if (s == "<vertice2>") 
 {
  readFloats(strm,vec);
  v2 = Vector3D(vec);
  data[1] = true;
 }

 if (s == "<vertice3>") 
 {
  readFloats(strm,vec);
  v3 = Vector3D(vec);
  data[2] = true;
 }

 if (s == "<color>") 
 {
  readFloats(strm,vec);
  Clr = Color(vec);
  data[3] = true;
 }

 if (s == "<reflectivity>") refl = readOneFloat(strm);

  
 s = getNextTag(strm);
}

for (int i =0; i < 4; i++)
{
 if (!data[i]) 
 {
  cerr << "Not enough information about the Cube Object\n"
       << "Missing field number " << i << endl;
  assert(false); 
 }
}

 return new Cube(v1, v2, v3, Clr, refl);
}

Cylinder * readCylinder(istream & strm)
{
 string s;
 char tag[50];
 float vec[3];
 bool data[5];

 Vector3D Center, Orientation;
 Color Clr;
 float radius, refl = 0, height;

 s = getNextTag(strm);
 while(s != "</cylinder>")
 {

 if (s == "<center>") 
 {
  readFloats(strm,vec);
  Center = Vector3D(vec);
  data[0] = true;
 }

 if (s == "<color>") 
 {
  readFloats(strm,vec);
  Clr = Color(vec);
  data[4] = true;
 }
 
 if (s == "<orientation>")
 {
  readFloats(strm, vec);
  Orientation = Vector3D(vec);
  data[1] = true;
 }

 if (s == "<radius>") 
 {
  radius = readOneFloat(strm);
  data[2] = true;
 }
 
 if (s == "<height>") 
 {
  height = readOneFloat(strm);
  data[3] = true;
 }
 
 if (s == "<reflectivity>") refl = readOneFloat(strm);


 s = getNextTag(strm);
}

 for (int i = 0; i < 5; i++)
 {
  if (!data[i]) 
  {
  cerr << "Not enough information about Cylinder Object\n"
       << "Missing field number " << i << endl;
  assert(false); 
  }
 }
  
 cout << "\t HELLLO \n";

 Orientation.normalize();
 return new Cylinder(Center, Orientation, radius, height, Clr, refl);
}

Sphere * readSphere(istream &strm)
{
 string s;
 char tag[50];
 float vec[3];
 bool data[3];

 Vector3D Center;
 Color Clr;
 float radius, refl = 0;

 s = getNextTag(strm);
 while(s != "</sphere>")
 {

 if (s == "<center>") 
 {
  readFloats(strm,vec);
  Center = Vector3D(vec);
  data[0] = true;
 }

 if (s == "<color>") 
 {
  readFloats(strm,vec);
  Clr = Color(vec);
  data[2] = true;
 }

 if (s == "<radius>")
 {
  radius = readOneFloat(strm);
  data[1] = true;
 }

 if (s == "<reflectivity>") refl = readOneFloat(strm);


 s = getNextTag(strm);
}

 for (int i = 0; i < 3; i++)
 {
  if (!data[i]) 
  {
  cerr << "Not enough information about Sphere Object\n"
       << "Missing field number " << i << endl;
  assert(false); 
  }
 }

 return new Sphere(Center, radius, Clr, refl);
}


Plane * readPlane(istream &strm)
{
 cout << "Reading plane ... \n";
 
 string s;
 char tag[50];
 float vec[3];
 bool data[3];

 Vector3D Normal;
 Color Clr;
 float dist = 0, refl = 0;

 s = getNextTag(strm);

 //TODO: Convert to  lower/uppercase
 while((s != "</plane>") && strm)
 {

 if (s == "<normal>") 
 {
  readFloats(strm,vec);
  Normal = Vector3D(vec);
  data[1] = true;
 }
 if (s == "<color>") 
 {
  readFloats(strm,vec);
  Clr = Color(vec);
  data[2] = true;
 }

 if (s == "<distance>")
 { 
  dist = readOneFloat(strm);
  data[0] = true;
 }

 if (s == "<reflectivity>") refl = readOneFloat(strm);

 s = getNextTag(strm);
}
	
 for (int i = 0; i < 3; i++)
 {
  if (!data[i]) 
  {
  cerr << "Not enough information about Cylinder Object\n"
       << "Missing field number " << i << endl;
  assert(false); 
  }
 }

 return new Plane(dist, Normal, Clr, refl);
}



float readOneFloat(istream &strm)
{
 cout << "\t Reading 1 float " << endl;

 //Total length of tag or variable to read.
 unsigned int len = 20;
 float res;
 char tag[len];
 string tmp;


 strm.getline(tag, len, '<');
 tmp = tag;

   try{
    res = atof(tmp.c_str());
   } 
   catch (exception &e)
   { 
     tmp = printf("Argument 1(only) : Float expected at %s", tmp.c_str()); 
     throw invalid_argument(tmp);
   }
 cout << "float= " << res << endl;
 return res;
}


void readFloats(istream &strm, float * vec)
{

 cout << "\t Reading 3 floats " << endl;  

 char ch;
 
 //Total length of tag or variable to read.
 unsigned int len = 20;
 char tag[len];
 string tmp;
 float coord;

for (short int i = 0; i < 3; i++)
  {
   
   if (i < 2) ch = ','; else ch = '<';
   cout << "\t\tTest 1.5=" << ch << endl;
   strm.getline(tag, len, ch);
   tmp = tag;
   //Trim(tmp);

   cout << "\t\tTest 2+"<< i << "=" << tmp << endl;
   try{
   coord = atof(tmp.c_str());
   vec[i] = coord;
   cout << "\t\tTest 3+"<< i << "=" << coord << endl;
   } 
   catch (exception &e)
   { 
     tmp = printf("Argument %i : Float expected at %s", i, tmp.c_str()); 
     throw invalid_argument(tmp);
   }
  }
cout << "floats=(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")" << endl;
}



void readScene(istream & strm, Scene * Sc, Camera ** Cr)
{
string s;

cout << "Parsing analysis\n" ;

while (strm)
{
s = getNextTag(strm);

cout << "TopTag= " << s << endl;


//TODO: Convert to  lower/uppercase
//TODO: Change this to something smarter with less code.
if (s == "<plane>") Sc->AddSceneObject(SPSceneObject(readPlane(strm)));
if (s == "<sphere>") Sc->AddSceneObject(SPSceneObject(readSphere(strm)));
if (s == "<light>") Sc->AddLight(SPLight(readLight(strm))); 
if (s == "<camera>") *Cr = readCamera(strm);
if (s == "<cube>") Sc->AddSceneObject(SPSceneObject(readCube(strm)));
if (s == "<cylinder>") Sc->AddSceneObject(SPSceneObject(readCylinder(strm)));
}

Sc->Describe();
}

