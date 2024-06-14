#ifndef PCG_ENGINE_C_API_CONFIG_HPP
#define PCG_ENGINE_C_API_CONFIG_HPP

#ifdef PCG_ENGINE_C_API_EXPORT
#define PCG_ENGINE_C_API_API extern "C" __declspec(dllexport)
#else
#define PCG_ENGINE_C_API_API extern"C" __declspec(dllimport)
#endif

#endif // PCG_ENGINE_C_API_CONFIG_HPP
