#include <QApplication>
#include "MainInterface.hpp"

int main(int argc, char *argv[]) {
    #if defined(__linux__)
    qputenv("QT_QPA_PLATFORM", "xcb");  // Force X11 backend instead of Wayland
    #endif

    QApplication app(argc, argv);
    MainInterface* view = new MainInterface();
    
    view->show();
    return app.exec();
}
