#include "AssetsController.hpp"

const QStringList AssetsController::ASSET_HEADERS = {"Symbol", "Quantity", "Price per Unit", "Daily change (%)", "Daily change ($)", "Total Value"};

AssetsController::AssetsController() :
        m_model(AssetModel::getInstance()),
        m_logger(DebugUtils::getInstance()), 
        m_api(ApiServices::getInstance()),
        m_utils(GeneralUtils::getInstance()) {
    m_timer = new QTimer(this);
    m_stockTable = new QStandardItemModel(this);
    m_cryptoTable = new QStandardItemModel(this);
    setupConnections();
    loadAssets();
    fetchAssets();
}

void AssetsController::setupConnections() {
    // Data received from API
    connect(&m_api, &ApiServices::assetDataReceived, this, [this](const QString& symbol, const QJsonDocument& data) {
        int type = getType(symbol);
        if (type != -1) {
            // Update model
            if (!m_model.update(symbol, data["c"].toDouble()))
                m_logger.debugLog("AssetsController: Failed to update asset: " + symbol.toStdString(), "CONTROLLER", "ERR");
            
            // Update view
            updateTable(symbol, data["c"].toDouble(), data["d"].toDouble(), data["dp"].toDouble(), type);
        } else {
            m_logger.debugLog("AssetsController: Unable to determine type: " + symbol.toStdString(), "CONTROLLER", "ERR");
        }
    });

    // Data received from API (Error)
    connect(&m_api, &ApiServices::assetRequestFailed, this, [this](const QString& symbol, const QString& error) {
        m_logger.debugLog("AssetsController: Failed to retrieve asset: " + symbol.toStdString() + "ERROR: " + error.toStdString(), "CONTROLLER", "ERR");
    });

    // Timer timeout event
    connect(m_timer, &QTimer::timeout, [this] {
        fetchAssets();
        updateStats();
    });
}

AssetsController* AssetsController::getInstance() {
    static AssetsController* instance = new AssetsController();
    return instance;
}

bool AssetsController::add(const QString& symbol, double quantity, int type) {
    m_logger.debugLog("AssetsController: Adding symbol: " + symbol.toStdString(), "CONTROLLER", "INFO");
    if (!m_model.add(symbol, quantity, 0, QDateTime::currentDateTime().toString("hh:mm:ss"), type))
        return false;

    // Update the table model
    QStandardItemModel* tableModel = (type) ? m_cryptoTable : m_stockTable;
    QString newSym = symbol.contains(':') ? symbol.section(':', 1, 1) : symbol;
    for (int row = 0; row < tableModel->rowCount(); row++) {
        if (tableModel->item(row, SYMBOL)->text() == newSym) {
            tableModel->item(row, QUANTITY)->setText(m_utils->formatNumberWithCommas(tableModel->item(row, QUANTITY)->text().toDouble() + quantity, 2));
            return true;
        }
    }

    int currRow = tableModel->rowCount();
    tableModel->insertRow(currRow);
    tableModel->setItem(currRow, SYMBOL, new QStandardItem(symbol));
    tableModel->setItem(currRow, QUANTITY, new QStandardItem(m_utils->formatNumberWithCommas(quantity, 2)));
    tableModel->setItem(currRow, PRICE, new QStandardItem("N/A"));
    tableModel->setItem(currRow, DAILY_CHANGE_PERCENT, new QStandardItem("N/A"));
    tableModel->setItem(currRow, DAILY_CHANGE_DOLLAR, new QStandardItem("N/A"));
    tableModel->setItem(currRow, TOTAL_VALUE, new QStandardItem("N/A"));

    for (int i = 0; i < COLUMN_COUNT; ++i)
        tableModel->item(currRow, i)->setData(Qt::AlignCenter, Qt::TextAlignmentRole);

    return true;
}

