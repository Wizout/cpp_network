#ifndef NET_SRC_UTIL_IO_H_
#define NET_SRC_UTIL_IO_H_


#pragma once
#include <cstdio>
#include <cstring>


/*
 * 清除stdin的输入缓存
 * 建议在每次调用scanf()之后使用
 */
void clear_stdin_cache();




/*
 * 内联函数实现
 */

inline void clear_stdin_cache()
{
  char c = '\0';

  while((c = getchar()) != '\n' && c != EOF);
}

#endif


