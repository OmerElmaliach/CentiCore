#include "AssetsController.hpp"

AssetsController::AssetsController() :
        m_model(AssetModel::getInstance()),
        m_logger(Logger::getInstance()),
        m_api(ApiServices::getInstance()) {
    m_timer = new QTimer(this);
    m_stockTable = new QStandardItemModel(this);
    m_cryptoTable = new QStandardItemModel(this);
    setupConnections();
    loadAssets();
    fetchAssets();

    // Single use timer to instantly update stats after dats is received
    QTimer::singleShot(250, this, [=]() {
        updateStats();
        m_timer->start(AppConstants::Pages::LIVE_UPDATE_INTERVAL); 
    });
}

void AssetsController::setupConnections() {
    // Data received from API
    connect(&m_api, &ApiServices::assetDataReceived, this, [this](const QString& symbol, const QJsonDocument& data) {
        QString newSym = symbol.contains(':') ? symbol.section(':', 1, 1) : symbol;
        int type = getType(symbol);
        if (type != -1) {
            // Update model
            if (!m_model.update(symbol, data["c"].toDouble()))
                m_logger.debugLog("AssetsController: Failed to update asset: " + symbol.toStdString(), "CONTROLLER", "ERR");
            
            // Update view
            updateTable(newSym, data["c"].toDouble(), data["d"].toDouble(), data["dp"].toDouble(), type);
        } else {
            m_logger.debugLog("AssetsController: Unable to determine type: " + symbol.toStdString(), "CONTROLLER", "ERR");
        }
    });

    // Data received from API (Error)
    connect(&m_api, &ApiServices::assetRequestFailed, this, [this](const QString& symbol, const QString& error) {
        m_logger.debugLog("AssetsController: Failed to retrieve asset: " + symbol.toStdString() + ", " + error.toStdString(), "CONTROLLER", "ERR");
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
        if (tableModel->item(row, AppConstants::Ui::SYMBOL)->text() == newSym) {
            tableModel->item(row, AppConstants::Ui::QUANTITY)->setText(
                Utils::formatNumberWithCommas(tableModel->item(row, AppConstants::Ui::QUANTITY)->text().toDouble() + quantity, 2));
            return true;
        }
    }

    int currRow = tableModel->rowCount();
    tableModel->insertRow(currRow);
    tableModel->setItem(currRow, AppConstants::Ui::SYMBOL, new QStandardItem(newSym));
    tableModel->setItem(currRow, AppConstants::Ui::QUANTITY, new QStandardItem(Utils::formatNumberWithCommas(quantity, 2)));
    tableModel->setItem(currRow, AppConstants::Ui::PRICE, new QStandardItem("Loading..."));
    tableModel->setItem(currRow, AppConstants::Ui::DAILY_CHANGE_PERCENT, new QStandardItem("Loading..."));
    tableModel->setItem(currRow, AppConstants::Ui::DAILY_CHANGE_DOLLAR, new QStandardItem("Loading..."));
    tableModel->setItem(currRow, AppConstants::Ui::TOTAL_VALUE, new QStandardItem("Loading..."));

    for (int i = 0; i < AppConstants::Ui::COLUMN_COUNT; ++i)
        tableModel->item(currRow, i)->setData(Qt::AlignCenter, Qt::TextAlignmentRole);

    // Fetch data
    m_api.getAsset(symbol);
    return true;
}

void AssetsController::updateTable(const QString& symbol, double price, double d, double dp, int type) {
    QStandardItemModel* model = (type ? m_cryptoTable : m_stockTable);
    QString newSym = symbol.contains(':') ? symbol.section(':', 1, 1) : symbol;
    for (int row = 0; row < model->rowCount(); row++) {
        if (model->item(row, AppConstants::Ui::SYMBOL)->text() == newSym) {
            double quantity = model->item(row, AppConstants::Ui::QUANTITY)->text().toDouble();

            // Update the table
            model->item(row, AppConstants::Ui::PRICE)->setText("$" + Utils::formatNumberWithCommas(price, 2));
            model->item(row, AppConstants::Ui::DAILY_CHANGE_PERCENT)->setText(Utils::formatNumberWithCommas(dp, 2) + "%");
            model->item(row, AppConstants::Ui::DAILY_CHANGE_DOLLAR)->setText("$" + Utils::formatNumberWithCommas(d * quantity, 2));
            model->item(row, AppConstants::Ui::TOTAL_VALUE)->setText("$" + Utils::formatNumberWithCommas(price * quantity, 2));

            QColor color = (d > 0) ? Qt::darkGreen : Qt::darkRed;
            model->item(row, AppConstants::Ui::DAILY_CHANGE_PERCENT)->setData(QBrush(color), Qt::ForegroundRole);
            model->item(row, AppConstants::Ui::DAILY_CHANGE_DOLLAR)->setData(QBrush(color), Qt::ForegroundRole);

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
    model->setHorizontalHeaderLabels(AppConstants::Pages::ASSET_HEADERS);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void AssetsController::updateStats() {
    double pvalue = 0, dchange = 0, invests = InvestsController::getInstance()->getTotal();
    for (int i = 0; i < m_stockTable->rowCount(); i++) {
        pvalue += m_stockTable->item(i, AppConstants::Ui::TOTAL_VALUE)->text().remove("$").remove(",").toDouble();
        dchange += m_stockTable->item(i, AppConstants::Ui::DAILY_CHANGE_DOLLAR)->text().remove("$").remove(",").toDouble();
    }

    for (int i = 0; i < m_cryptoTable->rowCount(); i++) {
        pvalue += m_cryptoTable->item(i, AppConstants::Ui::TOTAL_VALUE)->text().remove("$").remove(",").toDouble();
        dchange += m_cryptoTable->item(i, AppConstants::Ui::DAILY_CHANGE_DOLLAR)->text().remove("$").remove(",").toDouble();
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

        table->setItem(currRow, AppConstants::Ui::SYMBOL, new QStandardItem(symbol));
        table->setItem(currRow, AppConstants::Ui::QUANTITY, new QStandardItem(Utils::formatNumberWithCommas(item["quantity"].toDouble(), 2)));
        table->setItem(currRow, AppConstants::Ui::PRICE, new QStandardItem("Loading..."));
        table->setItem(currRow, AppConstants::Ui::DAILY_CHANGE_PERCENT, new QStandardItem("Loading..."));
        table->setItem(currRow, AppConstants::Ui::DAILY_CHANGE_DOLLAR, new QStandardItem("Loading..."));
        table->setItem(currRow, AppConstants::Ui::TOTAL_VALUE, new QStandardItem("Loading..."));

        // Cell settings
        for (int i = 0; i < AppConstants::Ui::COLUMN_COUNT; ++i) {
            table->item(currRow, i)->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        }
    }

    m_logger.debugLog("AssetsController: Loaded previous assets", "CONTROLLER", "INFO");
}

vector<QString> AssetsController::getLeadStocks() {
    vector<QString> stocks;
    vector<pair<double, int>> stockChanges;
    for (int row = 0; row < m_stockTable->rowCount(); row++) {
        if (m_stockTable->item(row, AppConstants::Ui::DAILY_CHANGE_PERCENT)) {
            double change = m_stockTable->item(row, AppConstants::Ui::DAILY_CHANGE_PERCENT)->text().remove("%").remove(",").toDouble();
            stockChanges.push_back(make_pair(change, row));
        }
    }
    
    // Sort by daily change percentage and get top 3
    sort(stockChanges.begin(), stockChanges.end(), [](const pair<double, int>& a, const pair<double, int>& b) { return a.first > b.first; });
    int numStocks = min(3, static_cast<int>(stockChanges.size()));
    
    for (int i = 0; i < numStocks; i++) {
        int rowIndex = stockChanges[i].second;
        if (m_stockTable->item(rowIndex, AppConstants::Ui::SYMBOL)) {
            QString stockInfo = m_stockTable->item(rowIndex, AppConstants::Ui::SYMBOL)->text();
            if (m_stockTable->item(rowIndex, AppConstants::Ui::PRICE))
                stockInfo += "|" + m_stockTable->item(rowIndex, AppConstants::Ui::PRICE)->text();
            if (m_stockTable->item(rowIndex, AppConstants::Ui::DAILY_CHANGE_PERCENT))
                stockInfo += "|" + m_stockTable->item(rowIndex, AppConstants::Ui::DAILY_CHANGE_PERCENT)->text();
            
            stocks.push_back(stockInfo);
        }
    }
    
    return stocks;
}