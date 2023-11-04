# Chat System Application
# Socket-based Client-Server Chat System

This is a simple client-server chat system implemented using C++ sockets. The server and clients can exchange messages in a text-based chat format.

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
Copy code
g++ -o server server.cpp -lpthread
g++ -o client client.cpp
   
