#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      cave_window_(new CaveWindow) {
  ui_->setupUi(this);
  this->setFixedSize(this->width(), this->height());
  connect(cave_window_, &CaveWindow::caveWindowHidden, this, &MainWindow::show);
}

MainWindow::~MainWindow() {
  delete ui_;
}

void MainWindow::on_selectFileQPushButton_clicked() {
  QString file_path = QFileDialog::getOpenFileName(
      this, tr("Выберите файл лабиринта"), "",
      tr("Текстовые файлы (*.txt);;Все файлы (*)"));

  if (!file_path.isEmpty()) {
    loadMazeFile(file_path);
  } else {
    QMessageBox::warning(this, tr("Информация"), tr("Файл не был выбран."));
  }
}

void MainWindow::loadMazeFile(const QString& file_path) {
  s21::MazeError error = controller_.InitializeMaze(file_path.toStdString());
  if (error == s21::MazeError::kOk) {
    ui_->selectFileQLineEdit->setText(file_path);
    setMaxXPoint(controller_.GetMazeRowsCount() - 1);
    setMaxYPoint(controller_.GetMazeColumnsCount() - 1);
    ui_->mazeView->setController(controller_);
  } else {
    QMessageBox::warning(this, tr("Ошибка"),
                         tr("Не удалось загрузить файл лабиринта."));
  }
}

void MainWindow::on_generateMazeQPushButton_clicked() {
  s21::Maze maze;
  size_t rows = ui_->rowsQSpinBox->text().toUInt();
  size_t columns = ui_->columnsQSpinBox->text().toUInt();
  controller_.GenerateRandomMaze(rows, columns);
  setMaxXPoint(columns - 1);
  setMaxYPoint(rows - 1);
  start_point_ = finish_point_ = {0, 0};
  ui_->mazeView->setController(controller_);
}

void MainWindow::setMaxXPoint(const int& value) {
  ui_->xFromCordQSpinBox->setValue(0);
  ui_->xToCordQSpinBox->setValue(0);
  ui_->xFromCordQSpinBox->setMaximum(value);
  ui_->xToCordQSpinBox->setMaximum(value);
}

void MainWindow::setMaxYPoint(const int& value) {
  ui_->yFromCordQSpinBox->setValue(0);
  ui_->yToCordQSpinBox->setValue(0);
  ui_->yFromCordQSpinBox->setMaximum(value);
  ui_->yToCordQSpinBox->setMaximum(value);
}

void MainWindow::on_xFromCordQSpinBox_valueChanged(int value) {
  start_point_.x = value;

  auto path = controller_.FindMazePath(start_point_, finish_point_);
  ui_->mazeView->setPath(path);
}

void MainWindow::on_yFromCordQSpinBox_valueChanged(int value) {
  start_point_.y = value;

  auto path = controller_.FindMazePath(start_point_, finish_point_);
  ui_->mazeView->setPath(path);
}

void MainWindow::on_xToCordQSpinBox_valueChanged(int value) {
  finish_point_.x = value;

  auto path = controller_.FindMazePath(start_point_, finish_point_);
  ui_->mazeView->setPath(path);
}

void MainWindow::on_yToCordQSpinBox_valueChanged(int value) {
  finish_point_.y = value;

  auto path = controller_.FindMazePath(start_point_, finish_point_);
  ui_->mazeView->setPath(path);
}

void MainWindow::on_caveSelectQPushButton_clicked() {
  this->hide();
  cave_window_->show();
}
