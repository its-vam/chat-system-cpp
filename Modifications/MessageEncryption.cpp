#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

using namespace std;

SSL_CTX* InitCTX(void) {
    SSL_library_init();
    SSL_load_error_strings();
    SSL_METHOD* method = SSLv23_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    if (ctx == nullptr) {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

int main() {
    SSL_CTX* ctx = InitCTX();
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // client setup code

    struct sockaddr_in serverAddress;
    // set serverAddress

    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, clientSocket);

    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        close(clientSocket);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    while (true) {
        string message;
        cout << "Client: ";
        getline(cin, message);

        // Encrypt the message
        char encryptedMessage[1024];
        int encryptedLength = SSL_write(ssl, message.c_str(), message.length());

        // Receive and decrypt the response
        char decryptedResponse[1024];
        int bytesRead = SSL_read(ssl, decryptedResponse, sizeof(decryptedResponse));

        cout << "Server: " << decryptedResponse << endl;
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(clientSocket);

    return 0;
}
