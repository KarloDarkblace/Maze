#include <gtest/gtest.h>

#include "../controller/controller.h"

TEST(MazeTest, InitializeMaze_Success) {
  s21::Controller controller;
  ASSERT_EQ(controller.InitializeMaze("objects/mazes/maze1.txt"),
            s21::MazeError::kOk);
}

TEST(MazeTest, InitializeMaze_FileOpenError) {
  s21::Controller controller;
  ASSERT_EQ(controller.InitializeMaze("invalid_path.txt"),
            s21::MazeError::kFileOpen);
}

TEST(MazeTest, GenerateRandomMaze) {
  s21::Controller controller;
  size_t rows = 5, cols = 5;
  controller.GenerateRandomMaze(rows, cols);
  ASSERT_EQ(controller.GetMazeRowsCount(), rows);
  ASSERT_EQ(controller.GetMazeColumnsCount(), cols);

  auto hWalls = controller.GetMazeHorizontalWalls();
  auto vWalls = controller.GetMazeVerticalWalls();
  ASSERT_EQ(hWalls.size(), rows);
  ASSERT_EQ(vWalls.size(), rows);

  bool hasTrue = false, hasFalse = false;
  for (const auto& row : hWalls) {
    for (bool wall : row) {
      if (wall)
        hasTrue = true;
      else
        hasFalse = true;
    }
    if (hasTrue && hasFalse)
      break;
  }
  ASSERT_TRUE(hasTrue && hasFalse);
}

TEST(MazeTest, GetHorizontalWalls) {
  s21::Controller controller;
  controller.GenerateRandomMaze(10, 10);
  auto walls = controller.GetMazeHorizontalWalls();
  ASSERT_EQ(static_cast<int>(walls.size()), 10);
}

TEST(MazeTest, GetVerticalWalls) {
  s21::Controller controller;
  controller.GenerateRandomMaze(10, 10);
  auto walls = controller.GetMazeVerticalWalls();
  ASSERT_EQ(static_cast<int>(walls.size()), 10);
}
