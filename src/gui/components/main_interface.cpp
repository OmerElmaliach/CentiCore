#include "main_interface.h"
#include "../ui/ui_main_interface.h"

MainInterface::MainInterface(QWidget *parent): QMainWindow(parent), ui(new Ui::MainInterface) {
    ui->setupUi(this);
    connect(ui->dashBoard_btn, &QPushButton::clicked, this, [] {
        qDebug("Dashboard button clicked");
    });
}

MainInterface::~MainInterface() {
    delete ui;
}
