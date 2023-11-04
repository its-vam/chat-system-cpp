#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

class ClientHandler {
public:
    ClientHandler(int clientSocket, const string& username, map<string, int>& usernameToSocket)
        : clientSocket_(clientSocket), username_(username), usernameToSocket_(usernameToSocket) {}

    void Handle() {
        while (true) {
            char buffer[1024];
            memset(buffer, 0, sizeof(buffer);

            int bytesRead = recv(clientSocket_, buffer, sizeof(buffer), 0);

            if (bytesRead <= 0) {
                cerr << "Connection closed for user: " << username_ << endl;
                close(clientSocket_);
                usernameToSocket_.erase(username_);
                break;
            }

            string message = string(buffer);

            // Check if the message is a private message
            if (message.find("/pm ") == 0) {
                size_t pos = message.find(" ");
                if (pos != string::npos) {
                    string recipient = message.substr(4, pos - 4);
                    string privateMessage = message.substr(pos + 1);

                    if (usernameToSocket_.find(recipient) != usernameToSocket_.end()) {
                        int recipientSocket = usernameToSocket_[recipient];
                        send(recipientSocket, privateMessage.c_str(), privateMessage.length(), 0);
                    }
                }
            } else {
                // Broadcast the message to all clients (including private messages)
                for (const auto& pair : usernameToSocket_) {
                    int clientSocket = pair.second;
                    send(clientSocket, message.c_str(), message.length(), 0);
                }
            }
        }
    }

private:
    int clientSocket_;
    string username_;
    map<string, int>& usernameToSocket_;
};

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress) == -1)) {
        perror("Binding failed");
        return 1;
    }

    if (listen(serverSocket, 5) == -1) {
        perror("Listening failed");
        return 1;
    }

    cout << "Server is listening on port 12345..." << endl;

    map<string, int> usernameToSocket;
    vector<thread> threads;

    while (true) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);

        if (clientSocket == -1) {
            perror("Accepting connection failed");
            return 1;
        }

        // After accepting a client, get their username
        string username = "DefaultUser";  // You should implement a username retrieval mechanism

        // Create a new client handler thread
        ClientHandler clientHandler(clientSocket, username, usernameToSocket);
        usernameToSocket[username] = clientSocket;
        threads.push_back(thread(&ClientHandler::Handle, &clientHandler));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    close(serverSocket);

    return 0;
}
