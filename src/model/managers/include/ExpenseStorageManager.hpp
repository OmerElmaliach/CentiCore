#pragma once

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCoreApplication>
#include <QJsonObject>
#include <QDateTime>
#include <string>
#include "../../../utils/DebugUtils.hpp"
#define LOG_MSG_LENGTH 256
using namespace std;

// Singleton
class ExpenseStorageManager {
private:
    QFile m_dataFile;
    DebugUtils& m_logger;
    QJsonArray m_data;

    /**
     * Constructor for the expense storage.
     */
    ExpenseStorageManager();

public:
    /**
     * Returns the instance of the expense storage.
     */
    static ExpenseStorageManager& getInstance();

    /**
     * Adds an expense to the db.
     */
    bool add(string date, string expenseName, double amount);

    /**
     * removes an expense from the db.
     */
    bool remove(string date, string expenseName);

    ExpenseStorageManager(const ExpenseStorageManager&) = delete;
    
    ExpenseStorageManager& operator=(const ExpenseStorageManager&) = delete;
};