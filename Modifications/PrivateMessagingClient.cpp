#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <string>

using namespace std;

void ReceiveMessages(int clientSocket) {
    while (true) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead <= 0) {
            cerr << "Connection closed by the server." << endl;
            close(clientSocket);
            exit(0);
        }

        cout << "Server: " << buffer << endl;
    }
}

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Connection failed");
        return 1;
    }

    thread receiverThread(ReceiveMessages, clientSocket);

    while (true) {
        string message;
        cout << "Client: ";
        getline(cin, message);

        if (message.empty()) {
            continue;
        }

        send(clientSocket, message.c_str(), message.length(), 0);
    }

    receiverThread.join();
    close(clientSocket);

    return 0;
}
