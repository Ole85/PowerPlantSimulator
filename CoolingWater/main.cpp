#include "compressedair.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CompressedAir w;
  w.controlPanelCA->move(0, 0);
  w.controlPanelCA->show();
  w.screenCA->move(500, 0);
  w.screenCA->show();
  return a.exec();
}
