#include "../net/tcp_client.h"
#include "../util/io.h"
#include "../util/log.h"


TCPv4_Client::TCPv4_Client(const char* peer_addr, uint16_t peer_port):
  is_connected(false)
{
  init_addr(_addr_peer, peer_addr, peer_port);
  init_socket(_sock_peer);
}

TCPv4_Client::TCPv4_Client(const char* peer_addr, uint16_t peer_port, 
                           const char* local_addr, uint16_t local_port):
  is_connected(false)
{
  init_addr(_addr_peer, peer_addr, peer_port);
  init_addr(_addr_local, local_addr, local_port);
  init_socket(_sock_peer);
}

TCPv4_Client::~TCPv4_Client()
{
  close_socket();
}

void TCPv4_Client::echo()
{
  if(!is_connected)
  {
    LOG(LOG_ERROR, "please connect first. is_connected = %u\n", is_connected);
    return;
  }

  const char* str_end = "bye";
  char* buf = new char[RECV_BUF_SIZE];
  memset(buf, 0, RECV_BUF_SIZE);

  LOG(LOG_INFO, 
      "note: input something and then press Enter. Input \"bye\" or press [Ctrl + D] to exit. ");
  while(scanf("%[^\n]", buf) != EOF)    //允许读入空白字符
  {
    if(0 == strncmp(buf, str_end, strnlen(str_end, 8)))
    {
      LOG(LOG_INFO, "user input \"bye\" to exit");
      break;
    }
    clear_stdin_cache();
    LOG(LOG_INFO, "send to server(%lu bytes): %s", strnlen(buf, RECV_BUF_SIZE), buf);
    send(_sock_peer, buf, (1 + strnlen(buf, RECV_BUF_SIZE)) % RECV_BUF_SIZE , 0);
    memset(buf, 0, RECV_BUF_SIZE);

    recv(_sock_peer, buf, RECV_BUF_SIZE - 1, 0);
    LOG(LOG_INFO, "receive from server(%lu bytes): %.31s", strnlen(buf, RECV_BUF_SIZE), buf);
    memset(buf, 0, RECV_BUF_SIZE);
  }

  close_socket();
  delete[] buf;
}

bool TCPv4_Client::bind_addr()
{
  int ret_val(0);
  ret_val = bind(_sock_peer, (TCPv4::sa*)&_addr_local, sizeof(TCPv4::sa4));
  if(0 != ret_val)
  {
    LOG(LOG_ERROR, "bind() returns %d, errno = %d. exit...", ret_val, errno);
    perror("\terrinfo");
    return false;
  } 
  return true;
}

bool TCPv4_Client::connect_server()
{
  if(is_connected)
  {
    LOG(LOG_ERROR, "connection has been established. Please close connection.");
    return false;
  }
  
  char* buf_ntop = new char[INET_ADDRSTRLEN];
  memset(buf_ntop, 0, INET_ADDRSTRLEN);
  LOG(LOG_INFO, "connect to server %s:%u...", 
      (nullptr == inet_ntop(AF_INET, &_addr_peer.sin_addr, buf_ntop, INET_ADDRSTRLEN) 
      ? "(error)" : buf_ntop), ntohs(_addr_peer.sin_port));

  int ret_val(0);
  ret_val = connect(_sock_peer, (TCPv4::sa*)&_addr_peer, sizeof(TCPv4::sa4));
  if(0 != ret_val)
  {
    LOG(LOG_ERROR, "connect() returns %d, errno = %d. exit...", ret_val, errno);
    perror("\terrinfo");
    return false;
  }
  is_connected = true;
  return true;
}

void TCPv4_Client::close_socket()
{
  if(is_connected)
  {
    LOG(LOG_INFO, "close socket");
    close(_sock_peer);
    is_connected = false;
  }
}


