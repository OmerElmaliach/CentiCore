#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QTableView>
#include "GeneralUtils.hpp"
#include "CreateAssetDialog.hpp"
#include "CreateInvestDialog.hpp"
#include "DebugUtils.hpp"
#include "WindowDragFilter.hpp"
#include "InvestsController.hpp"
#include "AssetsController.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class AssetPage; }
QT_END_NAMESPACE

class AssetPage : public QMainWindow {
    Q_OBJECT

private:
    const char* PAGE_UI = ":/styles/qss/asset_page.qss";
    Ui::AssetPage *m_ui;
    DebugUtils& m_logger;
    AssetsController* m_asset_cont;
    QStringListModel* m_invest_model;
    GeneralUtils* m_utils;
    enum AssetColumns {
        SYMBOL = 0,
        QUANTITY = 1, 
        PRICE = 2,
        DAILY_CHANGE_PERCENT = 3,
        DAILY_CHANGE_DOLLAR = 4,
        TOTAL_VALUE = 5,
        COLUMN_COUNT = 6
    };

public:
    /**
     * @brief Constructor function for asset page
     */
    explicit AssetPage(QWidget *parent = nullptr);

    /**
     * @brief Deconstructor function for asset page
     */
    ~AssetPage();

    /**
     * @brief Loads the qss into the ui file
     */
    void loadStyles(const char* stylePath);

    /**
     * @brief Define and load buttons functionality
     */
    void loadBtns();

    void onAssetUpdate();

    /**
     * @brief Loads up existing assets to the item widget
     */
    void loadAssets();

    /**
     * @brief Updates asset stats in view
     */
    void updateAsset(QString symbol, double currPrice, double d, double dp, int type);

    /**
     * @brief Adds an investment to the item list
     */
    void onInvestCreate(double amount);

    /**
     * @brief Loads up existing investments to the item list
     */
    void loadInvests();

    /**
     * @brief Update page stats
     */
    void updateStats(double pvalue, double dchange, double invests);

signals:
    void switchPage(int index);
};
