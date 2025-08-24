#include "Expense.hpp"

Expense::Expense(string date, string category, double amount) : m_date(date), m_category(category), m_amount(amount) {}

string Expense::getDate() { return m_date; }

string Expense::getCategory() { return m_category; }

double Expense::getAmount() { return m_amount; }