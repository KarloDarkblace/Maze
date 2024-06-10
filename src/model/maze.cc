#include "maze.h"

#include <cstddef>
#include <vector>

namespace s21 {

bool Maze::GetRandomBool() const noexcept {
  return std::rand() % 2;
}

void Maze::SetRandomMaze(const size_t& rows, const size_t& columns) noexcept {
  std::srand(static_cast<unsigned int>(time(nullptr)));
  rows_ = rows;
  cols_ = columns;
  horizontal_walls_ =
      std::vector<std::vector<bool>>(rows_, std::vector<bool>(cols_, false));
  vertical_walls_ =
      std::vector<std::vector<bool>>(rows_, std::vector<bool>(cols_, false));
  side_line_ = std::vector<size_t>(columns);
  GenerateRandomMaze();
}

void Maze::GenerateRandomMaze() noexcept {
  size_t sets_count = 1;
  for (size_t i = 0; i < rows_ - 1; ++i) {
    FillingSet(sets_count);
    AddVerticalWall(i);
    AddHorizontalWall(i);
    CheckHorizontalWalls(i);
    DuplicateSet(i);
  }
  EndGenerate(sets_count);
}

void Maze::FillingSet(size_t& count) noexcept {
  side_line_.resize(cols_);
  for (size_t i = 0; i < cols_; ++i) {
    if (side_line_[i] == 0) {
      side_line_[i] = count++;
    }
  }
}

void Maze::AddVerticalWall(const size_t& current_row) noexcept {
  for (size_t i = 0; i < cols_ - 1; ++i) {
    bool choise = GetRandomBool();

    if (choise == true || side_line_[i] == side_line_[i + 1]) {
      vertical_walls_[current_row][i] = true;
    } else {
      MergeSet(i, side_line_[i]);
    }
  }
  vertical_walls_[current_row][cols_ - 1] = true;
}

void Maze::MergeSet(const size_t& index, const size_t& new_set) noexcept {
  size_t old_set = side_line_[index + 1];
  for (size_t i = 0; i < cols_; ++i) {
    if (side_line_[i] == old_set) {
      side_line_[i] = new_set;
    }
  }
}

void Maze::AddHorizontalWall(const size_t& current_row) noexcept {
  for (size_t i = 0; i < cols_; i++) {
    bool choise = GetRandomBool();
    if (CountSet(side_line_[i]) != 1 && choise == true) {
      horizontal_walls_[current_row][i] = true;
    }
  }
}

void Maze::CheckHorizontalWalls(const size_t& current_row) noexcept {
  for (size_t i = 0; i < cols_; i++) {
    if (CountHorizontalWalls(current_row, side_line_[i]) == 0) {
      horizontal_walls_[current_row][i] = false;
    }
  }
}

void Maze::DuplicateSet(const size_t& current_row) noexcept {
  for (size_t i = 0; i < cols_; ++i) {
    if (horizontal_walls_[current_row][i] == true) {
      side_line_[i] = 0;
    }
  }
}

unsigned int Maze::CountSet(const size_t& num) noexcept {
  unsigned int count = 0;
  for (size_t i = 0; i < cols_; ++i) {
    if (side_line_[i] == num) {
      count++;
    }
  }
  return count;
}

void Maze::EndGenerate(size_t& count) noexcept {
  FillingSet(count);
  AddVerticalWall(rows_ - 1);

  for (size_t i = 0; i < cols_ - 1; ++i) {
    if (side_line_[i] != side_line_[i + 1]) {
      vertical_walls_[rows_ - 1][i] = false;
      MergeSet(i, side_line_[i]);
    }
  }

  for (size_t i = 0; i < cols_; ++i) {
    horizontal_walls_[rows_ - 1][i] = true;
  }
}

unsigned int Maze::CountHorizontalWalls(const size_t& index,
                                        const size_t& set) noexcept {
  unsigned int countHorizontalWalls = 0;
  for (size_t i = 0; i < cols_; ++i) {
    if (side_line_[i] == set && horizontal_walls_[index][i] == false) {
      countHorizontalWalls++;
    }
  }
  return countHorizontalWalls;
}

MazeError Maze::InitializeMaze(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    return MazeError::kFileOpen;
  }
  CleanMaze();

  MazeError error_return = ParsingFile(file);

  return error_return;
}

MazeError Maze::ParsingFile(std::ifstream& filestream) {
  std::string line;
  MazeError MazeError = MazeError::kOk;

  if (!(filestream >> rows_ >> cols_)) {
    MazeError = MazeError::kFileRead;
  } else if (rows_ > kMaxOfMaze || cols_ > kMaxOfMaze) {
    MazeError = MazeError::kOutOfMaximum;
  } else {
    filestream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    horizontal_walls_ =
        std::vector<std::vector<bool>>(rows_, std::vector<bool>(cols_, false));
    vertical_walls_ =
        std::vector<std::vector<bool>>(rows_, std::vector<bool>(cols_, false));

    if ((MazeError = ReadVerticalWalls(filestream)) == MazeError::kOk) {
      MazeError = ReadHorizontalWalls(filestream);
    }
  }

  return MazeError;
}

MazeError Maze::ReadVerticalWalls(std::ifstream& filestream) {
  std::string line;
  MazeError MazeError = MazeError::kOk;

  for (size_t i = 0; i < rows_ && MazeError == MazeError::kOk; ++i) {
    if (!std::getline(filestream, line)) {
      MazeError = MazeError::kFileRead;
    } else {
      std::istringstream iss(line);
      for (size_t j = 0; j < cols_; ++j) {
        int wall;
        if (!(iss >> wall)) {
          MazeError = MazeError::kFileRead;
          break;
        }
        vertical_walls_[i][j] = (wall != 0);
      }
    }
  }

  return MazeError;
}

MazeError Maze::ReadHorizontalWalls(std::ifstream& filestream) {
  std::string line;
  MazeError MazeError = MazeError::kOk;

  if (!std::getline(filestream, line) || !line.empty()) {
    MazeError = MazeError::kFileRead;
  }

  for (size_t i = 0; i < rows_ && MazeError == MazeError::kOk; ++i) {
    if (!std::getline(filestream, line)) {
      MazeError = MazeError::kFileRead;
    } else {
      std::istringstream iss(line);

      for (size_t j = 0; j < cols_; ++j) {
        int wall;
        if (!(iss >> wall)) {
          MazeError = MazeError::kFileRead;
          break;
        }

        horizontal_walls_[i][j] = (wall != 0);
      }
    }
  }

  return MazeError;
}

void Maze::CleanMaze() noexcept {
  rows_ = 0;
  cols_ = 0;
  horizontal_walls_.clear();
  vertical_walls_.clear();
}

}  // namespace s21
