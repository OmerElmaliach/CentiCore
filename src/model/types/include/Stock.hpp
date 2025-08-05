#pragma once

#include <string>
#include <QDateTime>
using namespace std;

class Stock {
private:
    string m_symbol;
    double m_shares;
    double m_averageBuyPrice;
    double m_currPrice;
    QString m_lastUpdated;

public:
    /**
     * Constructor for stock
     */
    Stock(string symbol, double shares, double averageBuyPrice, double currPrice);

    // Getters

    string getSymbol();

    double getShares();

    double getAverageBuyPrice();
    
    double getCurrPrice();

    QString getLastUpdated();


    // Setters

    void setShares(double shares);

    void setAverageBuyPrice(double averageBuyPrice);

    void setCurrPrice(double currPrice);

    /**
     * Updates the current price and records the update time.
     */
    void update(double newPrice);
};