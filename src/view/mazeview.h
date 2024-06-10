#ifndef MAZEVIEW_H
#define MAZEVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>

#include "../controller/controller.h"

class MazeView : public QGraphicsView {
  Q_OBJECT

 public:
  MazeView(QWidget* parent = nullptr);

 public:
  void setPath(const std::vector<s21::Point>& points) noexcept;
  void setController(const s21::Controller& controller) noexcept;

 private:
  void drawMaze() noexcept;
  void drawPath() noexcept;

 private:
  const int kMargin = 5;
  const int kPenWidth = 2;

 private:
  s21::Controller controller_;
  std::vector<s21::Point> path_;
};

#endif  // MAZEVIEW_H
