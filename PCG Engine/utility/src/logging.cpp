#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::utility
{
    namespace
    {
        /// @brief Logs message functor functor
        /// @param logger Logger functor used to log message
        /// @param message Messaget that will be logged
        void log(const CallbackFunctor<void(const char*)>& logger, const std::string& message)
        {
            if (logger)
            {
                logger(message.c_str());
            }
        }
    }

    CallbackFunctor<void(const char*)>&& logger = [](const char*) {};

    void setLoggingFunction(CallbackFunctor<void(const char*)>&& logFunction)
    {
        logger = std::move(logFunction);
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

