#pragma once

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace sh {

/** Enumeration for different status codes returned by HTTP operations */
enum class httpStatus : uint8_t
{
    SUCCESS,
    SOCKET_CREATION_FAILED,
    CONNECTION_FAILED,
    SEND_FAILED,
    RECEIVE_FAILED,
    INVALID_RESPONSE
};

/** Class to handle HTTP GET requests */
class httpGetHandle
{
public:
    /** Constructor to initialize with URL */
    httpGetHandle(std::string &url);
    /** Destructor to close connection */
    ~httpGetHandle();

    /** Method to send GET request and receive response */
    httpStatus sendGetRequest(std::string &response);

private:
    /** Member variable to store URL */
    std::string m_url{};

    /** Socket file descriptor */
    int m_clientSocket;
    /** Struct to hold server address information */
    struct sockaddr_in m_serverAddress;

    /** Method to create socket */
    httpStatus createSocket();
    /** Method to close the socket connection */
    void closeConnection();

    /** Method to extract the host from URL */
    std::string extractHost(const std::string &url);
    /** Method to extract the path from URL */
    std::string extractPath(const std::string &url);
    /** Method to build the GET request string */
    std::string buildGetRequest(const std::string &host, const std::string &path);

    /** Method to connect to the server */
    httpStatus connectToServer(const std::string &host);
    /** Method to send message over socket */
    httpStatus sendMessage(const std::string &message);
    /** Method to receive message from socket */
    httpStatus receiveMessage(std::string &response);

    /** Method to print response */
    void printResponse();
};

} // namespace sh