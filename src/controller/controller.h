#ifndef A1_MAZE_CPP_SRC_CONTROLLER_CONTROLLER_H_
#define A1_MAZE_CPP_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/cave.h"
#include "../model/maze.h"
#include "../model/pathfinder.h"

namespace s21 {

// TODO: cave_model_ -> *cave_model_ && maze_model_ -> *maze_model_
class Controller final {
 public:
  std::vector<std::vector<bool>> GetCaveGrip() const noexcept;
  CaveError InitializeCave(const std::string& filename);
  void GenerateRandomCave(const size_t& rows, const size_t& cols,
                          const int& fill_probability);
  CaveError SimulateStep(const size_t& birth_limit,
                         const size_t& death_limit) noexcept;

  MazeError InitializeMaze(const std::string& filename);
  std::vector<Point> FindMazePath(const Point& start, const Point& end);
  void GenerateRandomMaze(const size_t& rows, const size_t& columns) noexcept;
  size_t GetMazeRowsCount() const noexcept;
  size_t GetMazeColumnsCount() const noexcept;
  std::vector<std::vector<bool>> GetMazeHorizontalWalls() const noexcept;
  std::vector<std::vector<bool>> GetMazeVerticalWalls() const noexcept;

 private:
  Cave cave_model_;
  Maze maze_model_;
};

inline CaveError Controller::InitializeCave(const std::string& filename) {
  CaveError return_error = cave_model_.InitializeCave(filename);
  return return_error;
}

inline void Controller::GenerateRandomCave(const size_t& rows,
                                           const size_t& cols,
                                           const int& fill_probability) {
  cave_model_.GenerateRandomCave(rows, cols, fill_probability);
}

inline CaveError Controller::SimulateStep(const size_t& birth_limit,
                                          const size_t& death_limit) noexcept {
  return cave_model_.SimulateStep(birth_limit, death_limit);
}

inline std::vector<std::vector<bool>> Controller::GetCaveGrip() const noexcept {
  return cave_model_.GetGrid();
}

inline MazeError Controller::InitializeMaze(const std::string& filename) {
  return maze_model_.InitializeMaze(filename);
}

inline void Controller::GenerateRandomMaze(const size_t& rows,
                                           const size_t& columns) noexcept {
  maze_model_.SetRandomMaze(rows, columns);
}

inline size_t Controller::GetMazeRowsCount() const noexcept {
  return maze_model_.GetRowsCount();
}
inline size_t Controller::GetMazeColumnsCount() const noexcept {
  return maze_model_.GetColumnsCount();
}
inline std::vector<std::vector<bool>> Controller::GetMazeHorizontalWalls()
    const noexcept {
  return maze_model_.GetHorizontalWalls();
}
inline std::vector<std::vector<bool>> Controller::GetMazeVerticalWalls()
    const noexcept {
  return maze_model_.GetVerticalWalls();
}

inline std::vector<Point> Controller::FindMazePath(const Point& start,
                                                   const Point& end) {
  return PathFinder::FindPath(maze_model_, start, end);
}

}  // namespace s21

#endif  // A1_MAZE_CPP_SRC_CONTROLLER_CONTROLLER_H_
