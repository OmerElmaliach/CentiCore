#include "CreateExpenseDialog.hpp"
#include "../ui/ui_create_expense.h"

CreateExpenseDialog::CreateExpenseDialog(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::CreateExpenseDialog),
        m_logger(DebugUtils::getInstance()) {
    m_logger.debugLog("Creating QDialog Expense...", "VIEW", "INFO");
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
        m_logger.debugLog("Failed to load style file for Expense Dialog", "VIEW", "ERROR");
    }
}

void CreateExpenseDialog::accept() {
    // Send a request to add an expense
    ExpensesController* ec = new ExpensesController();
    bool isNumber;
    QString category = m_ui->categoryInput->text(), amount = m_ui->amountInput->text();
    amount.toDouble(&isNumber);

    // Check if fields are invalid
    if (category.isEmpty() || !isNumber) {
        QDialog::accept();
        return;
    }

    bool wasAdded = ec->add(QDateTime().currentDateTime().toString("dd-hh").toStdString(), category.toStdString(), amount.toDouble());
    delete ec;

    if (wasAdded) {
        emit expenseCreated(category, amount); 
    }

    QDialog::accept();
}