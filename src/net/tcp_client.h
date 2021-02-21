#ifndef NET_NET_TCP_CLIENT_H_
#define NET_NET_TCP_CLIENT_H_


/*
 * TCP客户端
 */

#pragma once
#include "../net/tcp.h"


class TCPv4_Client: public TCPv4
{
public:
  /*
   * 无需指定本地地址&端口
   */
  explicit TCPv4_Client(const char* peer_addr, uint16_t peer_port);

  /*
   * 指定本地地址和/或端口，通过此地址/端口通信
   */
  explicit TCPv4_Client(const char* peer_addr, uint16_t peer_port, 
                        const char* local_addr, uint16_t local_port);

  virtual ~TCPv4_Client();

public:
  /*
   * 回声服务：客户端读取字符串并向服务端发送，服务端返回其收到的字符串
   * 若读取到的字符串为bye，或读至EOF，则关闭连接
   */
  void echo();

public:
  /*
   * 绑定本地地址（可选）
   * 若不绑定，则由系统选择路由中的本地地址、随机选择本地端口号
   * 返回值：成功返回true，否则返回false
   */
  bool bind_addr();

  /*
   * 连接服务器. 服务器地址、端口由_addr_peer指定
   * 返回值：成功返回true，否则返回false
   */
  bool connect_server();

  /*
   * 关闭套接字
   */
  void close_socket();

private:
  bool is_connected;    //当前是否已经连接
};


#endif


