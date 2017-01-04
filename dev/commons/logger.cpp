#include "logger.h"

#include "exceptions/ioexception.h"

#include <ctime>
#include <chrono>

logger* logger::_logger = NULL;

logger::logger(std::ostream &log_stream):
    _log(log_stream)
{
}

void logger::log_timestamp()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration tp = now.time_since_epoch();
    tp -= std::chrono::duration_cast<typename std::chrono::seconds>(tp);

    std::time_t tt = std::chrono::system_clock::to_time_t(now);
    std::tm *t = localtime(&tt);
    this->_log << t->tm_year + 1900 << "-"
               << t->tm_mon + 1 << "-"
               << t->tm_mday << "T"
               << t->tm_hour << "."
               << t->tm_min << "."
               << t->tm_sec <<"."
               << static_cast<unsigned>(tp / std::chrono::milliseconds(1)) << "\t";
}

void logger::log(const char *message) throw(IOException)
{
    if(_logger == NULL)
        throw IOException("Log not opened", __FILE__, __LINE__);
    _logger->log_timestamp();
    _logger->_log << message << std::endl;
}

void logger::log(const char *message, int line, const char *file) throw(IOException)
{
    if(_logger == NULL)
        throw IOException("Log not opened", __FILE__, __LINE__);
    _logger->log_timestamp();
    _logger->_log << "At line '" << line << "' in file '" << "'\t " << message << std::endl;
}

void logger::init_logger(std::ostream &output)
{
    _logger = new logger(output);
}

void logger::close_logger()
{
    delete _logger;
    _logger = NULL;
}

