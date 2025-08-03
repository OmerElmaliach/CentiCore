#pragma once

#include <QObject>
#include "../../view/components/include/MainInterface.hpp"
#include "../../utils/DebugUtils.hpp"

class AppController : public QObject {
    Q_OBJECT

private:
    MainInterface* m_view;
    DebugUtils& m_logger;

public:
    /**
     * Constructor for the app controller.
     */
    AppController(MainInterface* view);

    /**
     * Routes all signals to proper functions in controllers.
     */
    void route();
};