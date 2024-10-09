#pragma once

#include <vector>

void pop_vec(std::vector<float>&, const float, const float);

std::vector<float> matrixMultiply(const std::vector<std::vector<float>>&, const std::vector<float>&);

std::vector<float> translate(const float, const float, const float, const float);

std::vector<float> rotate(float, float, float);

std::vector<float> scale(const float, const float, const float, const float);

void display_result(const std::vector<float>&);