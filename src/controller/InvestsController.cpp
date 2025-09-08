#include "InvestsController.hpp"

InvestsController::InvestsController() : m_model(InvestModel::getInstance()), m_logger(DebugUtils::getInstance()) {}

InvestsController& InvestsController::getInstance() {
    static InvestsController instance;
    return instance;
}

bool InvestsController::add(double amount) {
    m_logger.debugLog("Signal for add investment received", "CONTROLLER", "INFO");
    return m_model.add(amount);
}

QJsonArray InvestsController::getInvestments() {
    return m_model.getInvestments();
}