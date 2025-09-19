#pragma once

#include <iostream>
#include <string>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include "AppConstants.hpp"
#include "version.h"
#define LOG_MSG_LENGTH 256
using namespace std;

// Singleton
class Logger {
private:
    QFile m_logfile;

    /**
     * Default constructor for Logger
     */
    Logger();

    /**
     * Constructor for Logger
     */
    Logger(QString filepath);

    /**
     * @brief Prints initial welcome message.
     */
    void initMessage();
    
public:
    /**
     * Returns the instance of logger
     */
    static Logger& getInstance();

    /**
     * @brief Logs activity to the CLI and log file.
     */
    void debugLog(string info, string origin, string type);

    Logger(const Logger&) = delete;
    
    Logger& operator=(const Logger&) = delete;
};
