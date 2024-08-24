#ifndef PCG_ENGINE_UTILITY_LOGGING_HPP
#define PCG_ENGINE_UTILITY_LOGGING_HPP

#include <functional>
#include <string>

namespace pcg::engine::utility
{
    /// @brief Set function used to log info from the engine
    /// @param logFunction Function that will log engine messages
    void setLoggingFunction(std::function<void(const char*)>&& logFunction);
    /// @brief Log info from engine
    /// @param message Info message
    void logInfo(const std::string& message);
    /// @brief Log warning from engine
    /// @param message Warning message
    void logWarning(const std::string& message);
    /// @brief Log error from engine
    /// @param message Error message
    void logError(const std::string& message);
}

#endif // PCG_ENGINE_UTILITY_LOGGING_HPP
