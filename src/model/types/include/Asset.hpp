#pragma once

#include <string>
#include <QDateTime>
using namespace std;

class Asset {
private:
    string m_symbol;
    double m_shares;
    double m_averageBuyPrice;
    double m_currPrice;
    QString m_lastUpdated;
    int m_type;

public:
    /**
     * @brief Constructor for asset
     */
    Asset(string symbol, double shares, double currPrice, int type);

    // Getters

    string getSymbol();

    double getShares();
    
    double getCurrPrice();

    QString getLastUpdated();

    int getType();


    // Setters

    void setShares(double shares);

    void setCurrPrice(double currPrice);

    /**
     * @brief Updates the current price and records the update time.
     */
    void update(double newPrice);
};