#pragma once

#include <vector>

std::vector<std::vector<int>> random_Num_map(int row, int col);

std::vector<std::vector<int>> regular_Num_map(int row, int col,
                                              int object_size);

std::vector<std::vector<int>> map_enlarge(std::vector<std::vector<int>> map,
                                          int n);