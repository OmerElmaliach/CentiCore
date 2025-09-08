#pragma once

#include <QDialog>
#include <QMouseEvent>
#include <QDateTime>
#include "DebugUtils.hpp"
#include "WindowDragFilter.hpp"
#include "AssetsController.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CreateAssetDialog; }
QT_END_NAMESPACE

class CreateAssetDialog : public QDialog {
    Q_OBJECT

private:
    const char* DIALOG_UI = ":/styles/qss/create_asset.qss";
    Ui::CreateAssetDialog *m_ui;
    DebugUtils& m_logger;
    int m_type;

public:
    /**
     * @brief Constructor function for qdialog.
     */
    explicit CreateAssetDialog(int type, QWidget *parent = nullptr);

    /**
     * @brief Deconstructor function for qdialog.
     */
    ~CreateAssetDialog();

    /**
     * @brief Loads the qss into the ui file.
     */
    void loadStyles(const char* stylePath);

    /**
     * @brief Handles asset creation upon accept.
     */
    void accept() override;

signals:
    void assetCreated(const QString symbol, QString shares, int type);
};
