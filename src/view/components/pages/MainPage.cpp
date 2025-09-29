#include "MainPage.hpp"
#include "../../ui/ui_main_page.h"

MainPage::MainPage(QWidget *parent) :
        QMainWindow(parent),
        m_ui(new Ui::MainPage),
        m_logger(Logger::getInstance()), 
        m_expense_cont(ExpensesController::getInstance()) {
    m_logger.debugLog("MainPage: Performing UI setup", "VIEW", "INFO");
    m_ui->setupUi(this);

    // Setup expense model
    m_ui->expenseView->setModel(m_expense_cont->getList());

    // Load functions and styles
    setupConnections();
    setupChart();
    if (!Utils::loadStyles(this, AppConstants::Ui::MAIN_PAGE_UI))
        m_logger.debugLog("MainPage: Failed to load style file main_page", "VIEW", "ERR");
    if (!Utils::loadStyles(m_ui->topbarWidget, AppConstants::Ui::TOPBAR_UI))
        m_logger.debugLog("MainPage: Failed to load style for topbar", "VIEW", "ERR");
    if (!Utils::loadStyles(m_ui->pageWidget, AppConstants::Ui::PAGES_WIDGET_UI))
        m_logger.debugLog("MainPage: Failed to load style for pages widget", "VIEW", "ERR");
    if (!Utils::loadStyles(m_ui->leadWidget, AppConstants::Ui::LEAD_STOCKS_UI))
        m_logger.debugLog("MainPage: Failed to load style for leading stocks widget", "VIEW", "ERR");
    
    // Load page stats and expenses
    m_expense_cont->loadExpenses();
    m_ui->cashNum->setText("$" + Utils::formatNumberWithCommas(EnvLoader::getValue("AVAILABLE_CASH").toDouble(), 2));
    m_ui->cashNum->setStyleSheet("color: " + AppConstants::Colors::POSITIVE_COLOR);
    m_ui->networthNum->setText("Loading...");

    // Load events
    WindowDragFilter* dragFilter = new WindowDragFilter(parent, this);
    m_ui->topbarWidget->installEventFilter(dragFilter);
    m_ui->topbarDisplay->installEventFilter(dragFilter);
    m_logger.debugLog("MainPage: UI setup completed", "VIEW", "INFO");
}

void MainPage::setupChart() {
    QVBoxLayout* layout = new QVBoxLayout(m_ui->graphWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_chart = new ExpenseChart(m_expense_cont->getYear(QDateTime::currentDateTime().toString("yyyy")), this);
    m_chart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(m_chart);
}

void MainPage::setupConnections() {
    // Exit window button
    connect(m_ui->exit_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("MainPage: Exit pressed, program shutdown...", "VIEW", "INFO");
        this->window()->close();
    });

    // Minimize window button
    connect(m_ui->minimize_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("MainPage: Minimizing window", "VIEW", "INFO");
        this->window()->setWindowState(Qt::WindowMinimized);
    });

    // Add expense button
    connect(m_ui->addExpense_btn, &QPushButton::clicked, this, [this] {
        CreateExpenseDialog dialog(this);
        dialog.exec();
    });

    // Stocks page button
    connect(m_ui->stocks_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("MainPage: Switching to stocks page", "VIEW", "INFO");
        emit switchPage(AppConstants::Pages::STOCKS_PAGE);
    });

    // Stats page button
    connect(m_ui->stats_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("MainPage: Switching to stats page", "VIEW", "INFO");
        emit switchPage(AppConstants::Pages::STATS_PAGE);
    });

    // Get help button
    connect(m_ui->getHelp_btn, &QPushButton::clicked, this, [this] {
        QDesktopServices::openUrl(QUrl(AppConstants::Config::GITHUB_URL));
    });

    connect(m_expense_cont, &ExpensesController::expenseCreated, this, &MainPage::onExpenseCreate);
    connect(m_expense_cont, &ExpensesController::expensesLoaded, this, &MainPage::onLoadExpenses);
    connect(AssetsController::getInstance(), &AssetsController::updatedStats, this, &MainPage::onUpdateStats);
}

