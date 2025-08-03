#pragma once

#include "../../view/components/include/MainInterface.hpp"

class AppController {
private:
    MainInterface* m_view;

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