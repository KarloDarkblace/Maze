#ifndef A1_MAZE_CPP_SRC_MODEL_CAVE_H_
#define A1_MAZE_CPP_SRC_MODEL_CAVE_H_

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

namespace s21 {

enum class CaveError {
  kError = -1,
  kOk = 0,
  kFileOpen = 1,
  kFileRead = 2,
  kOutOfMaximum = 3,
  kEndSimulate = 4,
  kErrorSimulate = 5
};

class Cave final {
 public:
  Cave();

 public:
  CaveError InitializeCave(const std::string& filename);
  void GenerateRandomCave(const size_t& rows, const size_t& cols,
                          const int& fill_probability);
  CaveError SimulateStep(const size_t& birth_limit,
                         const size_t& death_limit) noexcept;

 public:
  std::vector<std::vector<bool>> GetGrid() const noexcept { return grid_; }

 private:
  bool IsStable(const std::vector<std::vector<bool>>& old_grid,
                const std::vector<std::vector<bool>>& new_grid);
  bool ShouldCellLive(const bool& currently_alive, const int& live_neighbors);
  int CountLiveNeighbors(const size_t& x, const size_t& y);
  void ClearCave();

 private:
  size_t rows_, cols_;
  int birth_limit_, death_limit_;
  std::vector<std::vector<bool>> grid_;
};

}  // namespace s21

#endif  // A1_MAZE_CPP_SRC_MODEL_S21_CAVE_H_
