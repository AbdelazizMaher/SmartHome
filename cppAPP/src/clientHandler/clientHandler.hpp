#pragma once

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h> 

namespace sh {

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

enum class SocketState : uint8_t
{
    CLOSE_SERVER_SOCKET,
    CLOSE_CLIENT_SOCKET,
    CLOSE_ALL
};

class clientHandler
{
public:
    clientHandler() = default;
    ~clientHandler();

    Status initConnection();
    std::pair<Status, std::string> requestHandle();
private:
    int m_port;
    int m_serverSocket;
    int m_clientSocket;
    struct sockaddr_in m_serverAddress {};
    struct sockaddr_in m_clientAddress {};

    Status createSocket();
    void closeConnection(SocketState socket);
    Status acceptClient();
    std::string receiveMessage(Status& status);
    Status sendMessage(const std::string& message);    
};

}