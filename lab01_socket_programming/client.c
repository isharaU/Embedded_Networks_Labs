#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")  // Link Winsock library

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];

    // Step 1: Initialize Winsock
    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed! Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Winsock initialized!\n");

    // Step 2: Create Socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed! Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Socket created successfully!\n");

    // Step 3: Define Server Address
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    // Step 4: Connect to Server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connect failed! Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Connected to server!\n");

    // Step 5: Send and Receive Messages
    while (1) {
        printf("Enter message: ");
        scanf("%s", message);

        if (send(sock, message, strlen(message), 0) < 0) {
            printf("Send failed!\n");
            return 1;
        }

        if (recv(sock, server_reply, 2000, 0) < 0) {
            printf("recv failed!\n");
            break;
        }

        printf("Server reply: %s\n", server_reply);
    }

    // Step 6: Cleanup
    closesocket(sock);
    WSACleanup();

    return 0;
}
