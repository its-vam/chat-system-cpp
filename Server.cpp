#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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
        cerr << "Connection closed by client." << endl;
        break;
      }

      cout << "Client: " << buffer << endl;

      string response;
      cout << "Server: ";
      getline(cin, response);
      send(clientSocket_, response.c_str(), response.length(), 0);
    }
  }

private:
  int clientSocket_;
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

  if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
    perror("Binding failed");
    return 1;
  }

  if (listen(serverSocket, 5) == -1) {
    perror("Listening failed");
    return 1;
  }

  cout << "Server is listening on port 12345..." << endl;

  vector<thread> threads;

  while (true) {
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);

    if (clientSocket == -1) {
      perror("Accepting connection failed");
      return 1;
    }

    ClientHandler clientHandler(clientSocket);
    threads.push_back(thread(&ClientHandler::Handle, &clientHandler));
  }

  for (auto& thread : threads) {
    thread.join();
  }

  close(serverSocket);

  return 0;
}
