#include <QApplication>
#include "gui/components/main_interface.h"
const char* INTERFACE_UI = ":/styles/qss/main_interface.qss";

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainInterface w;
    w.loadStyles(INTERFACE_UI);  
    w.show();
    return app.exec();
}
