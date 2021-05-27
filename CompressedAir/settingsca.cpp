#include "settingsca.h"
#include "ui_settingsca.h"

SettingsCA::SettingsCA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsCA)
{
    ui->setupUi(this);
}

SettingsCA::~SettingsCA()
{
    delete ui;
}
