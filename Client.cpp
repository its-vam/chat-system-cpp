#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <vector>

using namespace std;

class ClientHandler {
public:
  ClientHandler(int clientSocket) : clientSocket_(clientSocket) {}

  void Handle() {
    while (true) {
      char buffer[1024];
      memset(buffer, 0, sizeof(buffer);

      int bytesRead = recv(clientSocket_, buffer, sizeof(buffer), 0);

      if (bytesRead <= 0) {
        cerr << "Connection closed by server." << endl;
        break;
      }

      cout << "Server: " << buffer << endl;

      string message;
      cout << "Client: ";
      getline(cin, message);

      if (message.empty()) {
        continue;
      }

      send(clientSocket_, message.c_str(), message.length(), 0);
    }
  }

private:
  int clientSocket_;
};

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

  vector<thread> threads;

  threads.push_back(thread(&ClientHandler::Handle, new ClientHandler(clientSocket)));

  threads.push_back(thread([](int clientSocket) {
    while (true) {
      string message;
      cout << "Client: ";
      getline(cin, message);

      if (message.empty()) {
        continue;
      }

      send(clientSocket, message.c_str(), message.length(), 0);
    }
  }, clientSocket));

  for (auto& thread : threads) {
    thread.join();
  }

  close(clientSocket);

  return 0;
}
