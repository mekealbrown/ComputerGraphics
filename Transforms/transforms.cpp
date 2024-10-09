//------------------------------------------------------------------------------
// Developer---Mekeal Brown
// Course------CS3233-01
// Project-----Homework #2
// Due---------September 23, 2024
//
// This program prompts the user for an X and a Y coordinate that define
// a vector. It then prompts for the type of transform desired. The user 
// is then prompted to enter any required data needed to perform the transform.
// The program computes the new coordinates.
//-----------------------------------------------------------------------------
#include <cmath>
#include <iostream>

#include "transforms.hpp"

int main()
{
  float x_coor, y_coor;
  std::cout << "X coordinate ------- ";
  std::cin >> x_coor;

  std::cout << "Y coordinate ------- ";
  std::cin >> y_coor;

  char transform;
  std::cout << "\nChoose (t)ranslate, (r)otate, or (s)cale -- ";
  std::cin >> transform;


  std::vector<float> n_vec; //vector for new coordinates, passed to transform funcs by ref
  switch (transform) {
    case 't': {
      float x_off, y_off;
      std::cout << "\nX offset ----------- ";
      std::cin >> x_off;
      std::cout << "Y offset ----------- ";
      std::cin >> y_off;

      n_vec = translate(x_coor, y_coor, x_off, y_off);
      display_result(n_vec);
      break;
    }
    case 'r':
      float angle;
      std::cout << "\nAngle (degrees) ---- ";
      std::cin >> angle;

      //was using the already defined 'M_PI' constant changed due to rounding issues
      angle = angle * (3.1415926 / 180.0); //convert to rad

      n_vec = rotate(x_coor, y_coor, angle);
      display_result(n_vec);
      break;
    case 's':
      float x_sfact, y_sfact;
      std::cout << "\nX scale factor ----- ";
      std::cin >> x_sfact;
      std::cout << "Y scale factor ----- ";
      std::cin >> y_sfact;

      n_vec = scale(x_coor, y_coor, x_sfact, y_sfact);
      display_result(n_vec);
      break;
    default:
      break;
  }

  return 0;
}
