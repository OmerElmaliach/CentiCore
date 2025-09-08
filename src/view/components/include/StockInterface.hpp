#pragma once

#include <QMainWindow>
#include <QStandardItemModel>
#include "CreateAssetDialog.hpp"
#include "DebugUtils.hpp"
#include "WindowDragFilter.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class StockInterface; }
QT_END_NAMESPACE

class StockInterface : public QMainWindow {
    Q_OBJECT

private:
    const char* INTERFACE_UI = ":/styles/qss/asset_page.qss";
    Ui::StockInterface *m_ui;
    DebugUtils& m_logger;
    QStandardItemModel* m_stock_model;
    QStandardItemModel* m_crypto_model;

public:
    /**
     * @brief Constructor function for stock interface.
     */
    explicit StockInterface(QWidget *parent = nullptr);

    /**
     * @brief Deconstructor function for stock interface.
     */
    ~StockInterface();

    /**
     * @brief Loads the qss into the ui file.
     */
    void loadStyles(const char* stylePath);

    /**
     * @brief Define and load buttons functionality.
     */
    void loadBtns();

    /**
     * @brief Adds an asset to the display widget.
     * 
     * @param type 0 for stock, 1 for crypto
     */
    void onAssetCreate(const QString symbol, QString shares, int type);

    /**
     * @brief Loads up existing assets to the item widget
     */
    void loadAssets();

signals:
    void switchPage(int index);
};
