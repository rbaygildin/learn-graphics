/**
 * © Roman Yarnykh, 2017
 */

#ifndef OPENGL2_LOGGER_H
#define OPENGL2_LOGGER_H

#include "common.h"

/**
 * Logging
 */
class Logger {
public:
    static void info(string text);

    static void error(string text);
};


#endif //OPENGL2_LOGGER_H
