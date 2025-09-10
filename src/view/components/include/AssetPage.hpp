#pragma once

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStringListModel>
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
    QStandardItemModel* m_stock_model;
    QStandardItemModel* m_crypto_model;
    QStringListModel *m_invest_model;

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

    /**
     * @brief Adds an asset to the display widget
     * 
     * @param type 0 for stock, 1 for crypto
     */
    void onAssetCreate(const QString symbol, QString shares, int type);

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

signals:
    void switchPage(int index);
};