void AssetsController::updateTable(const QString& symbol, double price, double d, double dp, int type) {
    QStandardItemModel* model = (type ? m_cryptoTable : m_stockTable);
    QString newSym = symbol.contains(':') ? symbol.section(':', 1, 1) : symbol;
    for (int row = 0; row < model->rowCount(); row++) {
        if (model->item(row, SYMBOL)->text() == newSym) {
            double quantity = model->item(row, QUANTITY)->text().toDouble();

            // Update the table
            model->item(row, PRICE)->setText(m_utils->formatNumberWithCommas(price, 2) + "  $");
            model->item(row, DAILY_CHANGE_PERCENT)->setText(m_utils->formatNumberWithCommas(dp, 2) + "  %");
            model->item(row, DAILY_CHANGE_DOLLAR)->setText(m_utils->formatNumberWithCommas(d * quantity, 2) + "  $");
            model->item(row, TOTAL_VALUE)->setText(m_utils->formatNumberWithCommas(price * quantity, 2) + "  $");

            QColor color = (d > 0) ? Qt::darkGreen : Qt::darkRed;
            model->item(row, DAILY_CHANGE_PERCENT)->setData(QBrush(color), Qt::ForegroundRole);
            model->item(row, DAILY_CHANGE_DOLLAR)->setData(QBrush(color), Qt::ForegroundRole);

            // Signal to view
            emit updatedAsset(symbol, price, d, dp, type);
        }
    }
}

bool AssetsController::remove(const QString& symbol, double quantity) {
    m_logger.debugLog("AssetsController: Signal for removing asset quantity received", "CONTROLLER", "INFO");
    int idx = m_model.find(symbol);
    if (idx != -1)
        return m_model.remove(symbol, quantity, idx);

    m_logger.debugLog("AssetsController: Couldn't find given asset: " + symbol.toStdString(), "CONTROLLER", "WARN");
    return false;
}

void AssetsController::enableLiveUpdates(int time) { m_timer->start(time); }

void AssetsController::disableLiveUpdates() { m_timer->stop(); }

QStandardItemModel* AssetsController::getStockTable() { return m_stockTable; }

QStandardItemModel* AssetsController::getCryptoTable() { return m_cryptoTable; }

QJsonArray AssetsController::getAssets() { return m_model.getAssets(); }

int AssetsController::getType(const QString& symbol) { return m_model.getType(symbol); }

void AssetsController::fetchAssets() {
    QJsonArray assetArr = getAssets();
    for (int i = 0; i < assetArr.size(); i++) {
        m_api.getAsset(assetArr[i].toObject()["symbol"].toString());
    }
}

void AssetsController::setupAssetTable(QStandardItemModel* model, QTableView* view) {
    view->setModel(model);
    model->setHorizontalHeaderLabels(ASSET_HEADERS);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void AssetsController::updateStats() {
    double pvalue = 0, dchange = 0, invests = InvestsController::getInstance()->getSum();
    for (int i = 0; i < m_stockTable->rowCount(); i++) {
        pvalue += m_stockTable->item(i, TOTAL_VALUE)->text().remove("$").remove(",").toDouble();
        dchange += m_stockTable->item(i, DAILY_CHANGE_DOLLAR)->text().remove("$").remove(",").toDouble();
    }

    for (int i = 0; i < m_cryptoTable->rowCount(); i++) {
        pvalue += m_cryptoTable->item(i, TOTAL_VALUE)->text().remove("$").remove(",").toDouble();
        dchange += m_cryptoTable->item(i, DAILY_CHANGE_DOLLAR)->text().remove("$").remove(",").toDouble();
    }

    emit updatedStats(pvalue, dchange, invests);
}

void AssetsController::loadAssets() {
    QJsonArray data = getAssets();

    // Add each asset
    for (int i = 0; i < data.size(); i++) {
        QJsonObject item = data[i].toObject();
        QStandardItemModel* table = (item["type"].toInt()) ? m_cryptoTable : m_stockTable;
        int currRow = table->rowCount();
        QString symbol = item["symbol"].toString().contains(':') ? item["symbol"].toString().section(':', 1, 1) : item["symbol"].toString();

        table->setItem(currRow, SYMBOL, new QStandardItem(symbol));
        table->setItem(currRow, QUANTITY, new QStandardItem(m_utils->formatNumberWithCommas(item["quantity"].toDouble(), 2)));
        table->setItem(currRow, PRICE, new QStandardItem("Loading..."));
        table->setItem(currRow, DAILY_CHANGE_PERCENT, new QStandardItem("Loading..."));
        table->setItem(currRow, DAILY_CHANGE_DOLLAR, new QStandardItem("Loading..."));
        table->setItem(currRow, TOTAL_VALUE, new QStandardItem("Loading..."));

        // Cell settings
        for (int i = 0; i < COLUMN_COUNT; ++i) {
            table->item(currRow, i)->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        }
    }

    m_logger.debugLog("AssetsController: Loaded previous assets", "CONTROLLER", "INFO");
}