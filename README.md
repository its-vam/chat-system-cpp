# Chat System Application
# Socket-based Client-Server Chat System

This is a client-server chat system implemented using C++ sockets. The server and clients can exchange messages in a text-based chat format.

## Features

- **Multi-Client Support:** Multiple clients can connect to the server simultaneously, enabling real-time group chat.

- **Real-time Communication:** Messages are delivered in real-time between the server and clients, ensuring fast and responsive communication.

- **Error Handling:** The system incorporates input validation and comprehensive error handling to enhance reliability.

## Prerequisites

Before getting started with this chat system, ensure you have the following prerequisites in place:

- **C++ Compiler:** You need a C++ compiler, such as g++, to build and run the server and client programs.

- **UNIX-like Operating System:** The code is designed to work on UNIX-like operating systems, including Linux and macOS.

## Getting Started

Follow these steps to set up and run the Socket-based Client-Server Chat System:

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/its-vam/socket-chat-system.git
   cd socket-chat-system
   
2. **Compile the Server and Client Code:**

   Compile the server and client programs using the following commands:

   ```bash
   g++ -o server server.cpp -lpthread
   g++ -o client client.cpp

3. **Run the Server:**

   Start the server by running the following command:

   ```bash

   ./server

4. **Run the Clients:**

   Open one or more client terminals and run the client program:

    ```bash

   ./client

5. **Start Chatting:**   

   You can now start chatting between clients and the server. Messages will be displayed in the respective terminals in real-time. 

# Usage

- The server listens on port 12345 by default, but you can modify the port in the code if needed.

- Clients connect to the server using the client program and can send and receive messages in real-time.

- Messages from the server and clients are displayed in the respective terminals.

- To close the server or client, simply use Ctrl+C.

