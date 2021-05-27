#include "datatable.h"
#include "QDebug"
#include "ui_datatable.h"
#include <QTableWidgetItem>

DataTable::DataTable(QWidget *parent) : QWidget(parent), ui(new Ui::DataTable) {
  ui->setupUi(this);

  for (int i = 0; i < (int)myData.size(); i++) {

    myData[i].objectItem = new QTableWidgetItem;
    ui->tableWidget->setItem(i, 0, myData[i].objectItem);

    myData[i].qtyItem = new QTableWidgetItem;
    ui->tableWidget->setItem(i, 1, myData[i].qtyItem);

    myData[i].descriptionItem = new QTableWidgetItem;
    ui->tableWidget->setItem(i, 2, myData[i].descriptionItem);

    myData[i].valueItem = new QTableWidgetItem;
    ui->tableWidget->setItem(i, 3, myData[i].valueItem);

    myData[i].unitItem = new QTableWidgetItem;
    ui->tableWidget->setItem(i, 4, myData[i].unitItem);
  }
  myData[0].objectItem->setText("Haus");
}

DataTable::~DataTable() { delete ui; }

void DataTable::slotUpdatePumpsCW(std::array<Pump, 2> &pumps) {
  myData[0].objectItem->setText(pumps[mainPump].title);
  myData[0].qtyItem->setText(pumps[mainPump].capacity.quantity);
  myData[0].descriptionItem->setText(pumps[mainPump].capacity.description);
  myData[0].valueItem->setText(QString::number(pumps[mainPump].capacity.value));
  myData[0].unitItem->setText(pumps[mainPump].capacity.unit);

  myData[1].objectItem->setText(pumps[preheatingPump].title);
  myData[1].qtyItem->setText(pumps[preheatingPump].capacity.quantity);
  myData[1].descriptionItem->setText(
      pumps[preheatingPump].capacity.description);
  myData[1].valueItem->setText(
      QString::number(pumps[preheatingPump].capacity.value));
  myData[1].unitItem->setText(pumps[preheatingPump].capacity.unit);
}
//}

// void DataTable::fUpdatePumpsCW(std::array<Pump, 2> &pumps) {
//  qDebug() << pumps[mainPump].title;

//  myData[0].objectItem->setText(pumps[mainPump].title);
//  myData[0].qtyItem->setText(pumps[mainPump].capacity.quantity);
//  myData[0].descriptionItem->setText(pumps[mainPump].capacity.description);
//  myData[0].valueItem->setText(QString::number(pumps[mainPump].capacity.value));
//  myData[0].unitItem->setText(pumps[mainPump].capacity.unit);

//  myData[1].objectItem->setText(pumps[preheatingPump].title);
//  myData[1].qtyItem->setText(pumps[preheatingPump].capacity.quantity);
//  myData[1].descriptionItem->setText(
//      pumps[preheatingPump].capacity.description);
//  myData[1].valueItem->setText(
//      QString::number(pumps[preheatingPump].capacity.value));
//  myData[1].unitItem->setText(pumps[preheatingPump].capacity.unit);
//}
