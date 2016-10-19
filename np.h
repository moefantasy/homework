#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>

int np_inet_pton4(const char *strptr, void *addrptr)
{
    int err =  inet_pton(AF_INET, strptr, addrptr);
    if(err == -1)
        printf("np_inet_pton4, %d",  err);
    return err;
}

int np_inet_pton6(const char *strptr, void *addrptr)
{
    int err =  inet_pton(AF_INET6, strptr, addrptr);

    printf("np_inet_pton6, %d",  err);
    return err;
}

int np_socket4(int type, int protocol)
{
    int err =  socket(AF_INET, type, protocol);
    if(err == -1 )
    {
        printf("socket %d", err);
    }
    
    return err;
}

int np_socket6(int type, int protocol)
{
    return socket(AF_INET6, type, protocol);
}

int np_connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
    int err = connect(sockfd, servaddr, addrlen);
    if(err == 0)
        return err;
    
    if(ETIMEDOUT == errno ){
        err_sys("connect time out");
    }
    if(ECONNREFUSED == errno){
        err_sys("may be server not running");
    }
    if(EHOSTUNREACH == errno || ENETUNREACH == errno ){
        err_sys("destination not reach");
    }
        
    return err;
}

int np_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int err = bind(sockfd, addr, addrlen);
    if(err == -1)
        err_quit("bind failed");
    return err;
    
}

ssize_t np_recvfrom(int sockfd, void *buf, size_t len, int flags, 
        struct sockaddr *src_addr, socklen_t *addrlen)
{
    int err =  recvfrom(sockfd, buf, len, flags, src_addr, addrlen);
    if(err == -1)
        printf("np_recvfrom %d", err);
    return err;
}

ssize_t np_sendto(int sockfd, const void *buf, size_t len, int flags,
        const struct sockaddr *dest_addr, socklen_t addrlen)
{
    int err =  sendto(sockfd, buf, len, flags, dest_addr, addrlen);
    if(err == -1)
        printf("np_sendto %d", err);
    return err;
}

char* np_fgets(char *s, int size, FILE *stream)
{
    return fgets(s, size, stream);
}

int np_fputs(const char* s, FILE *stream)
{
    return fputs(s, stream);
}
