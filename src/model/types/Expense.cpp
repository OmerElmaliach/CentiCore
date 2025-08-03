#include "include/Expense.hpp"

Expense::Expense(string date, string name, double amount) : m_date(date), m_name(name), m_amount(amount) {}

string Expense::getDate() { return m_date; }

string Expense::getName() { return m_name; }

double Expense::getAmount() { return m_amount; }