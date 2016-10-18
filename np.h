#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

int np_inet_pton4(const char *strptr, void *addrptr)
{
    return  inet_pton(AF_INET, strptr, addrptr);
}

int np_inet_pton6(const char *strptr, void *addrptr)
{
    return inet_pton(AF_INET6, strptr, addrptr);
}

int np_socket4(int type, int protocol)
{
    return socket(AF_INET, type, protocol);
}

int np_socket6(int type, int protocol)
{
    return socket(AF_INET6, type, protocol);
}

int np_connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
    int err = connect(sockfd, servaddr, addrlen);
    if(ETIMEDOUT == err ){
        err_sys("connect time out");
    }
    if(ECONNREFUSED == err){
        err_sys("may be server not running");
    }
    if(EHOSTUNREACH == err || ENETUNREACH == err ){
        err_sys("destination not reach");
    }
        
    return err;
}
