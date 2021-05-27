#include "controlpanelca.h"
#include "ui_controlpanelca.h"
#include <QDebug>

ControlPanelCA::ControlPanelCA(QWidget *parent)
    : QWidget(parent), ui(new Ui::ControlPanelCA) {
  ui->setupUi(this);

  buttonPtr[0].buttonOn = ui->buttonOnCompressor0;
  buttonPtr[0].buttonOff = ui->buttonOffCompressor0;
  buttonPtr[1].buttonOn = ui->buttonOnCompressor1;
  buttonPtr[1].buttonOff = ui->buttonOffCompressor1;

  ui->comboBox->addItem("Compressor #1");
  ui->comboBox->addItem("Compressor #2");
}

ControlPanelCA::~ControlPanelCA() { delete ui; }

void ControlPanelCA::fGUIupdateButton(int id, Status &status) {
  if (status == On) {
    buttonPtr[id].buttonOn->setChecked(true);
    buttonPtr[id].buttonOff->setChecked(false);
  } else if (status == Off) {
    buttonPtr[id].buttonOff->setChecked(true);
    buttonPtr[id].buttonOn->setChecked(false);
  };
}

void ControlPanelCA::fGUIupdateButtonsAll(std::array<Compressor, 2> &stati) {
  for (int i = 0; i < (int)stati.size(); i++) {
    fGUIupdateButton(i, stati[i].status);
  }
}

void ControlPanelCA::on_buttonOnCompressor0_clicked() {
  emit signalButtonName(0, On);
}
void ControlPanelCA::on_buttonOffCompressor0_clicked() {
  emit signalButtonName(0, Off);
}
void ControlPanelCA::on_buttonOnCompressor1_clicked() {
  emit signalButtonName(1, On);
}
void ControlPanelCA::on_buttonOffCompressor1_clicked() {
  emit signalButtonName(1, Off);
}

void ControlPanelCA::on_radioButtonManual_clicked() {
  emit signalOperationMode(manual);
}

void ControlPanelCA::on_radioButtonAutomatic_clicked() {
  emit signalOperationMode(automatic);
}

void ControlPanelCA::on_comboBox_currentIndexChanged(int index) {
  emit signalPriorityCompressor(index);
}

void ControlPanelCA::on_spinBoxPSH_valueChanged(int value) {

  emit signalCvPSH(value);
}

void ControlPanelCA::on_spinBoxPSL_valueChanged(int value) {

  ui->spinBoxPSH->setMinimum(value + 1);
  ui->spinBoxPSLL->setMaximum(value - 1);

  qDebug() << "ui->spinBoxPSL->value();" << ui->spinBoxPSL->value();
  emit signalCvPSL(value);
}

void ControlPanelCA::on_spinBoxPSLL_valueChanged(int value) {
  emit signalCvPSLL(value);
}
