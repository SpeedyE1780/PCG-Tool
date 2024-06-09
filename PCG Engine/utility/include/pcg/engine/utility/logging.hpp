#ifndef PCG_ENGINE_UTILITY_LOGGING_HPP
#define PCG_ENGINE_UTILITY_LOGGING_HPP

#include <string>

namespace pcg::engine::utility
{
    typedef void (*logMessage)(const char* message);

    void setLoggingFunction(logMessage logFunction);
    void logInfo(const std::string& message);
    void logWarning(const std::string& message);
    void logError(const std::string& message);
}

#endif // PCG_ENGINE_UTILITY_LOGGING_HPP
