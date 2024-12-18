//funcion principal terminada
//hacer que lo que se escriba en la consola se escriba tambien en el sistema
//gcc servidor.c -o servidor -lWs2_32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include <conio.h>
#include <windows.h>

char buffer[1]={0};

int main() {
    //iniciar Windows Socket
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("Error en WSAStartup: %d\n", result);
        return 1;
    }
    //definir estructura del servidor y crear la estructura del cliente
    struct sockaddr_in server_addr,client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Puerto (en formato de red)
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP (localhost)

    //crear el socket del servidor
    int server_sock = socket(AF_INET,SOCK_STREAM, 0);

    //vincular el socket con la estructura definida y escuchar las solicitudes enviadas por los clientes
    bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    listen(server_sock,10);

    //acceptar las solicitudes de los clientes y recibir lo que ellos mandan
    int client_len = sizeof(client_addr);
    int new_socket = accept(server_sock,(struct sockaddr*)&client_addr,&client_len);
    while(buffer[0] != 'a'){
        recv(new_socket,buffer,1024-1,0); //recibe lo que manda el cliente
        printf("%s",buffer);
        char input = buffer[0]; //guarda la tecla pulsada en el buffer
        
        // Configura la estructura INPUT para que esto se ejecute en nuestro PC
        INPUT inputEvent = {0};
        inputEvent.type = INPUT_KEYBOARD;
        inputEvent.ki.wVk = VkKeyScan(input); // Convierte el carácter a un código de tecla virtual

        // Simula la pulsación de la tecla en nuestro PC
        SendInput(1, &inputEvent, sizeof(INPUT));
    
        // Simula la liberación de la tecla
        inputEvent.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &inputEvent, sizeof(INPUT));

        printf("Se simulo la pulsacion de la tecla '%c'.\n", input);
    }
    //cerrar los sockets y el Windows Socket
    closesocket(new_socket);
    closesocket(server_sock);
    WSACleanup();

    return 0;
}


