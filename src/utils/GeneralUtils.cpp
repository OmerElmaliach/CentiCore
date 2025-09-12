#include "GeneralUtils.hpp"

GeneralUtils::GeneralUtils() {}

GeneralUtils* GeneralUtils::getInstance() {
    static GeneralUtils* instance = new GeneralUtils();
    return instance;
}

QString GeneralUtils::formatNumberWithCommas(double num, int afterDot) {
    QLocale locale(QLocale::English, QLocale::UnitedStates);
    return locale.toString(num, 'f', afterDot);
}