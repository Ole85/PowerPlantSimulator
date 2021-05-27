#ifndef CONTROLPANELCA_H
#define CONTROLPANELCA_H

#include "enumsca.h"
#include "myEnums.h"
#include <QPushButton>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class ControlPanelCA;
}
QT_END_NAMESPACE

// structs for ControlPanel
struct ButtonPtr {
  QPushButton *buttonOn;
  QPushButton *buttonOff;
};
class ControlPanelCA : public QWidget {
  Q_OBJECT

  friend class CompressedAir;

public:
  explicit ControlPanelCA(QWidget *parent = nullptr);
  ~ControlPanelCA();

  std::array<ButtonPtr, 2> buttonPtr;
  int chrisControlPanel;
  void fGUIupdateButton(int, Status &);
  void fGUIupdateButtonsAll(std::array<Compressor, 2> &);
signals:
  void signalButtonName(int, Status);
  void signalPriorityCompressor(int);
  void signalCvPSH(int);
  void signalCvPSL(int);
  void signalCvPSLL(int);
  void signalOperationMode(OperationMode);
private slots:
  void on_buttonOnCompressor0_clicked();

  void on_buttonOffCompressor0_clicked();

  void on_buttonOnCompressor1_clicked();

  void on_buttonOffCompressor1_clicked();

  void on_radioButtonManual_clicked();

  void on_radioButtonAutomatic_clicked();

  void on_comboBox_currentIndexChanged(int);

  void on_spinBoxPSH_valueChanged(int);

  void on_spinBoxPSL_valueChanged(int);

  void on_spinBoxPSLL_valueChanged(int arg1);

private:
  Ui::ControlPanelCA *ui;
};

#endif // CONTROLPANELCA_H
