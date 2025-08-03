#pragma once

#include <QFile>
#include <QJsonDocument>
#include <string>
using namespace std;

// Singleton
class ExpenseStorageManager {
private:
    QFile m_dataFile;

    /**
     * Constructor for the expense storage.
     */
    ExpenseStorageManager();

public:
    /**
     * Returns the instance of the expense storage.
     */
    ExpenseStorageManager& getInstance();

    /**
     * Adds an expense to the db.
     */
    bool add(string expenseName, double amount);

    /**
     * removes an expense from the db.
     */
    bool remove(string date, string expenseName);

    ExpenseStorageManager(const ExpenseStorageManager&) = delete;
    
    ExpenseStorageManager& operator=(const ExpenseStorageManager&) = delete;
};