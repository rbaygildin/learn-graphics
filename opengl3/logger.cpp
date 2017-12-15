//
// Created by Max Heartfield on 06.12.17.
//

#include "logger.h"

void Logger::info(string text) {
    BOOST_LOG_TRIVIAL(info) << text;
}

void Logger::error(string text) {
    BOOST_LOG_TRIVIAL(fatal) << text;
}
