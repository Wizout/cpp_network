#ifndef NET_TCP_SERVER_H_
#define NET_TCP_SERVER_H_


#pragma once
#include "../net/tcp.h"
#include "../util/log.h"
#include "../util/signal.h"


class TCPv4_Server: public TCPv4
{
public:
  /*
   * 若listen_addr指针为空，则使用通配地址INADDR_ANY
   */
  explicit TCPv4_Server(const char* listen_addr, uint16_t listen_port = PORT_SERVER);
  virtual ~TCPv4_Server();

public:
  /*
   * 函数对象
   * 回声服务：客户端读取字符串并向服务端发送，服务端返回其收到的字符串
   * 若读取到的字符串为bye，或读至EOF，则关闭连接
   */
  struct Service_Echo
  {
    void operator ()(int socket_)
    {
      char* buf = new char[RECV_BUF_SIZE];
      memset(buf, 0, RECV_BUF_SIZE);

      while(0 < recv(socket_, buf, RECV_BUF_SIZE - 1, 0))
      {
        LOG(LOG_INFO, "receive from client(%lu bytes): %.31s", strnlen(buf, RECV_BUF_SIZE), buf);
        LOG(LOG_INFO, "send to client(%lu bytes): %s", strnlen(buf, RECV_BUF_SIZE), buf);
        send(socket_, buf, (1 + strnlen(buf, RECV_BUF_SIZE)) % RECV_BUF_SIZE, 0); //避免超过R_B_SIZE
        memset(buf, 0, RECV_BUF_SIZE);
      }
      LOG(LOG_INFO, "close socket");
      close(socket_);

      delete[] buf;
    }
  };

public:
  /*
   * 从完成三次握手的TCP连接队列中取出套接字并提供服务
   * 拉起子进程，使用service提供服务；service须为函数对象
   * 返回值：成功返回true，否则返回false
   */
  template<typename T>
  void accept_request(T& service);

  /*
   * 将监听地址、端口号绑定至套接字
   */
  virtual bool bind_addr();

  /*
   * 监听TCP连接请求
   * 返回值：成功返回true，否则返回false
   */
  bool listen_request(uint16_t listen_queue_len = LISTEN_QUEUE_LEN);

private:
  Signal*               _signal;      //信号处理
  int                   _sock_listen; //监听套接字
};



/*
 * 模板方法 实现
 */

template<typename T>
void TCPv4_Server::accept_request(T& service)
{
  pid_t       pid_child(0);
  socklen_t   sa4_len(sizeof(TCPv4::sa4));
  const char* p_ntop(nullptr);
  char* buf_ntop = new char[INET_ADDRSTRLEN]; 

  while(true)
  {
    _sock_peer = accept(_sock_listen, (TCPv4::sa*)&_addr_peer, &sa4_len);
    if(-1 == _sock_peer)
    {
      /*
       * 若阻塞在accept()时发生中断，accept()返回EINTR错误
       * 不需要处理EINTR错误
       */
      if(errno != EINTR)
      {
        LOG(LOG_ERROR, "accept() returns -1. errinfo: ");
        perror("\terrinfo");
        return;
      }
      continue;
    }

    memset(buf_ntop, 0, INET_ADDRSTRLEN);
    p_ntop = inet_ntop(AF_INET, &_addr_peer.sin_addr, buf_ntop, INET_ADDRSTRLEN);
    LOG(LOG_INFO, "accept request from %s:%u...", 
        (nullptr ==  p_ntop) ? "(error)" : p_ntop,
        ntohs(_addr_local.sin_port));

    pid_child = fork();
    if(0 == pid_child)    //子进程
    {
      close(_sock_listen);
      service(_sock_peer);
      exit(0);
    }

    close(_sock_peer);
  }

  delete[] buf_ntop;
}



#endif


