#pragma once

#include <QObject>
#include "ExpensesController.hpp"
#include "DebugUtils.hpp"
class MainInterface;

class AppController : public QObject {
    Q_OBJECT

private:
    MainInterface* m_view;
    DebugUtils& m_logger;

public:
    /**
     * Constructor for the app controller.
     */
    AppController();

    /**
     * Routes all signals to proper functions in controllers.
     */
    void route();

    /**
     * Links a view to the controller.
     */
    void setView(MainInterface* view);
};