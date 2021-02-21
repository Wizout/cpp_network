#include "../net/tcp_server.h"


TCPv4_Server::TCPv4_Server(const char* listen_addr, uint16_t listen_port)
{
  memset(&_addr_local, 0, sizeof(TCPv4::sa4));
  init_addr(_addr_local, listen_addr, listen_port);
  init_socket(_sock_listen);

  _signal = new Signal;
  if(false == _signal->set_sigchld_handler())
  {
    LOG(LOG_ERROR, "set_sigchld_handler() returns nullptr...exit");
    exit(-1);
  }
}

TCPv4_Server::~TCPv4_Server()
{
  close(_sock_listen);
  delete _signal;
}


bool TCPv4_Server::bind_addr()
{
  int ret_val(0);

  ret_val = bind(_sock_listen, (TCPv4::sa*)&_addr_local, sizeof(TCPv4::sa4));
  if(0 != ret_val)
  {
    LOG(LOG_ERROR, "bind() returns %d. errno = %d. exit...", ret_val, errno);
    perror("\terrinfo");
    return false;
  }
  return true;
}

bool TCPv4_Server::listen_request(uint16_t listen_queue_len)
{
  int ret_val = listen(_sock_listen, listen_queue_len);
  if(ret_val != 0)
  {
    LOG(LOG_ERROR, "listen() returns %d. errno = %d. exit...", ret_val, errno);
    perror("\terrinfo");
    return false;
  }

  const char* p_ntop(nullptr);
  char* buf_ntop = new char[INET_ADDRSTRLEN]; 
  p_ntop = inet_ntop(AF_INET, &_addr_local.sin_addr, buf_ntop, INET_ADDRSTRLEN);
  LOG(LOG_INFO, "listen connect requests on %s:%u...", 
      (nullptr ==  p_ntop) ? "(error)" : p_ntop,
      ntohs(_addr_local.sin_port));
  delete[] buf_ntop;
  return true;
}

