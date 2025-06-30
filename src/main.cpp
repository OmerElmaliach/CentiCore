#include <QDateTime>
#include <QApplication>
#include <QFile>
#include "gui/components/main_interface.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QFile styleFile(":/styles/qss/main_interface.qss");  
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        app.setStyleSheet(style);
        styleFile.close();
    } else {
        qWarning("[%s]%s %s", QDateTime().currentDateTime().toString("hh:mm:ss").toLocal8Bit().constData(),
         "[CENTICORE-FRONTEND][ERROR]", "Failed to load style file for main_interface");
    }

    MainInterface w;
    w.show();

    return app.exec();
}
