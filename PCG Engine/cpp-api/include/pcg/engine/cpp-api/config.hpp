#ifndef PCG_ENGINE_CPP_API_CONFIG_HPP
#define PCG_ENGINE_CPP_API_CONFIG_HPP

#ifdef PCG_ENGINE_CPP_API_EXPORT
#define PCG_ENGINE_CPP_API_API __declspec(dllexport)
#else
#define PCG_ENGINE_CPP_API_API __declspec(dllimport)
#endif

#endif // PCG_ENGINE_CPP_API_CONFIG_HPP
