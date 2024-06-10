#include <gtest/gtest.h>

#include <chrono>

#include "../controller/controller.h"

TEST(PathFinderTest, FindPathInSimpleMaze) {
  s21::Controller controller;
  controller.GenerateRandomMaze(5, 5);
  s21::Point start(0, 0), end(4, 4);
  auto path = controller.FindMazePath(start, end);

  ASSERT_FALSE(path.empty());
  ASSERT_EQ(path.front(), start);
  ASSERT_EQ(path.back(), end);
}

TEST(PathFinderTest, PerformanceTest) {
  s21::Controller controller;
  controller.GenerateRandomMaze(50, 50);
  s21::Point start(0, 0), end(49, 49);
  auto start_time = std::chrono::high_resolution_clock::now();
  auto path = controller.FindMazePath(start, end);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);

  std::cout << "Path finding took " << duration.count() << " milliseconds."
            << std::endl;
}
