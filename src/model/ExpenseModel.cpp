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
            m_logger.debugLog("Failed to open expense file", "MODEL", "ERROR");
        
        // Extract available data from the json file.
        m_data = QJsonDocument().fromJson(m_dataFile.readAll()).array();
        m_dataFile.close();
    }
}

ExpenseModel& ExpenseModel::getInstance() {
    static ExpenseModel instance;
    return instance;
}

bool ExpenseModel::add(Expense exp) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "Appending new expense: %s, amount: %.2f", exp.getCategory().c_str(), exp.getAmount());
    m_logger.debugLog(buff, "MODEL", "INFO");

    // Create new expense and append to array data
    QJsonObject jsonExpense;
    jsonExpense["date"] = QJsonValue(exp.getDate().c_str());
    jsonExpense["category"] = QJsonValue(exp.getCategory().c_str());
    jsonExpense["amount"] = QJsonValue(exp.getAmount());
    m_data.append(jsonExpense);

    if (!m_dataFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        m_logger.debugLog("Failed to open expense file", "MODEL", "ERROR");
        return false;
    }
    
    // Push into file
    m_dataFile.write(QJsonDocument(m_data).toJson());
    m_dataFile.close();

    return true;
}

bool ExpenseModel::remove(Expense exp, int idx) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "Removing expense: name: %s, date: %s", exp.getDate().c_str(), exp.getCategory().c_str());
    m_logger.debugLog(buff, "MODEL", "INFO");

    m_data.removeAt(idx);
    if (!m_dataFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        m_logger.debugLog("Failed to open expense file", "MODEL", "ERROR");
        return false;
    }
    
    // Push into file
    m_dataFile.write(QJsonDocument(m_data).toJson());
    m_dataFile.close();

    return true;
}

int ExpenseModel::find(Expense exp) {
    // Loop and find the expense index.
    for (int i = 0; i < m_data.size(); i++) {
        QJsonObject item = m_data[i].toObject();
        if ((!item["date"].toString().toStdString().compare(exp.getDate())) && (!item["name"].toString().toStdString().compare(exp.getCategory())))
            return i;
    }

    return -1;
}

QJsonArray ExpenseModel::getExpenses() {
    return m_data;
}