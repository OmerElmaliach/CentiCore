#include "MainPage.hpp"
#include "../../ui/ui_main_page.h"

MainPage::MainPage(QWidget *parent) :
        QMainWindow(parent),
        m_ui(new Ui::MainPage),
        m_logger(DebugUtils::getInstance()) {
    m_logger.debugLog("Performing MainPage UI setup", "VIEW", "INFO");
    m_ui->setupUi(this);

    // Setup expense model
    m_model = new QStringListModel();
    m_ui->expenseView->setModel(m_model);

    // Load functions and styles
    loadBtns();
    loadStyles(PAGE_UI);
    loadExpenses();

    // Load events
    WindowDragFilter* dragFilter = new WindowDragFilter(parent, this);
    m_ui->topbarWidget->installEventFilter(dragFilter);
    m_ui->topbarDisplay->installEventFilter(dragFilter);
    m_logger.debugLog("MainPage UI setup completed", "VIEW", "INFO");
}

MainPage::~MainPage() {
    delete m_ui;
}

void MainPage::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        m_logger.debugLog("Failed to load style file main_page", "VIEW", "ERR");
    }
}

void MainPage::loadBtns() {
    // Exit window button
    connect(m_ui->exit_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("Exit pressed, program shutdown...", "VIEW", "INFO");
        this->window()->close();
    });

    // Minimize window button
    connect(m_ui->minimize_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("Minimizing window", "VIEW", "INFO");
        this->window()->setWindowState(Qt::WindowMinimized);
    });

    // Add expense button
    connect(m_ui->addExpense_btn, &QPushButton::clicked, this, [this] {
        CreateExpenseDialog* dialog = new CreateExpenseDialog();
        connect(dialog, &CreateExpenseDialog::expenseCreated, this, &MainPage::onExpenseCreate);
        dialog->exec();
    });

    // Stocks page button
    connect(m_ui->stocks_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("Switching to stocks page", "VIEW", "INFO");
        emit switchPage(1); // Stock page index
    });
}

void MainPage::onExpenseCreate(const QString category, QString amount) {
    QStringList currList = m_model->stringList();
    double currTot = stod(m_ui->totExpNum->text().toStdString().c_str());

    // Update expense list
    currList.append(category + " " + amount + "$");
    m_model->setStringList(currList);
    m_ui->totExpNum->setText(QString::number(currTot + amount.toDouble()) + "$");

    m_logger.debugLog("Added expense to list", "VIEW", "INFO");
}

void MainPage::loadExpenses() {
    double sumExp = 0;
    m_ui->totExpNum->setText("0");
    QJsonArray data = ExpensesController::getInstance().getExpenses();
    QStringList curr = m_model->stringList();

    // Add each monthly expense
    for (int i = 0; i < data.size(); i++) {
        QJsonObject item = data[i].toObject();
        curr.append(item["category"].toString() + " " + QString::number(item["amount"].toDouble()) + "$");
        sumExp += item["amount"].toDouble();
    }

    m_ui->totExpNum->setText(QString::number(sumExp) + "$");
    m_model->setStringList(curr);
    m_logger.debugLog("Loaded previous monthly expenses", "VIEW", "INFO");
}