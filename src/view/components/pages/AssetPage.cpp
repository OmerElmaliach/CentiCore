#include "AssetPage.hpp"
#include "../../ui/ui_asset_page.h"

AssetPage::AssetPage(QWidget *parent) :
        QMainWindow(parent),
        m_ui(new Ui::AssetPage),
        m_logger(DebugUtils::getInstance()) {
    m_logger.debugLog("AssetPage: Performing UI setup", "VIEW", "INFO");
    m_ui->setupUi(this);

    // Setup assets model
    setupAssetModel(m_stock_model, m_ui->stocksView);
    setupAssetModel(m_crypto_model, m_ui->cryptoView);

    m_invest_model = new QStringListModel(this);
    m_ui->investsView->setModel(m_invest_model);

    // Load functions and styles
    loadBtns();
    loadStyles(PAGE_UI);
    loadAssets();
    loadInvests();

    // Load events
    WindowDragFilter* dragFilter = new WindowDragFilter(parent, this);
    m_ui->topbarWidget->installEventFilter(dragFilter);
    m_ui->topbarDisplay->installEventFilter(dragFilter);
    m_logger.debugLog("AssetPage: UI setup completed", "VIEW", "INFO");

    connect(&AssetsController::getInstance(), &AssetsController::updateAsset, this, &AssetPage::updateAsset);
    connect(&AssetsController::getInstance(), &AssetsController::updateStats, this, &AssetPage::updateStats);

    // Start regulary updating data
    AssetsController::getInstance().update();
}

AssetPage::~AssetPage() {
    delete m_ui;
}

void AssetPage::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        m_logger.debugLog("AssetPage: Failed to load style file stocks.ui", "VIEW", "ERR");
    }
}

void AssetPage::loadBtns() {
    // Exit window button
    connect(m_ui->exit_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("AssetPage: Exit pressed, program shutdown...", "VIEW", "INFO");
        this->window()->close();
    });

    // Minimize window button
    connect(m_ui->minimize_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("AssetPage: Minimizing window", "VIEW", "INFO");
        this->window()->setWindowState(Qt::WindowMinimized);
    });

    // Move to dashboard
    connect(m_ui->dashBoard_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("AssetPage: Switching to dashboard page", "VIEW", "INFO");
        emit switchPage(0);
    });

    // Add stock button
    connect(m_ui->addStock_btn, &QPushButton::clicked, this, [this] {
        CreateAssetDialog dialog(0, this);
        connect(&dialog, &CreateAssetDialog::assetCreated, this, &AssetPage::onAssetCreate);
        dialog.exec();
    });

    // Add crypto button
    connect(m_ui->addCrypto_btn, &QPushButton::clicked, this, [this] {
        CreateAssetDialog dialog(1, this);
        connect(&dialog, &CreateAssetDialog::assetCreated, this, &AssetPage::onAssetCreate);
        dialog.exec();
    });

    // Add investment button
    connect(m_ui->addInvest_btn, &QPushButton::clicked, this, [this] {
        CreateInvestDialog dialog(this);
        connect(&dialog, &CreateInvestDialog::investCreated, this, &AssetPage::onInvestCreate);
        dialog.exec();
    });
}

