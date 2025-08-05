#include "include/AppController.hpp"

AppController::AppController(MainInterface* view) : m_view(view), m_logger(DebugUtils::getInstance()) {
    route();
}

void AppController::route() {
    m_logger.debugLog("Routing signals to controller...", "CONTROLLER", "INFO");
    // connect(m_view, &MainInterface::test, this, &AppController::testMethod);
    // TODO: DEFINE SIGNALS
    m_logger.debugLog("Routing completed", "CONTROLLER", "INFO");
}
