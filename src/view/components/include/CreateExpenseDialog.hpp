#pragma once

#include <QDialog>
#include <QDateTime>
#include "DebugUtils.hpp"
#include "WindowDragFilter.hpp"
#include "ExpensesController.hpp"
#include "GeneralUtils.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CreateExpenseDialog; }
QT_END_NAMESPACE

/**
 * @class CreateExpenseDialog
 * @brief Modal dialog for creating new expense records within the application.
 * 
 * CreateExpenseDialog provides a user interface for recording and creating new
 * expense entries. The dialog includes date/time handling, input validation,
 * error handling, and integrates with the application's expense management system.
 */
class CreateExpenseDialog : public QDialog {
    Q_OBJECT
    
private:
    const char* DIALOG_UI = ":/styles/qss/dialog_box.qss";
    Ui::CreateExpenseDialog *m_ui;
    DebugUtils& m_logger;

public:
    /**
     * @brief Constructs a new expense creation dialog.
     * 
     * Initializes the dialog for creating new expense records. Sets up the
     * user interface with current date/time defaults, applies custom styling,
     * configures window properties, and establishes necessary connections.
     * The dialog is prepared with appropriate input fields for expense data
     * entry including amount, description, category, and date information.
     * 
     * @param parent Optional parent widget for proper dialog positioning
     *               and memory management. Defaults to nullptr for
     *               application-level modal behavior.
     */
    CreateExpenseDialog(QWidget *parent = nullptr);
    
    /**
     * @brief Handles dialog acceptance and initiates expense creation.
     * 
     * Overrides QDialog::accept() to perform custom validation and expense
     * creation logic before closing the dialog. Validates user input including
     * expense amounts, dates, and required fields, then creates the expense
     * record through ExpensesController. Handles errors and provides
     * appropriate user feedback for validation failures or creation issues.
     */
    void accept() override;
};