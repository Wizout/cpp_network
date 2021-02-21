#include "../util/log.h"
#include "../util/signal.h"
#include <sys/types.h>      //pid_t
#include <sys/wait.h>       //wait()


Signal::Signal()
{
  ;
}

Signal::~Signal()
{
  ;
}

bool Signal::set_sigchld_handler()
{
  return signal(SIGCHLD, handler_sigchld);
}

bool Signal::signal(int signo, Signal::sighandler_t func)
{
  struct sigaction act{};

  act.sa_flags    = 0;        //不设置标志位
  act.sa_handler  = func;     //信号处理函数
  sigemptyset(&act.sa_mask);  //不设置函数处理期间的阻塞信号

  int ret_val = 0;
  if((ret_val = sigaction(signo, &act, nullptr)) < 0)
  {
    LOG(LOG_ERROR, "sigaction() returns %d. error details: ", ret_val);
    perror(" ");
    return false;
  }

  return true;
}

void Signal::handler_sigchld(int signo)
{
  int   stat(0);
  //改用waitpid()避免多个子进程同时关闭时残留大量僵死进程
  while(waitpid(-1, &stat, WNOHANG) > 0);
//  wait(&stat);
}



