// Клиентская реализация модели клиент-сервер UDP
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

  
#define PORT     8080
#define MAXLINE 1024

  
// Код драйвера

int main() {

    int sockfd;

    char buf[MAXLINE];

    char *hello = "Hello from client";

    struct sockaddr_in     servaddr;

  

    // Создание дескриптора файла сокета
    /* int socket(int domain, int type, int protocol)
    Домен — определяет связь
    домен (AF_INET для IPv4 / AF_INET6 для IPv6)
    тип — тип сокета, который будет создан
    (SOCK_STREAM для TCP / SOCK_DGRAM для UDP)
    протокол — протокол, который будет использоваться сокетом.
    0 означает использовать протокол по умолчанию для семейства адресов.*/


    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {

        perror("socket creation failed");

        exit(EXIT_FAILURE);

    }

  

    memset(&servaddr, 0, sizeof(servaddr));

      

    // Заполнение информации о сервере

    servaddr.sin_family = AF_INET;

    servaddr.sin_port = htons(PORT);

    servaddr.sin_addr.s_addr = INADDR_ANY;

      

    int n;
    socklen_t len;

    /* ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen)
    sockfd — файловый дескриптор сокета
    buf — буфер приложения, содержащий данные для отправки
    len — Размер буфера приложения buf
    flags — Побитовое ИЛИ флагов для изменения поведения сокета
    dest_addr — структура, содержащая адрес назначения
    addrlen — размер структуры dest_addr */  

    sendto(sockfd, (const char *)hello, strlen(hello),

        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 

            sizeof(servaddr));

    printf("Hello message sent.\n");

    /* ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen)
    sockfd — файловый дескриптор сокета
    buf — буфер приложения, в который нужно получать данные
    len — Размер буфера приложения buf
    flags — Побитовое ИЛИ флагов для изменения поведения сокета
    src_addr — возвращается структура, содержащая адрес источника
    addrlen — переменная, в которой возвращается размер структуры src_addr */      

    n = recvfrom(sockfd, (char *)buf, MAXLINE, 

                MSG_WAITALL, (struct sockaddr *) &servaddr,

                &len);

    buf[n] = '\0';

    printf("Server : %s\n", buf);

    /* int close(int fd)
    fd — дескриптор файла */
    close(sockfd);

    return 0;

}