void AssetPage::onAssetCreate(const QString symbol, QString quantity, int type) {
    // Update assets list
    QStandardItemModel* model = (type) ? m_crypto_model : m_stock_model;
    int currRow = model->rowCount();
    model->setItem(currRow, SYMBOL, new QStandardItem(symbol));
    model->setItem(currRow, QUANTITY, new QStandardItem(formatNumberWithCommas(quantity.toDouble())));
    model->setItem(currRow, PRICE, new QStandardItem("N/A"));
    model->setItem(currRow, DAILY_CHANGE_PERCENT, new QStandardItem("N/A"));
    model->setItem(currRow, DAILY_CHANGE_DOLLAR, new QStandardItem("N/A"));
    model->setItem(currRow, TOTAL_VALUE, new QStandardItem("N/A"));

    for (int i = 0; i < COLUMN_COUNT; ++i) {
        model->item(currRow, i)->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    m_logger.debugLog("AssetPage: Added asset to list", "VIEW", "INFO");
}

void AssetPage::loadAssets() {
    QJsonArray data = AssetsController::getInstance().getAssets();

    // Add each asset
    for (int i = 0; i < data.size(); i++) {
        QJsonObject item = data[i].toObject();
        QStandardItemModel* model = (item["type"].toInt()) ? m_crypto_model : m_stock_model;
        int currRow = model->rowCount();
        QString symbol = item["symbol"].toString().contains(':') ? item["symbol"].toString().section(':', 1, 1) : item["symbol"].toString();

        model->setItem(currRow, SYMBOL, new QStandardItem(symbol));
        model->setItem(currRow, QUANTITY, new QStandardItem(formatNumberWithCommas(item["quantity"].toDouble())));
        // TODO: ADD VALUES WITH SJON REQUEST
        model->setItem(currRow, PRICE, new QStandardItem("N/A"));
        model->setItem(currRow, DAILY_CHANGE_PERCENT, new QStandardItem("N/A"));
        model->setItem(currRow, DAILY_CHANGE_DOLLAR, new QStandardItem("N/A"));
        model->setItem(currRow, TOTAL_VALUE, new QStandardItem("N/A"));

        // Cell settings
        for (int i = 0; i < COLUMN_COUNT; ++i) {
            model->item(currRow, i)->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        }
    }

    m_logger.debugLog("AssetPage: Loaded previous assets", "VIEW", "INFO");
}

void AssetPage::updateAsset(QString symbol, double currPrice, double d, double dp, int type) {
    QStandardItemModel* model = (type) ? m_crypto_model : m_stock_model;
    QString newSym = symbol.contains(':') ? symbol.section(':', 1, 1) : symbol;

    for (int i = 0; i < model->rowCount(); i++) {
        if (model->item(i, SYMBOL)->text() == newSym) {
            model->item(i, PRICE)->setText(formatNumberWithCommas(currPrice) + "  $");
            model->item(i, DAILY_CHANGE_PERCENT)->setText(QString::number(dp, 'f', 2) + "  %");
            model->item(i, DAILY_CHANGE_DOLLAR)->setText(formatNumberWithCommas(d * model->item(i, QUANTITY)->text().toDouble()) + "  $");
            QStandardItem* quantityItem = model->item(i, QUANTITY);
            if (quantityItem) {
                bool ok;
                double quantity = quantityItem->text().toDouble(&ok);
                if (ok) {
                    model->item(i, TOTAL_VALUE)->setText(formatNumberWithCommas(currPrice * quantity) + "  $");
                    
                    QColor color = (d > 0) ? Qt::darkGreen : Qt::darkRed;
                    model->item(i, DAILY_CHANGE_PERCENT)->setData(QBrush(color), Qt::ForegroundRole);
                    model->item(i, DAILY_CHANGE_DOLLAR)->setData(QBrush(color), Qt::ForegroundRole);
                    break;
                }
            }

            model->setItem(i, TOTAL_VALUE, new QStandardItem("N/A"));
            break;
        }
    }
}

void AssetPage::onInvestCreate(double amount) {
    QStringList currList = m_invest_model->stringList();
    double currTot = m_ui->investsNum->text().remove('$').toDouble();

    // Update investment list
    currList.append(QString::number(amount) + "$");
    m_invest_model->setStringList(currList);
    m_ui->investsNum->setText(QString::number(currTot + amount) + "$");

    m_logger.debugLog("AssetPage: Added investment to list", "VIEW", "INFO");
}

void AssetPage::loadInvests() {
    double sumInv = 0;
    m_ui->investsNum->setText("0");
    QJsonArray data = InvestsController::getInstance().getInvestments();
    QStringList curr = m_invest_model->stringList();

    // Add each investment made
    for (int i = 0; i < data.size(); i++) {
        QJsonObject item = data[i].toObject();
        curr.append(QString::number(item["amount"].toDouble()) + "$");
        sumInv += item["amount"].toDouble();
    }

    m_ui->investsNum->setText(QString::number(sumInv) + "$");
    m_invest_model->setStringList(curr);
    m_logger.debugLog("AssetPage: Loaded previous investments", "VIEW", "INFO");
}

void AssetPage::setupAssetModel(QStandardItemModel*& model, QTableView* view) {
    QStringList headers = {"Symbol", "Quantity", "Price per Unit", 
                          "Daily change (%)", "Daily change ($)", "Total Value"};
    model = new QStandardItemModel(this);
    view->setModel(model);
    model->setHorizontalHeaderLabels(headers);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

QString AssetPage::formatNumberWithCommas(const double num) {
    QLocale locale(QLocale::English, QLocale::UnitedStates);
    return locale.toString(num, 'f', 2);
}

void AssetPage::updateStats() {
    double pvalue = 0, dchange = 0, invests = InvestsController::getInstance().getSum();
    for (int i = 0; i < m_stock_model->rowCount(); i++) {
        pvalue += m_stock_model->item(i, TOTAL_VALUE)->text().remove("$").remove(",").toDouble();
        dchange += m_stock_model->item(i, DAILY_CHANGE_DOLLAR)->text().remove("$").remove(",").toDouble();
    }

    for (int i = 0; i < m_crypto_model->rowCount(); i++) {
        pvalue += m_crypto_model->item(i, TOTAL_VALUE)->text().remove("$").remove(",").toDouble();
        dchange += m_crypto_model->item(i, DAILY_CHANGE_DOLLAR)->text().remove("$").remove(",").toDouble();
    }

    m_ui->valueNum->setText(formatNumberWithCommas(pvalue) + " $");
    m_ui->balanceNum->setText(formatNumberWithCommas(pvalue - invests) + " $");
    m_ui->changeNum->setText(formatNumberWithCommas(dchange) + " $");
}