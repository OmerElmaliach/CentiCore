#include "monthlyExpenses.hpp"

MonthlyExpenses::MonthlyExpenses(string month, double total) : m_month(month), m_total(total) { }

string MonthlyExpenses::getMonth() { return m_month; }

double MonthlyExpenses::getTotal() { return m_total; }

void MonthlyExpenses::updateTotal(double amount) { m_total += amount; }

void MonthlyExpenses::add(string expenseName, double amount) {
    tuple<string, string, double> exp;
    get<0>(exp) = QDateTime::currentDateTime().toString("dd").toLocal8Bit().toStdString();
    get<1>(exp) = expenseName;
    get<2>(exp) = amount;
    m_expenses.push_back(exp);
}