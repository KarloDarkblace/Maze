#include "cave.h"

namespace s21 {

Cave::Cave() {
  srand(time(NULL));
}

CaveError Cave::InitializeCave(const std::string& filename) {
  ClearCave();

  std::ifstream file(filename);
  if (!file.is_open()) {
    return CaveError::kFileOpen;
  }

  if (!(file >> rows_ >> cols_)) {
    return CaveError::kFileRead;
  }

  if (rows_ > 50 || cols_ > 50) {
    return CaveError::kOutOfMaximum;
  }

  grid_.resize(rows_, std::vector<bool>(cols_, false));
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < cols_; ++j) {
      int cell;
      if (!(file >> cell)) {
        return CaveError::kFileRead;
      }
      grid_[i][j] = (cell == 1);
    }
  }

  return CaveError::kOk;
}

void Cave::GenerateRandomCave(const size_t& rows, const size_t& cols,
                              const int& fill_probability) {
  ClearCave();

  rows_ = rows;
  cols_ = cols;

  grid_.resize(rows_, std::vector<bool>(cols_, false));
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < cols_; ++j) {
      grid_[i][j] = (rand() % 100 < fill_probability);
    }
  }
}

bool Cave::IsStable(const std::vector<std::vector<bool>>& old_grid,
                    const std::vector<std::vector<bool>>& new_grid) {
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < cols_; ++j) {
      if (old_grid[i][j] != new_grid[i][j]) {
        return false;
      }
    }
  }
  return true;
}

CaveError Cave::SimulateStep(const size_t& birth_limit,
                             const size_t& death_limit) noexcept {
  if (rows_ == 0 || cols_ == 0) {
    return CaveError::kErrorSimulate;
  }

  birth_limit_ = birth_limit;
  death_limit_ = death_limit;

  std::vector<std::vector<bool>> new_grid(rows_,
                                          std::vector<bool>(cols_, false));
  bool changed = false;

  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < cols_; ++j) {
      int live_neighbors = CountLiveNeighbors(i, j);
      new_grid[i][j] = ShouldCellLive(grid_[i][j], live_neighbors);
      changed |= (new_grid[i][j] != grid_[i][j]);
    }
  }

  if (!changed) {
    return CaveError::kEndSimulate;
  }

  grid_ = new_grid;
  return CaveError::kOk;
}

int Cave::CountLiveNeighbors(const size_t& x, const size_t& y) {
  int count = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0)
        continue;

      int ni = static_cast<int>(x) + i;
      int nj = static_cast<int>(y) + j;
      if (ni >= 0 && static_cast<size_t>(ni) < rows_ && nj >= 0 &&
          static_cast<size_t>(nj) < cols_) {
        count += grid_[ni][nj];
      } else {
        ++count;
      }
    }
  }
  return count;
}

bool Cave::ShouldCellLive(const bool& currently_alive,
                          const int& live_neighbors) {
  if (currently_alive) {
    return live_neighbors >= birth_limit_ && live_neighbors <= 8;
  } else {
    return live_neighbors >= death_limit_;
  }
}

void Cave::ClearCave() {
  grid_.clear();
  rows_ = 0;
  cols_ = 0;
}

}  // namespace s21
