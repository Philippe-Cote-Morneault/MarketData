#ifndef MARKET_DATA_API_HPP_
#define MARKET_DATA_API_HPP_

#if defined(LIBRARY_HEADER_ONLY)
#define LIBRARY_API_TYPE inline
#elif defined(LIBRARY_EXPORT)
#define LIBRARY_API_TYPE __declspec(dllexport)
#elif defined(LIBRARY_IMPORT)
#define LIBRARY_API_TYPE __declspec(dllimport)
#else
#define LIBRARY_API_TYPE
#endif

#endif