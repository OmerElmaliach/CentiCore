#include <QApplication>
#include "MainInterface.hpp"
#include "AppController.hpp"

int main(int argc, char *argv[]) {
    #if defined(__linux__)
    qputenv("QT_QPA_PLATFORM", "xcb");  // Force X11 backend instead of Wayland
    #endif

    QApplication app(argc, argv);
    AppController* controller = new AppController();
    MainInterface* view = new MainInterface(controller);
    
    controller->setView(view);
    view->show();
    return app.exec();
}
