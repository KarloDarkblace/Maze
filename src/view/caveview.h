#ifndef CAVEVIEW_H
#define CAVEVIEW_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>

class CaveView : public QGraphicsView {
  Q_OBJECT

 public:
  CaveView(QWidget* parent = nullptr);

 public:
  void displayCave(const std::vector<std::vector<bool>>& caveGrid);

 private:
  const int kMargin = 5;
};

#endif  // CAVEVIEW_H
