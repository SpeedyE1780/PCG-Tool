#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::utility
{
    namespace
    {
        void log(logMessage logger, const std::string& message)
        {
            if (logger)
            {
                logger(message);
            }
        }
    }

    logMessage logger = nullptr;

    void setLoggingFunction(logMessage logFunction)
    {
        logger = logFunction;
    }

    void logInfo(const std::string& message)
    {
        log(logger, "[INFO] " + message);
    }

    void logWarning(const std::string& message)
    {
        log(logger, "[WARNING] " + message);
    }

    void logError(const std::string& message)
    {
        log(logger, "[ERROR] " + message);
    }
}

