#include <QApplication>
#include "view/components/include/MainInterface.hpp"
#include "controller/include/AppController.hpp"
const char* INTERFACE_UI = ":/styles/qss/main_interface.qss";

int main(int argc, char *argv[]) {
    #if defined(__linux__)
    qputenv("QT_QPA_PLATFORM", "xcb");  // Force X11 backend instead of Wayland
    #endif

    QApplication app(argc, argv);
    MainInterface* view = new MainInterface();
    AppController* controller = new AppController(view);
    
    view->loadStyles(INTERFACE_UI);
    view->show();
    return app.exec();
}
