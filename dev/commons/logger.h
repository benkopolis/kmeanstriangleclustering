#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

#include "exceptions/ioexception.h"

#define log_error(x) logger::log(x, __LINE__, __FILE__)

class logger
{
protected:
    logger(std::ostream& log_stream);
    logger(const logger&) = delete;
    logger(logger&&) = delete;
    ~logger();

    static logger* _logger;
    static bool _enabled;

    std::ostream& _log;

    void log_timestamp(std::ofstream &out);
    void log_timestamp();

public:

    static void log(const char* message) throw(IOException);
    static void log(const char* message, int line, const char* file) throw(IOException);
    static void log(const char* message, std::ofstream& out) throw(IOException);
    static void log(const char* message, int line, const char* file, std::ofstream& out) throw(IOException);

    static void init_logger(std::ostream& output);
    static void disable_logger();
    static void close_logger();
};

#endif // LOGGER_H
