#ifndef EC_UTIL_LOG_H_
#define EC_UTIL_LOG_H_

/*
  日志组件
*/

#pragma once
#include <iostream>


#define LOG_INFO	"INFO"
#define LOG_DEBUG	"DEBUG"
#define LOG_ERROR	"ERROR"

#define PRINT_LOG


#ifdef PRINT_LOG 
#define LOG(level, format, ...) \
do {\
        fprintf(stderr, "[%s|%s:%d] " format "\n", \
            level, __func__, __LINE__, ##__VA_ARGS__); \
} while (false)
#else
#define LOG(level, format, ...) \
do \
{ \
 \
} while (false) 
#endif


#endif // !EC_UTIL_LOG_H_H


