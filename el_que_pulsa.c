//funcion principal terminada
//hacer que lo que se escriba en la consola se escriba tambien en el sistema
//gcc el_que_pulsa.c -o el_que_pulsa.exe -lWs2_32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include <conio.h>
#include <windows.h>

int main(int argc, char* argv[]) {
    if(argc < 1){
        printf("ERROR: to many arguments");
        return -1;
    }
    char dir_ip[16];
    strcpy(dir_ip,argv[1]);
    // inciar el Windows Socket
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("Error en WSAStartup: %d\n", result);
        return 1;
    }
    printf("Usando la direccion IP: %s",argv[1]);

    //definir la direccion del servidor a conectar y sus caracteristicas
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Puerto (en formato de red)
    server_addr.sin_addr.s_addr = inet_addr(dir_ip); // Dirección IP (localhost)

    //crear socket del cliente
    int client_sock = socket(AF_INET,SOCK_STREAM, 0);

    //connectar el socket del cliente con el del servidor
    connect(client_sock, (struct sockaddr*)&server_addr,sizeof(server_addr));

    char input;
    char *puntero_input=&input;
    while(input != 'a'){
        printf("\nPresiona una tecla para simular su pulsacion en el sistema: ");
        input = getch();
        printf("\nHas presionado: %c\n", input);

        //enviar tecla o frase al servidor ej:Hola Mundo
        send(client_sock, puntero_input, strlen(puntero_input), 0);

        //si el servidor envia algo recibirlo y guardarlo en la variable buffer definida anteriormente
        //recv(client_sock,buffer,1024-1,0);

        printf("%s\n",puntero_input);
    }

    //cerrar los sockets y el Windows Socket
    closesocket(client_sock);
    WSACleanup();

    return 0;
}


