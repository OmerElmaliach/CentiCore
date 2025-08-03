#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <QDateTime>
using namespace std;

class MonthlyExpenses {
private:
    string m_month;
    vector<tuple<string, string, double>> m_expenses;
    double m_total;

public:
    /**
     * Constructor for stock.
     */
    MonthlyExpenses(string month, double total);

    // Getters

    string getMonth();

    double getTotal();

    /**
     * Update total amount of spending.
     */
    void updateTotal(double amount);

    /**
     * Appends an expense to the list.
     */
    void add(string expenseName, double amount);
};