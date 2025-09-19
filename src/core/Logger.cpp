#include "Logger.hpp"

Logger::Logger() : Logger("cc_" + QDateTime::currentDateTime().toString("dd-MM-yyyy_hh-mm-ss") + ".log") {}

Logger::Logger(QString filepath) {
    // Creates directory if doesnt exist.
    QDir dir(AppConstants::Utils::LOG_PATH);
    if (!dir.exists())
        dir.mkpath(".");

    m_logfile.setFileName(AppConstants::Utils::LOG_PATH + filepath);
    if (!m_logfile.open(QIODevice::WriteOnly | QIODevice::Text))
        qWarning("Failed to open log file.");

    initMessage();
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::debugLog(string info, string origin, string type) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "[%s][CENTICORE-%s][%s] %s", QDateTime().currentDateTime().toString("hh:mm:ss").toLocal8Bit().constData(),
        origin.c_str(), type.c_str(), info.c_str());

    // Write to log
    m_logfile.write(buff);
    m_logfile.write("\n");
    m_logfile.flush();
}

void Logger::initMessage() {
    // Log starting message
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "=            Version %s | Build %s              =", CENTICORE_VERSION,
         QDateTime::currentDateTime().toString("dd-MM-yyyy").toLocal8Bit().constData());

    m_logfile.write("============================================================\n");
    m_logfile.write("=           CentiCore Personal Finance Tracker             =\n");
    m_logfile.write("=               Initialization Started...                  =\n");
    m_logfile.write(buff);
    m_logfile.write("\n");
    m_logfile.write("============================================================\n");
    m_logfile.flush();
}