#include <QApplication>
#include <QFile>
#include "components/main_interface.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QFile styleFile("styles/main_interface.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        app.setStyleSheet(style);
    }

    MainInterface w;
    w.show();

    return app.exec();
}
