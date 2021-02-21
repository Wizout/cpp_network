#ifndef NET_NET_COMMON_H_
#define NET_NET_COMMON_H_


#pragma once
#include	<arpa/inet.h>	      /* inet(3) functions */
#include	<netinet/in.h>	    /* sockaddr_in{} and other Internet defns */
#include	<sys/socket.h>	    /* basic socket definitions */
#include	<sys/stat.h>	      /* for S_xxx file mode constants */
#include	<sys/time.h>	      /* timeval{} for select() */
#include	<sys/types.h>	      /* basic system data types */
#include	<sys/uio.h>		      /* for iovec{} and readv/writev */
#include	<sys/un.h>		      /* for Unix domain sockets */
#include	<sys/wait.h>
#include	<errno.h>
#include	<fcntl.h>		        /* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<unistd.h>
#include  <cstdint>
#include	<cstdio>
#include	<cstdlib>           /* perror(), etc...  */
#include	<cstring>
#include	<ctime>		          /* timespec{} for pselect() */


//缓冲区大小
constexpr uint16_t  RECV_BUF_SIZE    = 32;
constexpr uint16_t  COMMON_BUF_SIZE  = 128;    //待废弃

//端口号
constexpr uint16_t  PORT_CLIENT      = 38324;
constexpr uint16_t  PORT_SERVER      = 14122;

//IPv4地址
constexpr const char* ADDR_SERVER = "192.168.3.102";

//服务端listen()队列长度
constexpr uint16_t  LISTEN_QUEUE_LEN = 128;

#endif


