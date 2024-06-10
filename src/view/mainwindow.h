#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>

#include "../controller/controller.h"
#include "cavewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_selectFileQPushButton_clicked();
  void on_generateMazeQPushButton_clicked();
  void on_xFromCordQSpinBox_valueChanged(int value);
  void on_yFromCordQSpinBox_valueChanged(int value);
  void on_xToCordQSpinBox_valueChanged(int value);
  void on_yToCordQSpinBox_valueChanged(int value);
  void on_caveSelectQPushButton_clicked();

 private:
  void setMaxXPoint(const int& value);
  void setMaxYPoint(const int& value);
  void loadMazeFile(const QString& file_path);

 private:
  s21::Point start_point_ = {0, 0};
  s21::Point finish_point_ = {0, 0};
  s21::Controller controller_;
  Ui::MainWindow* ui_;
  CaveWindow* cave_window_;
};
#endif  // MAINWINDOW_H
