#include "ExpenseModel.hpp"

ExpenseModel::ExpenseModel() : m_logger(DebugUtils::getInstance()) {
    QDateTime dt = QDateTime::currentDateTime();
    QString dataPath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("../../data/" + dt.toString("yyyy") + "/expenses/");
    QDir dir(dataPath);
    if (!dir.exists())
        dir.mkpath(".");

    m_dataFile.setFileName(dataPath + dt.toString("MMMM") + ".json");
    if (m_dataFile.exists()) {
        if (!m_dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
            m_logger.debugLog("Failed to open expense file", "MODEL", "ERR");
        
        // Extract available data from the json file.
        m_data = QJsonDocument().fromJson(m_dataFile.readAll()).array();
        m_dataFile.close();
    }
}

ExpenseModel& ExpenseModel::getInstance() {
    static ExpenseModel instance;
    return instance;
}

bool ExpenseModel::add(QString category, double amount, QString date) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "Appending new expense: %s, amount: %.2f", category.toStdString().c_str(), amount);
    m_logger.debugLog(buff, "MODEL", "INFO");

    // Create new expense and append to array data
    QJsonObject jsonExpense;
    jsonExpense["date"] = QJsonValue(date);
    jsonExpense["category"] = QJsonValue(category);
    jsonExpense["amount"] = QJsonValue(amount);
    m_data.append(jsonExpense);

    if (!m_dataFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        m_logger.debugLog("Failed to open expense file", "MODEL", "ERR");
        return false;
    }
    
    // Push into file
    m_dataFile.write(QJsonDocument(m_data).toJson());
    m_dataFile.close();

    return true;
}

bool ExpenseModel::remove(QString category, QString date, int idx) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "Removing expense: name: %s, date: %s", date.toStdString().c_str(), category.toStdString().c_str());
    m_logger.debugLog(buff, "MODEL", "INFO");

    m_data.removeAt(idx);
    if (!m_dataFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        m_logger.debugLog("Failed to open expense file", "MODEL", "ERR");
        return false;
    }
    
    // Push into file
    m_dataFile.write(QJsonDocument(m_data).toJson());
    m_dataFile.close();

    return true;
}

int ExpenseModel::find(QString category, QString date) {
    // Loop and find the expense index.
    for (int i = 0; i < m_data.size(); i++) {
        QJsonObject item = m_data[i].toObject();
        if ((item["date"].toString() == date) && (item["category"].toString() == category))
            return i;
    }

    return -1;
}

QJsonArray ExpenseModel::getExpenses() {
    return m_data;
}