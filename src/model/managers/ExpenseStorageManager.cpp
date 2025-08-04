#include "include/ExpenseStorageManager.hpp"

ExpenseStorageManager::ExpenseStorageManager() : m_logger(DebugUtils::getInstance()) {
    QDateTime dt = QDateTime::currentDateTime();
    QString dataPath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("../../data/" + dt.toString("yyyy") + "/expenses/");
    QDir dir(dataPath);
    if (!dir.exists())
        dir.mkpath(".");

    m_dataFile.setFileName(dataPath + dt.toString("MMMM") + ".json");
    if (!m_dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
        m_logger.debugLog("Failed to open expense file", "MODEL-MANAGER", "ERROR");
    
    // Extract available data from the json file.
    m_data = QJsonDocument().fromJson(m_dataFile.readAll()).array();
    m_dataFile.close();
}

ExpenseStorageManager& ExpenseStorageManager::getInstance() {
    static ExpenseStorageManager instance;
    return instance;
}

bool ExpenseStorageManager::add(string date, string expenseName, double amount) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "Appending new expense: %s, amount: %.2f", expenseName.c_str(), amount);
    m_logger.debugLog(buff, "MODEL-MANAGER", "INFO");

    // Create new expense and append to array data
    QJsonObject newExpense;
    newExpense["date"] = QJsonValue(date.c_str());
    newExpense["name"] = QJsonValue(expenseName.c_str());
    newExpense["amount"] = QJsonValue(amount);
    m_data.append(newExpense);

    if (!m_dataFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        m_logger.debugLog("Failed to open expense file", "MODEL-MANAGER", "ERROR");
        return false;
    }
    
    // Push into file
    m_dataFile.write(QJsonDocument(m_data).toJson());
    m_dataFile.close();

    return true;
}

bool ExpenseStorageManager::remove(string date, string expenseName) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "Removing expense: name: %s, date: %s", date.c_str(), expenseName.c_str());
    m_logger.debugLog(buff, "MODEL-MANAGER", "INFO");

    // Find and remove the expense from file.
    for (int i = 0; i < m_data.size(); i++) {
        QJsonObject expense = m_data[i].toObject();
        if ((!expense["date"].toString().toStdString().compare(date)) && (!expense["name"].toString().toStdString().compare(expenseName))) {
            m_data.removeAt(i);
            break;
        }

        if (i == m_data.size() - 1) {
            m_logger.debugLog("Failed to remove expense, couldn't find expense with given date/name", "MODEL-MANAGER", "ERROR");
            return false;
        }
    }

    if (!m_dataFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        m_logger.debugLog("Failed to open expense file", "MODEL-MANAGER", "ERROR");
        return false;
    }
    
    // Push into file
    m_dataFile.write(QJsonDocument(m_data).toJson());
    m_dataFile.close();

    return true;
}