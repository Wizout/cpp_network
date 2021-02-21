#include "../net/tcp.h"
#include "../util/log.h"


TCPv4::TCPv4()
{
  _sock_peer = 0;
  memset(&_addr_local, 0, sizeof(struct sockaddr_in));
  memset(&_addr_peer, 0, sizeof(struct sockaddr_in));
}

TCPv4::~TCPv4()
{
  ;
}

void TCPv4::init_addr(TCPv4::sa4& addr, const char* addr_ipv4, uint16_t port)
{
  addr.sin_family = AF_INET;
  
  if(0 != port)
    addr.sin_port = htons(port);
  
  if(nullptr != addr_ipv4)
  {
    int ret_val = inet_pton(AF_INET, addr_ipv4, &addr.sin_addr);
    if(1 != ret_val)
      LOG(LOG_ERROR, "inet_pton() returns %d (expect 1)", ret_val);
  }
}


