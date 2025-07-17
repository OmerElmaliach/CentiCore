#include "include/main_interface.h"
#include "../ui/ui_main_interface.h"

MainInterface::MainInterface(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainInterface) {
    m_ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    loadFuncs();

    m_ui->topbarWidget->installEventFilter(this);
    m_ui->topbarDisplay->installEventFilter(this);
}

MainInterface::~MainInterface() {
    delete m_ui;
}

void MainInterface::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);  
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        qWarning("[%s]%s %s", QDateTime().currentDateTime().toString("hh:mm:ss").toLocal8Bit().constData(),
         "[CENTICORE-UI][ERROR]", "Failed to load style file for main_interface");
    }
}

void MainInterface::loadFuncs() {
    // Exit window button.
    connect(m_ui->exit_btn, &QPushButton::clicked, this, [] {
        qDebug("[%s]%s %s", QDateTime().currentDateTime().toString("hh:mm:ss").toLocal8Bit().constData(),
         "[CENTICORE-UI][INFO]", "Exit pressed, program shutdown...");
         exit(0);
    });

    // Minimize window button.
    connect(m_ui->minimize_btn, &QPushButton::clicked, this, [this] {
        qDebug("[%s]%s %s", QDateTime().currentDateTime().toString("hh:mm:ss").toLocal8Bit().constData(),
         "[CENTICORE-UI][INFO]", "Minimizing window");
         setWindowState(Qt::WindowMinimized);
    });
}

bool MainInterface::eventFilter(QObject *object, QEvent *event) {
    if(object == m_ui->topbarWidget || object == m_ui->topbarDisplay) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* mouse_eve = static_cast <QMouseEvent*> (event);
            if (mouse_eve->buttons() == Qt::LeftButton) {
                m_dragPosition = QCursor::pos() - frameGeometry().topLeft();  
                m_dragging = true;
            }
        } else if (event->type() == QEvent::MouseMove && m_dragging) {
            move(QCursor::pos() - m_dragPosition);
        } else if (event->type() == QEvent::MouseButtonRelease && m_dragging) {
            m_dragging = false;
        }
    }

    return QObject::eventFilter(object, event); 
}
