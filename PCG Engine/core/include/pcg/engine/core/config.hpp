#ifndef PCG_ENGINE_CORE_CONFIG_HPP
#define PCG_ENGINE_CORE_CONFIG_HPP

#ifdef PCG_ENGINE_CORE_EXPORT
#define PCG_ENGINE_CORE_API __declspec(dllexport)
#else
#define PCG_ENGINE_CORE_API _declspec(dllimport)
#endif

#endif // PCG_ENGINE_CORE_CONFIG_HPP
