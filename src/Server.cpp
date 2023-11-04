#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Bind the socket to a port
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Binding failed");
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        perror("Listening failed");
        return 1;
    }

    std::cout << "Server is listening on port 12345..." << std::endl;

    // Accept connections from clients
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);

    if (clientSocket == -1) {
        perror("Accepting connection failed");
        return 1;
    }

    // Communication loop
    while (true) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer);

        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead <= 0) {
            std::cerr << "Connection closed by client." << std::endl;
            break;
        }

        std::cout << "Client: " << buffer << std::endl;

        std::string response;
        std::cout << "Server: ";
        std::getline(std::cin, response);
        send(clientSocket, response.c_str(), response.length(), 0);
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}
