#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")  // Link Winsock library

int main() {
    WSADATA wsa;
    SOCKET server_sock, client_sock;
    struct sockaddr_in server, client;
    int c, recv_size;
    char client_message[2000];

    // Step 1: Initialize Winsock
    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed! Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Winsock initialized!\n");

    // Step 2: Create Socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == INVALID_SOCKET) {
        printf("Socket creation failed! Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Socket created successfully!\n");

    // Step 3: Bind Socket
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed! Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Bind successful!\n");

    // Step 4: Listen for Connections
    listen(server_sock, 3);
    printf("Waiting for incoming connections...\n");

    // Step 5: Accept Incoming Connection
    c = sizeof(struct sockaddr_in);
    client_sock = accept(server_sock, (struct sockaddr *)&client, &c);
    if (client_sock == INVALID_SOCKET) {
        printf("Accept failed! Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Connection accepted!\n");

    // Step 6: Receive and Send Messages
    while ((recv_size = recv(client_sock, client_message, 2000, 0)) > 0) {
        send(client_sock, client_message, strlen(client_message), 0);
    }

    if (recv_size == 0) {
        printf("Client disconnected.\n");
    } else {
        printf("recv failed! Error Code: %d\n", WSAGetLastError());
    }

    // Step 7: Cleanup
    closesocket(client_sock);
    closesocket(server_sock);
    WSACleanup();
    
    return 0;
}
