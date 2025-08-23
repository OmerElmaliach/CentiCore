#include "MainInterface.hpp"
#include "../ui/ui_main_interface.h"

MainInterface::MainInterface(QWidget *parent) :
        QMainWindow(parent),
        m_ui(new Ui::MainInterface),
        m_logger(DebugUtils::getInstance()) {
    m_logger.debugLog("Performing MainInterface UI setup", "VIEW", "INFO");
    m_ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    // Setup expense model
    m_model = new QStringListModel();
    m_ui->expenseView->setModel(m_model);

    // Load functions and styles
    loadBtns();
    loadStyles(INTERFACE_UI);
    loadExpenses();

    // Load events
    WindowDragFilter* dragFilter = new WindowDragFilter(this, this);
    m_ui->topbarWidget->installEventFilter(dragFilter);
    m_ui->topbarDisplay->installEventFilter(dragFilter);
    m_logger.debugLog("MainInterface UI setup completed", "VIEW", "INFO");
}

MainInterface::~MainInterface() {
    delete m_ui;
}

void MainInterface::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        m_logger.debugLog("Failed to load style file for main_interface", "VIEW", "ERROR");
    }
}

void MainInterface::loadBtns() {
    // Exit window button.
    connect(m_ui->exit_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("Exit pressed, program shutdown...", "VIEW", "INFO");
        exit(0);
    });

    // Minimize window button.
    connect(m_ui->minimize_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("Minimizing window", "VIEW", "INFO");
        setWindowState(Qt::WindowMinimized);
    });

    // Add expense button.
    connect(m_ui->addExpense_btn, &QPushButton::clicked, this, [this] {
        CreateExpenseDialog* dialog = new CreateExpenseDialog();
        connect(dialog, &CreateExpenseDialog::expenseCreated, this, &MainInterface::onExpenseCreate);
        dialog->exec();
    });
}

void MainInterface::onExpenseCreate(const QString name, QString amount) {
    QStringList curr = m_model->stringList();
    curr.append(name + " " + amount + "$");
    m_model->setStringList(curr);
    m_logger.debugLog("Added expense to list", "VIEW", "INFO");
}

void MainInterface::loadExpenses() {
    QJsonArray data = ExpensesController::getInstance().getExpenses();
    QStringList curr = m_model->stringList();
    for (int i = 0; i < data.size(); i++) {
        QJsonObject item = data[i].toObject();
        curr.append(item["name"].toString() + " " + QString::number(item["amount"].toDouble()) + "$");
    }

    m_model->setStringList(curr);
    m_logger.debugLog("Loaded previous monthly expenses", "VIEW", "INFO");
}