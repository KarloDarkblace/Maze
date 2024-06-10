#include "caveview.h"

CaveView::CaveView(QWidget* parent) : QGraphicsView(parent) {
  QGraphicsScene* scene = new QGraphicsScene(this);
  this->setScene(scene);
  this->scene()->setSceneRect(kMargin, kMargin, 500, 500);
}

void CaveView::displayCave(const std::vector<std::vector<bool>>& caveGrid) {
  scene()->clear();
  int rows = caveGrid.size();
  int cols = caveGrid[0].size();
  qreal cellWidth = scene()->width() / rows;
  qreal cellHeight = scene()->height() / cols;

  QPen pen(Qt::NoPen);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      QColor color = caveGrid[i][j] ? Qt::black : Qt::white;
      QGraphicsRectItem* rect =
          scene()->addRect(j * cellWidth, i * cellHeight, cellWidth, cellHeight,
                           pen, QBrush(color));
      rect->setPos(kMargin, kMargin);
    }
  }
}
