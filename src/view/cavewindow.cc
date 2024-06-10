#include "cavewindow.h"

#include "ui_cavewindow.h"

CaveWindow::CaveWindow(QWidget* parent)
    : QWidget(parent), ui_(new Ui::CaveWindow), timer_(new QTimer(this)) {
  ui_->setupUi(this);
  setFixedSize(width(), height());
  connect(timer_, &QTimer::timeout, this,
          &CaveWindow::on_nextStepQPushButton_clicked);
}

CaveWindow::~CaveWindow() {
  delete ui_;
}

void CaveWindow::closeEvent(QCloseEvent* event) {
  emit windowClosed();
  QWidget::closeEvent(event);
}

void CaveWindow::on_selectFileQPushButton_clicked() {
  handleFileSelection();
}

void CaveWindow::on_generateCaveQPushButton_clicked() {
  int rows = ui_->rowsQSpinBox->value();
  int cols = ui_->columnsQSpinBox->value();
  int chance_of_random = ui_->fillProbabilityQSpinBox->value();
  controller_.GenerateRandomCave(rows, cols, chance_of_random);
  updateDisplay();
}

void CaveWindow::on_nextStepQPushButton_clicked() {
  if (controller_.GetCaveGrip().empty() ||
      controller_.GetCaveGrip()[0].empty()) {
    QMessageBox::warning(this, tr("Ошибка"),
                         tr("Пещера не была сгенерирована или загружена."));
    timer_->stop();
    ui_->startQPushButton->setText(tr("START"));
    return;
  }
  if (controller_.SimulateStep(ui_->birthLimitQSpinBox->value(),
                               ui_->deathLimitQSpinBox->value()) ==
      s21::CaveError::kEndSimulate) {
    timer_->stop();
    ui_->startQPushButton->setText(tr("START"));
  }
  updateDisplay();
}

void CaveWindow::on_startQPushButton_clicked() {
  startOrStopSimulation();
}

void CaveWindow::on_mazeSelectQPushButton_clicked() {
  emit caveWindowHidden();
  hide();
}

void CaveWindow::handleFileSelection() {
  QString file_path = QFileDialog::getOpenFileName(
      this, tr("Выберите файл шахты"), "",
      tr("Текстовые файлы (*.txt);;Все файлы (*)"));
  if (!file_path.isEmpty()) {
    auto error = controller_.InitializeCave(file_path.toStdString());
    if (error == s21::CaveError::kOk) {
      ui_->selectFileQLineEdit->setText(file_path);
      updateDisplay();
    } else {
      QMessageBox::warning(this, tr("Ошибка"),
                           tr("Не удалось загрузить файл пещеры."));
    }
  } else {
    QMessageBox::warning(this, tr("Информация"), tr("Файл не был выбран."));
  }
}

void CaveWindow::updateDisplay() {
  ui_->caveView->displayCave(controller_.GetCaveGrip());
}

void CaveWindow::startOrStopSimulation() {
  if (timer_->isActive()) {
    timer_->stop();
    ui_->startQPushButton->setText(tr("START"));
  } else {
    timer_->start(ui_->millisecondQSpinBox->value());
    ui_->startQPushButton->setText(tr("STOP"));
  }
}
