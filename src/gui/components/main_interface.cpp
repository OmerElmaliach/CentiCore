#include "main_interface.h"
#include "../ui/ui_main_interface.h"

MainInterface::MainInterface(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainInterface) {
    m_ui->setupUi(this);
    connect(m_ui->dashBoard_btn, &QPushButton::clicked, this, [] {
        qDebug("[%s]%s %s", QDateTime().currentDateTime().toString("hh:mm:ss").toLocal8Bit().constData(),
         "[CENTICORE-FRONTEND][INFO]", "Dashboard button pressed");
    });
}

MainInterface::~MainInterface() {
    delete m_ui;
}
