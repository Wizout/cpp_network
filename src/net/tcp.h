#ifndef NET_NET_TCP_H_
#define NET_NET_TCP_H_


#pragma once
#include "../net/common.h"


/*
 * TCP IPv4抽象基类
 */
class TCPv4
{
public:
  explicit TCPv4();
  virtual ~TCPv4();

public:
  typedef struct sockaddr    sa;
  typedef struct sockaddr_in sa4;

public:
  /*
   * 绑定本地地址
   * 客户端：绑定至套接字_sock_peer；服务端：绑定至套接字_sock_local.
   */
  virtual bool bind_addr() = 0;

  /*
   * 初始化sockaddr_in结构
   * 若addr_ipv4为空指针、port为0，则仅填写sin_family为AF_INET
   */
  void init_addr(TCPv4::sa4& addr, const char* addr_ipv4 = nullptr, uint16_t port = 0);

  /*
   * 初始化套接字
   */
  inline void init_socket(int& socket_, int protocol = IPPROTO_TCP);

protected:
  sa4   _addr_local;    //本地地址
  sa4   _addr_peer;     //对端地址
  int   _sock_peer;     //连接至对端的套接字
};


/*
 * 内联函数实现
 */

void TCPv4::init_socket(int& socket_, int protocol)
{
  socket_ = socket(AF_INET, SOCK_STREAM, protocol);
}



#endif


