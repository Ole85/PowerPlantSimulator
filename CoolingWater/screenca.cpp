#include "screenca.h"
#include "ui_screenca.h"

ScreenCA::ScreenCA(QWidget *parent) : QWidget(parent), ui(new Ui::ScreenCA) {
  ui->setupUi(this);

  labelPtr[0] = ui->labelCompressor0;
  labelPtr[1] = ui->labelCompressor1;
}

ScreenCA::~ScreenCA() { delete ui; }

void ScreenCA::fGUIupdateCompressor(int id, Status &status) {
  switch (status) {
  case Off:
    labelPtr[id]->setPixmap(QPixmap(":/compressorOff.png"));
    break;
  case On:
    labelPtr[id]->setPixmap(QPixmap(":/compressoron.png"));
    break;
  }
}

void ScreenCA::fGUIupdateCompressorAll(std::array<Compressor, 2> &stati) {
  for (int i = 0; i < (int)stati.size(); i++) {
    fGUIupdateCompressor(i, stati[i].status);
  }
}
