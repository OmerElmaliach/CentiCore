#include "Stock.hpp"

Stock::Stock(string symbol, double shares, double averageBuyPrice, double currPrice) :
    m_symbol(symbol),
    m_shares(shares),
    m_averageBuyPrice(averageBuyPrice),
    m_currPrice(currPrice) {
    m_lastUpdated = QDateTime::currentDateTime().toString("hh:mm:ss");
}

string Stock::getSymbol() { return m_symbol; }

double Stock::getShares() { return m_shares; }

double Stock::getAverageBuyPrice() { return m_averageBuyPrice; }

double Stock::getCurrPrice() { return m_currPrice; }

QString Stock::getLastUpdated() { return m_lastUpdated; }

void Stock::setShares(double shares) { m_shares = shares; }

void Stock::setAverageBuyPrice(double averageBuyPrice) { m_averageBuyPrice = averageBuyPrice; }

void Stock::setCurrPrice(double currPrice) { m_currPrice = currPrice; }

void Stock::update(double newPrice) {
    setCurrPrice(newPrice);
    m_lastUpdated = QDateTime::currentDateTime().toString("hh:mm:ss"); 
}