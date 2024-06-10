#ifndef CAVEWINDOW_H
#define CAVEWINDOW_H

#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QWidget>

#include "../controller/controller.h"

namespace Ui {
class CaveWindow;
}

class CaveWindow : public QWidget {
  Q_OBJECT

 public:
  explicit CaveWindow(QWidget* parent = nullptr);
  ~CaveWindow();

 signals:
  void windowClosed();
  void caveWindowHidden();

 protected:
  void closeEvent(QCloseEvent* event) override;

 private slots:
  void on_selectFileQPushButton_clicked();
  void on_generateCaveQPushButton_clicked();
  void on_nextStepQPushButton_clicked();
  void on_startQPushButton_clicked();
  void on_mazeSelectQPushButton_clicked();

 private:
  void updateDisplay();
  void handleFileSelection();
  void startOrStopSimulation();

 private:
  s21::Controller controller_;
  Ui::CaveWindow* ui_;
  QTimer* timer_;
};

#endif  // CAVEWINDOW_H
