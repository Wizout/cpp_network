#ifndef NET_UTIL_SIGNAL_H_
#define NET_UTIL_SIGNAL_H_


/*
 * Unix信号处理
 */
#pragma once
#include <signal.h>




class Signal
{
public:
  explicit Signal();
  virtual ~Signal();

public:
  typedef void (*sighandler_t)(int);    //用于简化signal()函数原型

public:
  /*
   * 为SIGCHLD信号注册处理函数
   * 操作成功，返回true，否则返回false
   */
  bool set_sigchld_handler();

  /*
   * 为信号signo注册信号处理函数func
   * 若发生错误，则返回false，否则返回true
   */
  bool signal(int signo, Signal::sighandler_t func);

private:
  /*
   * SIGCHLD信号处理函数
   * 由父进程调用，负责wait()子进程
   */
  static void handler_sigchld(int signo);
};



#endif


