#include "MainPage.hpp"
#include "../../ui/ui_main_page.h"

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
    if (!m_utils->loadStyles(this, PAGE_UI))
        m_logger.debugLog("MainPage: Failed to load style file main_page.ui", "VIEW", "ERR");
    m_expense_cont->loadExpenses();

    // Load events
    WindowDragFilter* dragFilter = new WindowDragFilter(parent, this);
    m_ui->topbarWidget->installEventFilter(dragFilter);
    m_ui->topbarDisplay->installEventFilter(dragFilter);
    m_logger.debugLog("MainPage: UI setup completed", "VIEW", "INFO");
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
}

void MainPage::onExpenseCreate(const QString category, double amount) {
    double currTot = m_ui->totExpNum->text().remove('$').toDouble();
    m_ui->totExpNum->setText(QString::number(currTot + amount) + " $");
    m_logger.debugLog("MainPage: Added expense to list: " + category.toStdString(), "VIEW", "INFO");
}

void MainPage::onLoadExpenses(double totalExp) {
    m_ui->totExpNum->setText(QString::number(totalExp) + " $");
    m_logger.debugLog("MainPage: Loaded total monthly expenses", "VIEW", "INFO");
}