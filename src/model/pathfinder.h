#ifndef A1_MAZE_CPP_SRC_MODEL_PATHFINDER_H_
#define A1_MAZE_CPP_SRC_MODEL_PATHFINDER_H_

#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

#include "maze.h"

namespace s21 {

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  struct Hash {
    size_t operator()(const Point& p) const {
      return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
  };
};

class PathFinder final {
 public:
  struct AStarNode {
    Point position;
    int g_cost;
    int h_cost;
    AStarNode* parent;

    AStarNode(Point pos, AStarNode* parent = nullptr)
        : position(pos), g_cost(0), h_cost(0), parent(parent) {}

    int GetFCost() const { return g_cost + h_cost; }

    bool operator>(const AStarNode& other) const {
      return this->GetFCost() > other.GetFCost();
    }
  };

  static std::vector<Point> FindPath(const Maze& maze, const Point& start,
                                     const Point& end);

 private:
  static int Heuristic(const Point& a, const Point& b);
  static std::vector<Point> ReconstructPath(AStarNode* node);
  static std::vector<Point> GetNeighbors(const Maze& maze,
                                         const Point& current);
  static bool IsWallBetween(const Maze& maze, const Point& first,
                            const Point& second);
};

}  // namespace s21

#endif  // A1_MAZE_CPP_SRC_MODEL_PATHFINDER_H_