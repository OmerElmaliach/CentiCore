#pragma once
#include <QFile>
#include <QTextStream>
#include <QProcessEnvironment>
#include <QDebug>
#include "AppConstants.hpp"
#include "Logger.hpp"

/**
 * @class EnvLoader
 * @brief Utility namespace for loading environment variables from a configuration file.
 *
 * The EnvLoader class provides functionality to retrieve configuration values
 * from a `.env` style file stored as a Qt resource.
 * The file is expected to contain key-value pairs.
 */
namespace EnvLoader {
    /**
     * @brief Retrieves the value associated with a given key from the configuration file.
     *
     * The function searches through the .env file
     * for a matching key and returns its corresponding value. If the value is enclosed
     * in double quotes, they will be removed before returning.  
     * If the key is not found, an empty string is returned and a warning is logged.
     *
     * @param key The configuration key to search for.
     * @return The value associated with the given key, or an empty string if not found.
     */
    QString getValue(const QString& key);
}