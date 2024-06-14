#ifndef PCG_ENGINE_UTILITY_LOGGING_HPP
#define PCG_ENGINE_UTILITY_LOGGING_HPP

#include <pcg/engine/utility/CallbackFunctor.hpp>

#include <string>

namespace pcg::engine::utility
{
    void setLoggingFunction(CallbackFunctor<void(const char*)>&& logFunction);
    void logInfo(const std::string& message);
    void logWarning(const std::string& message);
    void logError(const std::string& message);
}

#endif // PCG_ENGINE_UTILITY_LOGGING_HPP
