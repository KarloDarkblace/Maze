#include "mazeview.h"

MazeView::MazeView(QWidget* parent) : QGraphicsView(parent) {
  QGraphicsScene* scene = new QGraphicsScene(this);
  this->setScene(scene);
  this->scene()->setSceneRect(kMargin, kMargin, 500, 500);
}

void MazeView::setController(const s21::Controller& controller) noexcept {
  controller_ = controller;
  drawMaze();
}

void MazeView::setPath(const std::vector<s21::Point>& points) noexcept {
  path_ = points;
  drawMaze();
  drawPath();
}

void MazeView::drawMaze() noexcept {
  scene()->clear();

  QPen pen(Qt::black, kPenWidth);
  QRectF rect = scene()->sceneRect();

  scene()->addLine(rect.left(), rect.top(), rect.right(), rect.top(), pen);
  scene()->addLine(rect.left(), rect.top(), rect.left(), rect.bottom(), pen);

  auto horizontalWalls = controller_.GetMazeHorizontalWalls();
  auto verticalWalls = controller_.GetMazeVerticalWalls();

  qreal cellWidth = rect.width() / controller_.GetMazeColumnsCount();
  qreal cellHeight = rect.height() / controller_.GetMazeRowsCount();

  for (size_t i = 0; i < controller_.GetMazeRowsCount(); ++i) {
    for (size_t j = 0; j < controller_.GetMazeColumnsCount(); ++j) {
      qreal x = j * cellWidth + kMargin;
      qreal y = i * cellHeight + kMargin;

      if (verticalWalls[i][j]) {
        scene()->addLine(x + cellWidth, y, x + cellWidth, y + cellHeight, pen);
      }

      if (horizontalWalls[i][j]) {
        scene()->addLine(x, y + cellHeight, x + cellWidth, y + cellHeight, pen);
      }
    }
  }
}

void MazeView::drawPath() noexcept {
  if (path_.empty())
    return;
  QPen pen(Qt::red, kPenWidth);
  QBrush brush(Qt::red);
  QRectF rect = scene()->sceneRect();

  qreal cellWidth = rect.width() / controller_.GetMazeColumnsCount();
  qreal cellHeight = rect.height() / controller_.GetMazeRowsCount();

  for (size_t i = 1; i < path_.size(); ++i) {
    qreal x1 = path_[i - 1].x * cellWidth + cellWidth / 2 + kMargin;
    qreal y1 = path_[i - 1].y * cellHeight + cellHeight / 2 + kMargin;
    qreal x2 = path_[i].x * cellWidth + cellWidth / 2 + kMargin;
    qreal y2 = path_[i].y * cellHeight + cellHeight / 2 + kMargin;

    scene()->addLine(x1, y1, x2, y2, pen);
  }

  qreal startX = path_.front().x * cellWidth + cellWidth / 2 + kMargin;
  qreal startY = path_.front().y * cellHeight + cellHeight / 2 + kMargin;
  scene()->addEllipse(startX - kPenWidth * 2, startY - kPenWidth * 2,
                      kPenWidth * 4, kPenWidth * 4, pen, brush);

  qreal endX = path_.back().x * cellWidth + cellWidth / 2 + kMargin;
  qreal endY = path_.back().y * cellHeight + cellHeight / 2 + kMargin;
  scene()->addEllipse(endX - kPenWidth * 2, endY - kPenWidth * 2, kPenWidth * 4,
                      kPenWidth * 4, pen, brush);
}
