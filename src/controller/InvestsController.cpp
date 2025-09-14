#include "InvestsController.hpp"

InvestsController::InvestsController() : m_model(InvestModel::getInstance()), m_logger(DebugUtils::getInstance()) {
    m_investList = new QStringListModel(this);
    loadInvests();
}

InvestsController* InvestsController::getInstance() {
    static InvestsController* instance = new InvestsController();
    return instance;
}

bool InvestsController::add(double amount, QString date) {
    m_logger.debugLog("InvestsController: Signal for add investment received", "CONTROLLER", "INFO");
    if (m_model.add(amount, date)) {
        QStringList currList = m_investList->stringList();

        // Update investment list
        currList.append(QString::number(amount) + "$");
        m_investList->setStringList(currList);
        emit investCreated(amount);
    }

    return false;
}

QJsonArray InvestsController::getInvestments() {
    return m_model.getInvestments();
}

QStringListModel* InvestsController::getList() {
    return m_investList;
}

double InvestsController::getTotal() {
    double sum = 0;
    QJsonArray data = m_model.getInvestments();
    for (QJsonValue item : data) {
        sum += item["amount"].toDouble();
    }

    return sum;
}

void InvestsController::loadInvests() {
    QJsonArray data = m_model.getInvestments();
    QStringList curr = m_investList->stringList();

    // Add each investment made
    for (int i = 0; i < data.size(); i++) {
        QJsonObject item = data[i].toObject();
        curr.append(QString::number(item["amount"].toDouble()) + " $");
    }

    m_investList->setStringList(curr);
    m_logger.debugLog("InvestsController: Loaded previous investments", "CONTROLLER", "INFO");
}