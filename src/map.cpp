#include "map.hpp"
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

std::vector<std::vector<State>> Map::NumtoState() {
  std::vector<std::vector<State>> statemap(row, std::vector<State>(col));
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (Num_map[i][j])
        statemap[i][j] = OBSTACLE;
      else
        statemap[i][j] = EMPTY;
    }
  }
  State_map = statemap;
  return statemap;
}

std::vector<std::vector<State>> Map::StatetoGrid(int size) {
  std::vector<std::vector<State>> gridmap(
      row / grid_size, std::vector<State>(col / grid_size, UNKNOW));
  for (int i = 0; i < row; i++) {
    int x = i / grid_size;
    for (int j = 0; j < col; j++) {
      int y = j / grid_size;
      if (gridmap[x][y] == UNKNOW) {
        if (State_map[i][j] == OBSTACLE)
          gridmap[x][y] = OBSTACLE;
        else
          gridmap[x][y] = EMPTY;
      }
    }
  }
  Grid_map = gridmap;
  return gridmap;
}

std::vector<std::vector<State>> Map::NumtoGrid(int size) {
  NumtoState();
  StatetoGrid(size);
  return Grid_map;
}

void Map::State_change(std::pair<int, int> position, State state) {
  State_map[position.first][position.second] = state;
}

void Map::show() {
  for (int i = 0; i < col; i++) {
    if (i % 10 == 0) {
      std::cout << BLUE << "  " << RESET;
    } else
      std::cout << WHITE << "  " << RESET;
  }
  std::cout << std::endl;

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      switch (State_map[i][j]) {
      case UNKNOW:
      case CLOSED:
      case OPEND:
        break;
      case EMPTY:
        std::cout << WHITE << "  " << RESET;
        break;
      case OBSTACLE:
        std::cout << BLACK << "  " << RESET;
        break;
      case PATH:
        std::cout << GREEN << "  " << RESET;
        break;
      case BEGIN:
      case END:
      case OBJECT:
        std::cout << RED << "  " << RESET;
        break;
      }
    }
    std::cout << std::endl;
  }
}

void Map::updatePath_Statemap(std::vector<std::pair<int, int>> path) {
  for (size_t i; i < path.size(); i++) {
    // if (State_map[path[i].first][path[i].second] == EMPTY)
    State_change(path[i], PATH);
  }
}

void Map::updatePath_Gridmap(std::vector<std::pair<int, int>> Gridpath) {
  std::vector<std::pair<int, int>> path(Gridpath.size());
  for (size_t i; i < path.size(); i++) {
    path[i].first = Gridpath[i].first * grid_size;
    path[i].second = Gridpath[i].second * grid_size;
    State_change(path[i], PATH);
  }
}