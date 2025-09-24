#include "CreateExpenseDialog.hpp"
#include "../../ui/ui_create_expense.h"

CreateExpenseDialog::CreateExpenseDialog(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::CreateExpenseDialog),
        m_logger(Logger::getInstance()) {
    m_logger.debugLog("CreateExpenseDialog: Creating QDialog Expense...", "VIEW", "INFO");
    m_ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    Utils::loadStyles(this, AppConstants::Ui::DIALOG_UI);

    m_ui->categoryInput->addItems(AppConstants::Pages::EXPENSE_CATEGORIES);

    WindowDragFilter *dragFilter = new WindowDragFilter(this, this);
    m_ui->topbarLabel->installEventFilter(dragFilter);
    connect(m_ui->createBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_ui->cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

void CreateExpenseDialog::accept() {
    // Send a request to add an expense
    bool isNumber;
    QString category = m_ui->categoryInput->currentText(), amount = m_ui->amountInput->text();
    amount.toDouble(&isNumber);

    // Check if fields are invalid
    if (category.isEmpty() || !isNumber || amount.toDouble() < 0) {
        m_logger.debugLog("CreateExpenseDialog: Fields do not meet the requirements", "VIEW", "WARN");
        QDialog::accept();
        return;
    }

    bool wasAdded = ExpensesController::getInstance()->add(category, amount.toDouble(), QDateTime().currentDateTime().toString("dd"));
    if (!wasAdded)
        m_logger.debugLog("CreateExpenseDialog: Failed to create new expense: " + category.toStdString(), "VIEW", "WARN");

    QDialog::accept();
}