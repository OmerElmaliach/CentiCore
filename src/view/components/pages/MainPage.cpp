#include "MainPage.hpp"
#include "../../ui/ui_main_page.h"

const int MainPage::STOCKS_PAGE = 1;
const QString MainPage::POSITIVE_COLOR = "#28a745";
const QString MainPage::NEGATIVE_COLOR = "#dc3545";
const QString MainPage::PAGE_UI = ":/styles/qss/main_page.qss";
const QString MainPage::TOPBAR_UI = ":/styles/qss/topbar.qss";
const QString MainPage::PAGES_WIDGET_UI = ":/styles/qss/page_widget.qss";

MainPage::MainPage(QWidget *parent) :
        QMainWindow(parent),
        m_ui(new Ui::MainPage),
        m_logger(DebugUtils::getInstance()),
        m_utils(GeneralUtils::getInstance()), 
        m_expense_cont(ExpensesController::getInstance()) {
    m_logger.debugLog("MainPage: Performing UI setup", "VIEW", "INFO");
    m_ui->setupUi(this);

    // Setup expense model
    m_ui->expenseView->setModel(m_expense_cont->getList());

    // Load functions and styles
    setupConnections();
    setupChart();
    if (!m_utils->loadStyles(this, PAGE_UI))
        m_logger.debugLog("MainPage: Failed to load style file main_page.ui", "VIEW", "ERR");
    if (!m_utils->loadStyles(m_ui->topbarWidget, TOPBAR_UI))
        m_logger.debugLog("MainPage: Failed to load style for topbar", "VIEW", "ERR");
    if (!m_utils->loadStyles(m_ui->pageWidget, PAGES_WIDGET_UI))
        m_logger.debugLog("MainPage: Failed to load style for pages widget", "VIEW", "ERR");
    
    // Load page stats and expenses
    m_expense_cont->loadExpenses();
    EnvLoader env;
    m_ui->cashNum->setText(m_utils->formatNumberWithCommas(env.getValue("AVAILABLE_CASH").toDouble(), 2) + " $");
    m_ui->cashNum->setStyleSheet("color: " + POSITIVE_COLOR);
    m_ui->networthNum->setText("Loading...");

    // Load events
    WindowDragFilter* dragFilter = new WindowDragFilter(parent, this);
    m_ui->topbarWidget->installEventFilter(dragFilter);
    m_ui->topbarDisplay->installEventFilter(dragFilter);
    m_logger.debugLog("MainPage: UI setup completed", "VIEW", "INFO");
}

void MainPage::setupChart() {
    QVBoxLayout *layout = new QVBoxLayout(m_ui->graphWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    ExpenseChart *chart = new ExpenseChart(m_expense_cont->getYear("2025"), this);
    chart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(chart);
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
        emit switchPage(STOCKS_PAGE);
    });

    connect(m_expense_cont, &ExpensesController::expenseCreated, this, &MainPage::onExpenseCreate);
    connect(m_expense_cont, &ExpensesController::expensesLoaded, this, &MainPage::onLoadExpenses);
    connect(AssetsController::getInstance(), &AssetsController::updatedStats, this, &MainPage::onUpdateStats);
}

void MainPage::onExpenseCreate(const QString category, double amount) {
    double currTot = m_ui->totExpNum->text().remove('$').toDouble();
    m_ui->totExpNum->setText(QString::number(currTot + amount) + " $");
    m_logger.debugLog("MainPage: Added expense to list: " + category.toStdString(), "VIEW", "INFO");
}

void MainPage::onLoadExpenses(double totalExp) {
    m_ui->totExpNum->setText(QString::number(totalExp) + " $");

    // Update stats
    QSettings settings(":/config/config/app.conf", QSettings::IniFormat);
    settings.beginGroup("Finance");
    double balance = settings.value("monthly_budget").toDouble() - totalExp;
    m_ui->balanceNum->setText(((balance >= 0) ? "+ " : "- ") + m_utils->formatNumberWithCommas(abs(balance), 2) + " $");
    m_ui->balanceNum->setStyleSheet("color: " + ((balance >= 0) ? POSITIVE_COLOR : NEGATIVE_COLOR));

    m_logger.debugLog("MainPage: Loaded total monthly expenses", "VIEW", "INFO");
}

void MainPage::onUpdateStats(double pvalue) {
    double networth = pvalue + m_ui->cashNum->text().remove("$").remove(",").toDouble();
    m_ui->networthNum->setText(m_utils->formatNumberWithCommas(networth, 2) + " $");
    m_ui->networthNum->setStyleSheet("color: " + ((networth >= 0) ? POSITIVE_COLOR : NEGATIVE_COLOR));
}