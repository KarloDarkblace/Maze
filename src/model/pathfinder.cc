#include "pathfinder.h"

#include <iostream>

namespace s21 {

bool PathFinder::IsWallBetween(const Maze& maze, const Point& first,
                               const Point& second) {
  if (std::abs(first.x - second.x) + std::abs(first.y - second.y) != 1) {
    return false;
  }
  if (first.x + 1 == second.x) {
    return maze.GetVerticalWalls()[first.y][first.x];
  } else if (first.y + 1 == second.y) {
    return maze.GetHorizontalWalls()[first.y][first.x];
  } else if (first.x - 1 == second.x) {
    return maze.GetVerticalWalls()[second.y][second.x];
  } else if (first.y - 1 == second.y) {
    return maze.GetHorizontalWalls()[second.y][second.x];
  }
  return false;
}

std::vector<Point> PathFinder::GetNeighbors(const Maze& maze,
                                            const Point& current) {
  std::vector<Point> neighbors;

  if (current.x > 0 &&
      !IsWallBetween(maze, current, Point(current.x - 1, current.y))) {
    neighbors.push_back(Point(current.x - 1, current.y));
  }
  if (current.x < static_cast<int>(maze.GetColumnsCount()) - 1 &&
      !IsWallBetween(maze, current, Point(current.x + 1, current.y))) {
    neighbors.push_back(Point(current.x + 1, current.y));
  }
  if (current.y > 0 &&
      !IsWallBetween(maze, current, Point(current.x, current.y - 1))) {
    neighbors.push_back(Point(current.x, current.y - 1));
  }
  if (current.y < static_cast<int>(maze.GetRowsCount()) - 1 &&
      !IsWallBetween(maze, current, Point(current.x, current.y + 1))) {
    neighbors.push_back(Point(current.x, current.y + 1));
  }

  return neighbors;
}

int PathFinder::Heuristic(const Point& a, const Point& b) {
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Point> PathFinder::ReconstructPath(AStarNode* node) {
  std::vector<Point> path;
  for (AStarNode* current_node = node; current_node != nullptr;
       current_node = current_node->parent) {
    path.push_back(current_node->position);
  }
  std::reverse(path.begin(), path.end());
  return path;
}

std::vector<Point> PathFinder::FindPath(const Maze& maze, const Point& start,
                                        const Point& end) {

  std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<>>
      open_set;
  std::unordered_map<Point, AStarNode*, Point::Hash> all_nodes;
  std::unordered_map<Point, bool, Point::Hash> closed_set;

  AStarNode* start_node = new AStarNode(start);
  start_node->g_cost = 0;
  start_node->h_cost = Heuristic(start, end);
  open_set.push(*start_node);
  all_nodes[start] = start_node;

  while (!open_set.empty()) {
    AStarNode current_node = open_set.top();
    open_set.pop();

    if (current_node.position == end) {
      std::vector<Point> path = ReconstructPath(&current_node);
      for (auto& node : all_nodes)
        delete node.second;
      return path;
    }

    closed_set[current_node.position] = true;

    for (const Point& neighbor : GetNeighbors(maze, current_node.position)) {
      if (closed_set.count(neighbor))
        continue;

      int tentative_g_cost = current_node.g_cost + 1;
      if (!all_nodes.count(neighbor) ||
          tentative_g_cost < all_nodes[neighbor]->g_cost) {
        AStarNode* neighbor_node =
            new AStarNode(neighbor, all_nodes[current_node.position]);
        neighbor_node->g_cost = tentative_g_cost;
        neighbor_node->h_cost = Heuristic(neighbor, end);
        open_set.push(*neighbor_node);
        delete all_nodes[neighbor];
        all_nodes[neighbor] = neighbor_node;
      }
    }
  }

  for (auto& node : all_nodes)
    delete node.second;
  return std::vector<Point>();
}

}  // namespace s21
