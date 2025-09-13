#pragma once

#include <QObject>
#include <QWidget>
#include <QFile>
#include <QLocale>

class GeneralUtils {

private:
    /**
     * @brief Constructor for GeneralUtils
     */
    GeneralUtils();

public:
    /**
     * Returns an instance of GeneralUtils
     */
    static GeneralUtils* getInstance();

    /**
     * @brief Formats a given number with comma separators
     */
    QString formatNumberWithCommas(const double num, int afterDot);

    /**
     * @brief Loads the qss into the ui file
     */
    bool loadStyles(QWidget* widget, const QString stylePath);

    GeneralUtils(const GeneralUtils&) = delete;
    
    GeneralUtils& operator=(const GeneralUtils&) = delete;
};