//
// Created by Vatsalya Yadav on 8/17/24.
//

#ifndef CORE_H
#define CORE_H

using U_CHAR = unsigned char;
using U_INT = unsigned int;
using U_INT32 = uint32_t;
using U_INT16 = uint16_t;

#ifdef ASSERT_CHECK
#ifdef GCC_COMPILER
    #define ASSERT(condition, message, ...) \
        do { \
            if (!(condition)) \
            { \
                std::string formattedMessage = std::format("Condition \"{0}\" failed: ", #condition); \
                formattedMessage += std::format(message, ##__VA_ARGS__); \
                std::cerr << formattedMessage << '\n'; \
                std::terminate(); \
            } \
        } while(0)
#elif MSVC_COMPILER
    #define ASSERT(condition, message, ...) \
    do { \
        if (!(condition)) \
        { \
            std::string formattedMessage = std::format("Condition \"{0}\" failed: ", #condition); \
            formattedMessage += std::format(message, __VA_ARGS__); \
            std::cerr << formattedMessage << '\n'; \
            __debugbreak(); \
        } \
    } while(0)
    #endif
#else
    #define ASSERT(condition, message, ...) do { } while(0)
#endif

#endif //CORE_H
