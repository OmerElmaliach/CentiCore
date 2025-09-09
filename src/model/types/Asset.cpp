#include "Asset.hpp"

Asset::Asset(string symbol, double shares, double currPrice, int type) :
    m_symbol(symbol),
    m_shares(shares),
    m_currPrice(currPrice),
    m_type(type) {
        m_lastUpdated = QDateTime::currentDateTime().toString("hh:mm:ss");
}

string Asset::getSymbol() { return m_symbol; }

double Asset::getShares() { return m_shares; }

double Asset::getCurrPrice() { return m_currPrice; }

QString Asset::getLastUpdated() { return m_lastUpdated; }

int Asset::getType() { return m_type; }

void Asset::setShares(double shares) { m_shares = shares; }

void Asset::setCurrPrice(double currPrice) { m_currPrice = currPrice; }

void Asset::update(double newPrice) {
    setCurrPrice(newPrice);
    m_lastUpdated = QDateTime::currentDateTime().toString("hh:mm:ss"); 
}