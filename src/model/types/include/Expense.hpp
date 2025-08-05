#pragma once

#include <string>
using namespace std;

class Expense {
private:
    string m_date;
    string m_name;
    double m_amount;

public:
    /**
     * Constructor for expense.
     */
    Expense(string date, string name, double amount);

    // Getters

    string getDate();

    string getName();

    double getAmount();
};