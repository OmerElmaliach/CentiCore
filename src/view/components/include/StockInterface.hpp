#pragma once

#include <QMainWindow>
#include <QDateTime>
#include <QFile>
#include <QMouseEvent>
#include <QListView>
#include <QCursor>
#include <QPoint>
#include <QStringListModel>
#include "DebugUtils.hpp"
#include "WindowDragFilter.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class StockInterface; }
QT_END_NAMESPACE

class StockInterface : public QMainWindow {
    Q_OBJECT

private:
    const char* INTERFACE_UI = ":/styles/qss/stocks.qss";
    Ui::StockInterface *m_ui;
    DebugUtils& m_logger;
    QStringListModel *m_model;

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
     */
    void onAssetCreate(const QString sign, QString amount, QString type);

    /**
     * @brief Loads up existing assets to the item widget
     */
    void loadAssets();
};
