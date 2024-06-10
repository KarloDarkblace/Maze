#ifndef A1_MAZE_CPP_SRC_MODEL_MAZE_H_
#define A1_MAZE_CPP_SRC_MODEL_MAZE_H_

#include <cstddef>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

constexpr int kMaxOfMaze = 50;

enum class MazeError {
  kOk = 0,
  kFileOpen = 1,
  kFileRead = 2,
  kOutOfMaximum = 3
};

class Maze final {
 public:
  MazeError InitializeMaze(const std::string& filename);
  void SetRandomMaze(const size_t& rows, const size_t& columns) noexcept;

 public:
  size_t GetRowsCount() const noexcept { return rows_; };
  size_t GetColumnsCount() const noexcept { return cols_; };
  std::vector<std::vector<bool>> GetHorizontalWalls() const noexcept {
    return horizontal_walls_;
  };
  std::vector<std::vector<bool>> GetVerticalWalls() const noexcept {
    return vertical_walls_;
  };

 private:
  unsigned int CountSet(const size_t& num) noexcept;
  unsigned int CountHorizontalWalls(const size_t& index,
                                    const size_t& set) noexcept;
  bool GetRandomBool() const noexcept;
  void EndGenerate(size_t& count) noexcept;
  void GenerateRandomMaze() noexcept;
  void FillingSet(size_t& count) noexcept;
  void DuplicateSet(const size_t& current_row) noexcept;
  void MergeSet(const size_t& index, const size_t& new_set) noexcept;
  void AddVerticalWall(const size_t& current_row) noexcept;
  void AddHorizontalWall(const size_t& current_row) noexcept;
  void CheckHorizontalWalls(const size_t& current_row) noexcept;
  void CleanMaze() noexcept;
  MazeError ParsingFile(std::ifstream& filestream);
  MazeError ReadVerticalWalls(std::ifstream& filestream);
  MazeError ReadHorizontalWalls(std::ifstream& filestream);

 private:
  size_t rows_ = 0, cols_ = 0;
  std::vector<std::vector<bool>> horizontal_walls_;
  std::vector<std::vector<bool>> vertical_walls_;
  std::vector<size_t> side_line_;
};

}  // namespace s21

#endif  // A1_MAZE_CPP_SRC_MODEL_MAZE_H_
