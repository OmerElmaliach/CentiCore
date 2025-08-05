#include "AppController.hpp"
#include "MainInterface.hpp"

AppController::AppController() : m_logger(DebugUtils::getInstance()) {
    route();
}

void AppController::route() {
    m_logger.debugLog("Routing signals to controller...", "CONTROLLER", "INFO");
    // connect(m_view, &MainInterface::test, this, &AppController::testMethod);
    // TODO: DEFINE SIGNALS
    m_logger.debugLog("Routing completed", "CONTROLLER", "INFO");
}

void AppController::setView(MainInterface* view) {
    m_view = view;
}