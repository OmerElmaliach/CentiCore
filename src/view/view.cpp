#include <QApplication>
#include "components/include/main_interface.hpp"
const char* INTERFACE_UI = ":/styles/qss/main_interface.qss";

int main(int argc, char *argv[]) {
    #if defined(__linux__)
    qputenv("QT_QPA_PLATFORM", "xcb");  // Force X11 backend instead of Wayland
    #endif

    QApplication app(argc, argv);
    MainInterface w;
    w.loadStyles(INTERFACE_UI);
    w.show();
    return app.exec();
}
