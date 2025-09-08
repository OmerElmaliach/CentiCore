#pragma once

#include <QDialog>
#include <QMouseEvent>
#include <QDateTime>
#include "DebugUtils.hpp"
#include "WindowDragFilter.hpp"
#include "ExpensesController.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CreateExpenseDialog; }
QT_END_NAMESPACE

class CreateExpenseDialog : public QDialog {
    Q_OBJECT

private:
    const char* DIALOG_UI = ":/styles/qss/dialog_box.qss";
    Ui::CreateExpenseDialog *m_ui;
    DebugUtils& m_logger;

public:
    /**
     * @brief Constructor function for qdialog.
     */
    explicit CreateExpenseDialog(QWidget *parent = nullptr);

    /**
     * @brief Deconstructor function for qdialog.
     */
    ~CreateExpenseDialog();

    /**
     * @brief Loads the qss into the ui file.
     */
    void loadStyles(const char* stylePath);

    /**
     * @brief Handles expense creation upon accept.
     */
    void accept() override;

signals:
    void expenseCreated(const QString name, QString amount);
};
