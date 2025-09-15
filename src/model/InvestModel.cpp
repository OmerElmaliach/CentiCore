#include "InvestModel.hpp"

InvestModel::InvestModel() : m_logger(DebugUtils::getInstance()) {
    QDateTime dt = QDateTime::currentDateTime();
    QString dataPath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("../../data/");
    QDir dir(dataPath);
    if (!dir.exists())
        dir.mkpath(".");

    m_dataFile.setFileName(dataPath + "Investments.json");
    if (m_dataFile.exists()) {
        if (!m_dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
            m_logger.debugLog("InvestModel: Failed to open investment file", "MODEL", "ERR");
        
        // Extract available data from the json file.
        m_data = QJsonDocument().fromJson(m_dataFile.readAll()).array();
        m_dataFile.close();
    }
}

InvestModel& InvestModel::getInstance() {
    static InvestModel instance;
    return instance;
}

bool InvestModel::add(double amount, const QString& date) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "InvestModel: Appending new investment, amount: %.2f", amount);
    m_logger.debugLog(buff, "MODEL", "INFO");

    // Create new investment and append to array data
    QJsonObject jsonInv;
    jsonInv["amount"] = QJsonValue(amount);
    jsonInv["date"] = QJsonValue(date);
    m_data.append(jsonInv);

    if (!m_dataFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        m_logger.debugLog("InvestModel: Failed to open investment file", "MODEL", "ERR");
        return false;
    }
    
    // Push into file
    m_dataFile.write(QJsonDocument(m_data).toJson());
    m_dataFile.close();

    return true;
}

QJsonArray InvestModel::getInvestments() {
    return m_data;
}