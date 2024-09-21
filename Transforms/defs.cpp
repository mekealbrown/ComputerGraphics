

#include "transforms.hpp"


void pop_vec(std::vector<float>& vec, const float x, const float y)
{
  vec.push_back(x);
  vec.push_back(y);
  vec.push_back(1.0);
}

//TODO: ADD BOX COMMENT
std::vector<float> matrixMultiply(const std::vector<std::vector<float>>& mx_1, const std::vector<float>& mx_2)
{
  std::vector<float> new_vec;
  for(int i = 0; i < 3; i++) {
    float val = 0.0;
    for(int j = 0; j < 3; j++) {
      val += mx_1[i][j] * mx_2[j];
    }
    new_vec.push_back(val);
  }

  return new_vec;
}

//TODO: ADD BOX COMMENT
std::vector<float> translate(const float x, const float y, const float x_off, const float y_off)
{
  std::vector<std::vector<float>> matrix = {
    {1, 0, x_off},
    {0, 1, y_off},
    {0, 0, 1}
  };

  std::vector<float> vec;
  pop_vec(vec, x, y);

  return matrixMultiply(matrix, vec);
}

//TODO: ADD BOX COMMENT
std::vector<float> rotate(float x, float y, float angle) //degrees to radians??
{
  std::vector<std::vector<float>> matrix = {
    {cosf(angle), -(sinf(angle)), 0},
    {sinf(angle), cosf(angle), 0},
    {0, 0, 1}
  };
  std::vector<float> vec;
  pop_vec(vec, x, y);

  return matrixMultiply(matrix, vec);
}

//TODO: ADD BOX COMMENT
std::vector<float> scale(const float x, const float y, const float x_sfact, const float y_sfact)
{
  std::vector<std::vector<float>> matrix = {
    {x_sfact, 0, 0},
    {0, y_sfact, 0},
    {0, 0, 1}
  };

  std::vector<float> vec;
  pop_vec(vec, x, y);

  return matrixMultiply(matrix, vec);
}


//TODO: ADD BOX COMMENT
void display_result(const std::vector<float>& vec)
{
  std::cout << "\nNew X coordinate --- " << std::setprecision(6) << vec[0] << "\n";
  std::cout << "New Y coordinate --- " << std::setprecision(6) << vec[1] << "\n";
}