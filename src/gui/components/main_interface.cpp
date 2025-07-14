#include "include/main_interface.h"
#include "../ui/ui_main_interface.h"

MainInterface::MainInterface(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainInterface) {
    m_ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->loadFuncs();
    m_ui->topbarWidget->installEventFilter(this);
}

MainInterface::~MainInterface() {
    delete m_ui;
}

void MainInterface::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);  
    if (styleFile.open(QFile::ReadOnly)) {
        this->setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        qWarning("[%s]%s %s", QDateTime().currentDateTime().toString("hh:mm:ss").toLocal8Bit().constData(),
         "[CENTICORE-UI][ERROR]", "Failed to load style file for main_interface");
    }
}

void MainInterface::loadFuncs() {
    connect(m_ui->exit_btn, &QPushButton::clicked, this, [] {
        qDebug("[%s]%s %s", QDateTime().currentDateTime().toString("hh:mm:ss").toLocal8Bit().constData(),
         "[CENTICORE-UI][INFO]", "Exit pressed, program shutdown...");
         exit(0);
    });
}

bool MainInterface::eventFilter(QObject *object, QEvent *event) {
    if(object == m_ui->topbarWidget) {
        if (event->type() == QEvent::MouseButtonPress) {
            // TODO: DEFINE DRAGGING FUNC
        }
    }

    return QObject::eventFilter(object, event); 
}