void MainPage::onExpenseCreate(const QString category, double amount) {
    double total = m_ui->totExpNum->text().remove('$').toDouble() + amount;
    // Update total
    m_ui->totExpNum->setText("$" +  QString::number(total));

    // Update chart
    m_chart->refreshMonth(QDateTime::currentDateTime().toString("MM").toDouble() - 1, total);

    // Update stat
    double newbalance = m_ui->balanceNum->text().remove("$").remove(",").remove("+").remove("-").toDouble() - amount;
    m_ui->balanceNum->setText(((newbalance >= 0) ? "+ $" : "- $") + Utils::formatNumberWithCommas(abs(newbalance), 2));
    m_ui->balanceNum->setStyleSheet("color: " + ((newbalance >= 0) ? AppConstants::Colors::POSITIVE_COLOR : AppConstants::Colors::NEGATIVE_COLOR));

    m_logger.debugLog("MainPage: Added expense to list: " + category.toStdString(), "VIEW", "INFO");
}

void MainPage::onLoadExpenses(double totalExp) {
    m_ui->totExpNum->setText("$" + QString::number(totalExp));

    // Update stats
    QSettings settings(":/config/config/app.conf", QSettings::IniFormat);
    settings.beginGroup("Finance");
    double balance = settings.value("monthly_budget").toDouble() - totalExp;
    m_ui->balanceNum->setText(((balance >= 0) ? "+ $" : "- $") + Utils::formatNumberWithCommas(abs(balance), 2));
    m_ui->balanceNum->setStyleSheet("color: " + ((balance >= 0) ? AppConstants::Colors::POSITIVE_COLOR : AppConstants::Colors::NEGATIVE_COLOR));

    m_logger.debugLog("MainPage: Loaded total monthly expenses", "VIEW", "INFO");
}

void MainPage::onUpdateStats(double pvalue) {
    // Update total networth
    double networth = pvalue + m_ui->cashNum->text().remove("$").remove(",").toDouble();
    m_ui->networthNum->setText("$" + Utils::formatNumberWithCommas(networth, 2));
    m_ui->networthNum->setStyleSheet("color: " + ((networth >= 0) ? AppConstants::Colors::POSITIVE_COLOR : AppConstants::Colors::NEGATIVE_COLOR));

    // Update leading stocks
    vector<QString> leadStocks = AssetsController::getInstance()->getLeadStocks();
    QLabel* stockLabels[] = {m_ui->stock_1, m_ui->stock_2, m_ui->stock_3};
    QLabel* priceLabels[] = {m_ui->price_1, m_ui->price_2, m_ui->price_3};
    QLabel* perLabels[] = {m_ui->per_1, m_ui->per_2, m_ui->per_3};
    
    for (int i = 0; i < leadStocks.size(); i++) {
        QStringList stockData = leadStocks[i].split("|");
        if (stockData.size() < 3) {
            m_logger.debugLog("MainPage: Invalid stock data format at index: " + i, "VIEW", "WARN");
            continue;
        }

        QString symbol = stockData[0], price = stockData[1], changePercent = stockData[2];
        QString percentForParsing = changePercent;
        percentForParsing = percentForParsing.remove("%").remove("+");

        // Update UI
        bool isPositive = (percentForParsing.toDouble() >= 0);
        stockLabels[i]->setText(symbol);
        priceLabels[i]->setText(price);
        perLabels[i]->setText((isPositive ? "▲ +" : "▼ ") + changePercent);
        perLabels[i]->setStyleSheet(isPositive ?
             "background-color: rgba(0, 200, 100, 25); color: green" : 
             "background-color: rgba(200, 0, 50, 25); color: #ff4757");
    }
}