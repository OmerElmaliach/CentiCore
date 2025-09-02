#include <QApplication>
#include "AppContainer.hpp"

int main(int argc, char *argv[]) {
    #if defined(__linux__)
    qputenv("QT_QPA_PLATFORM", "xcb");  // Force X11 backend instead of Wayland
    #endif

    QApplication app(argc, argv);
    AppContainer* view = new AppContainer();
    
    view->show();
    return app.exec();
}
