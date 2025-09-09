#include "CreateInvestDialog.hpp"
#include "../../ui/ui_create_invest.h"

CreateInvestDialog::CreateInvestDialog(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::CreateInvestDialog),
        m_logger(DebugUtils::getInstance()) {
    m_logger.debugLog("Creating QDialog Invest...", "VIEW", "INFO");
    m_ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    m_ui->dateInput->setDate(QDate::currentDate());
    loadStyles(DIALOG_UI);

    WindowDragFilter *dragFilter = new WindowDragFilter(this, this);
    m_ui->topbarLabel->installEventFilter(dragFilter);
    connect(m_ui->createBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_ui->cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

CreateInvestDialog::~CreateInvestDialog() {
    delete m_ui;
}

void CreateInvestDialog::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);  
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        m_logger.debugLog("Failed to load style file for Expense Dialog", "VIEW", "ERR");
    }
}

void CreateInvestDialog::accept() {
    // Send a request to add an investment
    bool isNumber;
    QString amount = m_ui->amountInput->text();
    amount.toDouble(&isNumber);

    // Check if fields are invalid
    if (!isNumber) {
        m_logger.debugLog("Fields do not meet the requirements", "VIEW", "WARN");
        QDialog::accept();
        return;
    }

    bool wasAdded = InvestsController::getInstance().add(amount.toDouble(), m_ui->dateInput->dateTime().toString("dd/MM/yy"));

    if (wasAdded) {
        emit investCreated(amount.toDouble()); 
    }

    QDialog::accept();
}