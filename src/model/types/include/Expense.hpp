#pragma once

#include <string>
using namespace std;

class Expense {
private:
    string m_date;
    string m_category;
    double m_amount;

public:
    /**
     * Constructor for expense.
     */
    Expense(string date, string category, double amount);

    // Getters

    string getDate();

    string getCategory();

    double getAmount();
};