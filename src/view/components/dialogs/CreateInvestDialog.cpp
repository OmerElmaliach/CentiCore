#include "CreateInvestDialog.hpp"
#include "../../ui/ui_create_invest.h"

CreateInvestDialog::CreateInvestDialog(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::CreateInvestDialog),
        m_logger(DebugUtils::getInstance()) {
    m_logger.debugLog("CreateInvestDialog: Creating QDialog Invest...", "VIEW", "INFO");
    m_ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    m_ui->dateInput->setDate(QDate::currentDate());
    GeneralUtils::getInstance()->loadStyles(this, DIALOG_UI);

    WindowDragFilter *dragFilter = new WindowDragFilter(this, this);
    m_ui->topbarLabel->installEventFilter(dragFilter);
    connect(m_ui->createBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_ui->cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

void CreateInvestDialog::accept() {
    // Send a request to add an investment
    bool isNumber;
    QString amount = m_ui->amountInput->text();
    amount.toDouble(&isNumber);

    // Check if fields are invalid
    if (!isNumber) {
        m_logger.debugLog("CreateInvestDialog: Fields do not meet the requirements", "VIEW", "WARN");
        QDialog::accept();
        return;
    }

    bool wasAdded = InvestsController::getInstance()->add(amount.toDouble(), m_ui->dateInput->dateTime().toString("dd/MM/yy"));
    if (!wasAdded)
        m_logger.debugLog("CreateInvestDialog: Failed to add investment", "VIEW", "WARN");

    QDialog::accept();
}