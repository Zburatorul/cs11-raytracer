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


#include <fstream>
#include "parser.hh"
#include "scene_objects/objects.hh"
#include <memory>
//#include "boost/shared_ptr.hpp"

using namespace std;


int main(int argc, char** argv)
{
  Scene * Sc = new Scene;
  Camera * Cr;
  
  unsigned int imgSize = atoi(argv[1]);
  
  cout << "Trying to read scene description from: " << argv[2] << endl;
  ifstream fin(argv[2]); 
  ofstream file("scene.ppm");
   
  readScene(fin, Sc, & Cr);
  Sc->Render(*Cr, imgSize, file);
 return 0;
}

