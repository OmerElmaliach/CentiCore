#pragma once

#include <iostream>
#include <string>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include "version.h"
#define LOG_MSG_LENGTH 256
using namespace std;

// Singleton
class DebugUtils {
private:
    QFile m_logfile;

    /**
     * Default constructor for DebugUtils
     */
    DebugUtils();

    /**
     * Constructor for DebugUtils
     */
    DebugUtils(QString filepath);
    
public:
    const char* logFolder = "logs/";
    
    /**
     * Returns the instance of debug log
     */
    static DebugUtils& getInstance();

    /**
     * @brief Logs activity to the CLI and log file.
     */
    void debugLog(string info, string origin, string type);

    /**
     * @brief Prints initial welcome message.
     */
    void initMessage();

    DebugUtils(const DebugUtils&) = delete;
    
    DebugUtils& operator=(const DebugUtils&) = delete;
};
