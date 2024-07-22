#pragma once

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace sh {

/** Enum representing the status of various operations */
enum class Status : uint8_t
{
    SUCCESS,
    SOCKET_CREATION_FAILED,
    BIND_FAILED,
    LISTEN_FAILED,
    ACCEPT_FAILED,
    SEND_FAILED,
    RECEIVE_FAILED,
    NOT_CONNECTED
};

/** Enum representing the state of the socket connections */
enum class SocketState : uint8_t
{
    CLOSE_SERVER_SOCKET,
    CLOSE_CLIENT_SOCKET,
    CLOSE_ALL
};

/** Class to handle client connections */
class clientHandler
{
public:
    /** Default constructor */
    clientHandler();
    /** Destructor */
    ~clientHandler();

    /** Delete copy constructor */
    clientHandler(const clientHandler&) = delete;
    /** Delete copy assignment operator */
    clientHandler& operator=(const clientHandler&) = delete;

    /** Delete move constructor */
    clientHandler(clientHandler&&) = delete;
    /** Delete move assignment operator */
    clientHandler& operator=(clientHandler&&) = delete;

    /** Initialize the server socket connection */
    Status initConnection();
    /** Handle a client request */
    std::pair<Status, std::string> requestHandle();
private:
    /** Port number for the server */
    int m_port;
    /** Server socket file descriptor */
    int m_serverSocket;
    /** Client socket file descriptor */
    int m_clientSocket;
    /** Server address structure */
    struct sockaddr_in m_serverAddress {};
    /** Client address structure */
    struct sockaddr_in m_clientAddress {};

    /** Create the server socket */
    Status createSocket();
    /** Close the server and/or client socket based on the parameter */
    void closeConnection(SocketState socket);
    /** Accept a client connection */
    Status acceptClient();
    /** Receive a message from the client */
    std::string receiveMessage(Status& status);
    /** Send a message to the client */
    Status sendMessage(const std::string& message);
};

} // namespace sh
