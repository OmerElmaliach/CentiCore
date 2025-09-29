#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QTableView>
#include <QDesktopServices>
#include "AppConstants.hpp"
#include "Utils.hpp"
#include "CreateAssetDialog.hpp"
#include "CreateInvestDialog.hpp"
#include "Logger.hpp"
#include "WindowDragFilter.hpp"
#include "InvestsController.hpp"
#include "AssetsController.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class AssetPage; }
QT_END_NAMESPACE

/**
 * @brief Asset management page for stocks and cryptocurrencies
 * 
 * This class provides a comprehensive interface for managing user assets including
 * stocks, cryptocurrencies, and investments with real-time price updates and
 * portfolio statistics visualization.
 */
class AssetPage : public QMainWindow {
    Q_OBJECT

private:
    Ui::AssetPage *m_ui;
    Logger& m_logger;
    AssetsController* m_asset_cont;
    InvestsController* m_invest_cont;

    /**
     * @brief Initializes and connects all UI signals to their respective slots
     * @details Sets up window controls, navigation buttons, dialog connections, and controller signals
     */
    void setupConnections();

public:
    /**
     * @brief Constructs the asset page with parent widget
     * @param parent Parent widget, used for proper Qt ownership hierarchy (default: nullptr)
     */
    explicit AssetPage(QWidget *parent = nullptr);
    
    /**
     * @brief Destructor - cleans up UI resources and stops live data updates
     */
    ~AssetPage();
    
    /**
     * @brief Loads existing assets from persistent storage into the UI tables
     * @details Populates both stock and cryptocurrency tables with saved user assets
     */
    void loadAssets();
    
    /**
     * @brief Loads and displays the total sum of all investments
     * @details Updates the investment total display from the InvestsController
     */
    void loadTotalInvests();

public slots:
    /**
     * @brief Handles real-time asset data updates from the controller
     * @details Performs UI animations and visual feedback when asset prices change
     */
    void onAssetUpdate();
    
    /**
     * @brief Updates the portfolio statistics display with current values
     * @param pvalue Total portfolio value in USD
     * @param dchange Daily change amount in USD (can be negative)
     * @param invests Total amount of investments made in USD
     * @details Updates portfolio value, balance, and daily change with appropriate color coding
     */
    void onUpdateStats(double pvalue, double dchange, double invests);
    
    /**
     * @brief Handles the creation of a new investment entry
     * @param amount Investment amount in USD to add to the portfolio
     * @details Updates the total investment display and refreshes the investment list
     */
    void onInvestCreate(double amount);

signals:
    /**
     * @brief Emitted when user requests navigation to a different page
     * @param index Target page index in the main application stack (0 = dashboard)
     */
    void switchPage(int index);
};