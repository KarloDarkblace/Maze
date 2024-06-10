#include <gtest/gtest.h>

#include "../controller/controller.h"

TEST(CaveTest, InitializeCave_Success) {
  s21::Controller controller;
  ASSERT_EQ(controller.InitializeCave("objects/caves/cave1.txt"),
            s21::CaveError::kOk);
}

TEST(CaveTest, InitializeCave_FileOpenError) {
  s21::Controller controller;
  ASSERT_EQ(controller.InitializeCave("invalid_path.txt"),
            s21::CaveError::kFileOpen);
}

TEST(CaveTest, GenerateRandomCave) {
  s21::Controller controller;
  size_t rows = 10, cols = 10;
  int fill_probability = 50;
  controller.GenerateRandomCave(rows, cols, fill_probability);
  auto grid = controller.GetCaveGrip();

  ASSERT_EQ(grid.size(), rows);
  ASSERT_EQ(grid[0].size(), cols);
  bool has_filled = false, has_empty = false;
  for (const auto& row : grid) {
    for (bool cell : row) {
      if (cell)
        has_filled = true;
      else
        has_empty = true;
    }
  }
  ASSERT_TRUE(has_filled && has_empty);
}

TEST(CaveTest, SimulateStep) {
  s21::Controller controller;
  size_t rows = 5, cols = 5;
  int fill_probability = 75;
  controller.GenerateRandomCave(rows, cols, fill_probability);
  auto initial_grid = controller.GetCaveGrip();
  auto error = controller.SimulateStep(4, 1);
  auto new_grid = controller.GetCaveGrip();

  ASSERT_EQ(error, s21::CaveError::kOk);

  bool state_changed = false;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (initial_grid[i][j] != new_grid[i][j]) {
        state_changed = true;
        break;
      }
    }
    if (state_changed)
      break;
  }

  ASSERT_TRUE(state_changed);
}

TEST(CaveTest, GenerateEmptyCave) {
  s21::Controller controller;
  size_t rows = 5, cols = 5;
  int fill_probability = 0;
  controller.GenerateRandomCave(rows, cols, fill_probability);
  auto grid = controller.GetCaveGrip();

  bool is_empty = true;
  for (const auto& row : grid) {
    for (bool cell : row) {
      if (cell) {
        is_empty = false;
        break;
      }
    }
    if (!is_empty)
      break;
  }
  ASSERT_TRUE(is_empty);
}

TEST(CaveTest, ZeroSizeCave) {
  s21::Controller controller;
  size_t rows = 0, cols = 0;
  int fill_probability = 50;
  controller.GenerateRandomCave(rows, cols, fill_probability);
  auto grid = controller.GetCaveGrip();

  ASSERT_TRUE(grid.empty());
}
