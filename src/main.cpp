#include <QString>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <QApplication>
#include <QFile>
#include "gui/components/main_interface.h"
using namespace std;
using namespace chrono;

QString getCurrentTimestamp() {
    auto now = system_clock::now();
    time_t t_now = system_clock::to_time_t(now);
    tm tm_now = *localtime(&t_now);

    ostringstream oss;
    oss << "[" << put_time(&tm_now, "%Y-%m-%d %H:%M:%S") << "]";
    return QString::fromStdString(oss.str());
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QFile styleFile(":/styles/main_interface.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        app.setStyleSheet(style);
        styleFile.close();
    } else {
        qWarning("%s %s %s",
            getCurrentTimestamp().toLocal8Bit().constData(),
            "[CENTICORE-GUI][ERROR]",
            "Failed to load style file for main_interface");
    }

    MainInterface w;
    w.show();

    return app.exec();
}
