# C Server and Client with Sockets

This repository contains a simple C program that demonstrates basic server and client communication using sockets. The program is designed to create a server that listens for incoming connections and a client that connects to the server. It's a foundation for building networked applications.

## Table of Contents

- [Introduction](#introduction)
- [How to Use](#how-to-use)
- [Program Structure](#program-structure)
- [Features](#features)
- [Author](#author)
- [License](#license)

## Introduction

This C program showcases the fundamentals of socket programming. The server listens for client connections, while the client connects to the server. It's a minimalistic example and can be extended for more complex networking tasks.

## How to Use

### Server

1. Compile the server source code by running the appropriate compiler command (e.g., `gcc server.c -o server`).
2. Run the server program, providing the desired server address and port as command-line arguments.
3. The server will start listening for incoming client connections.

### Client

1. Compile the client source code using a similar compilation command (e.g., `gcc client.c -o client`).
2. Execute the client program, specifying the server address and port as command-line arguments.
3. The client will connect to the server.

The program showcases basic client-server interaction. You can further build upon it to implement custom communication protocols.

## Program Structure

- `server.c`: Contains the server logic, including socket creation, binding, and listening for incoming connections.
- `client.c`: Implements the client logic, including socket creation and connecting to the server.
- `sockets.h`: Header file for socket-related functions.

## Features

This is a basic implementation that serves as a starting point for more advanced networking applications. It demonstrates the following features:

- Server setup to listen for incoming connections.
- Client setup to connect to the server.

You can enhance the program by implementing custom protocols, data exchange, and error handling as needed.

## Author

- [Brivia Allan]
- GitHub: [briviamoon](https://github.com/briviamoon/)

## License

This program is open-source and available under the [MIT License](LICENSE). You are free to use, modify, and distribute it according to the terms of the license.
