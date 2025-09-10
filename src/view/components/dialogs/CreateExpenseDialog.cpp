#include "CreateExpenseDialog.hpp"
#include "../../ui/ui_create_expense.h"

CreateExpenseDialog::CreateExpenseDialog(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::CreateExpenseDialog),
        m_logger(DebugUtils::getInstance()) {
    m_logger.debugLog("CreateExpenseDialog: Creating QDialog Expense...", "VIEW", "INFO");
    m_ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    loadStyles(DIALOG_UI);

    WindowDragFilter *dragFilter = new WindowDragFilter(this, this);
    m_ui->topbarLabel->installEventFilter(dragFilter);
    connect(m_ui->createBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_ui->cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

CreateExpenseDialog::~CreateExpenseDialog() {
    delete m_ui;
}

void CreateExpenseDialog::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);  
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        m_logger.debugLog("CreateExpenseDialog: Failed to load style file for Expense Dialog", "VIEW", "ERR");
    }
}

void CreateExpenseDialog::accept() {
    // Send a request to add an expense
    bool isNumber;
    QString category = m_ui->categoryInput->text(), amount = m_ui->amountInput->text();
    amount.toDouble(&isNumber);

    // Check if fields are invalid
    if (category.isEmpty() || !isNumber || amount.toDouble() < 0) {
        m_logger.debugLog("CreateExpenseDialog: Fields do not meet the requirements", "VIEW", "WARN");
        QDialog::accept();
        return;
    }

    bool wasAdded = ExpensesController::getInstance().add(category, amount.toDouble(), QDateTime().currentDateTime().toString("dd"));

    if (wasAdded) {
        emit expenseCreated(category, amount); 
    }

    QDialog::accept();
}