#include "httpGetHandle.hpp"

namespace sh {

/** Constructor: Initializes the URL and socket */
httpGetHandle::httpGetHandle(std::string &url) : m_url{url}, m_clientSocket{-1}
{
}

/** Destructor: Closes the socket connection */
httpGetHandle::~httpGetHandle()
{
    closeConnection();
}

/** Method to create a socket */
httpStatus httpGetHandle::createSocket()
{
    /** Create a socket with IPv4 and TCP protocols */
    m_clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    /** Check if socket creation was successful */
    if (m_clientSocket == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return httpStatus::SOCKET_CREATION_FAILED;
    }
    return httpStatus::SUCCESS;
}

/** Method to close the socket connection */
void httpGetHandle::closeConnection()
{
    /** Check if socket is valid and close it */
    if (m_clientSocket != -1)
    {
        close(m_clientSocket);
        m_clientSocket = -1;
    }
}

/** Method to extract the host part from the URL */
std::string httpGetHandle::extractHost(const std::string &url)
{
    /** Find the position of "://" in the URL */
    size_t hostStart = url.find("://");
    if (hostStart == std::string::npos)
        return "";

    /** Move past the "://" */
    hostStart += 3;

    /** Find the end of the host part */
    size_t hostEnd = url.find("/", hostStart);
    if (hostEnd == std::string::npos)
        return url.substr(hostStart);

    /** Return the host part */
    return url.substr(hostStart, hostEnd - hostStart);
}

/** Method to extract the path part from the URL */
std::string httpGetHandle::extractPath(const std::string &url)
{
    /** Find the position of "://" in the URL */
    size_t hostStart = url.find("://");
    if (hostStart == std::string::npos)
        return "/";

    /** Move past the "://" */
    hostStart += 3;

    /** Find the start of the path */
    size_t pathStart = url.find("/", hostStart);
    if (pathStart == std::string::npos)
        return "/";

    /** Return the path part */
    return url.substr(pathStart);
}

/** Method to build the GET request string */
std::string httpGetHandle::buildGetRequest(const std::string &host, const std::string &path)
{
    /** Create the GET request string with host and path */
    return "GET " + path + " HTTP/1.1\r\n"
           "Host: " + host + "\r\n"
           "Connection: close\r\n\r\n";
}

/** Method to connect to the server */
httpStatus httpGetHandle::connectToServer(const std::string &host)
{
    /** Get the server address using the host name */
    struct hostent *server = gethostbyname(host.c_str());
    if (server == nullptr)
    {
        std::cerr << "Error: No such host" << std::endl;
        return httpStatus::CONNECTION_FAILED;
    }

    /** Initialize server address struct */
    memset(&m_serverAddress, 0, sizeof(m_serverAddress));
    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_port = htons(80);
    memcpy(&m_serverAddress.sin_addr.s_addr, server->h_addr, server->h_length);

    /** Connect to the server */
    if (connect(m_clientSocket, (struct sockaddr *)&m_serverAddress, sizeof(m_serverAddress)) == -1)
    {
        std::cerr << "Error connecting to server" << std::endl;
        return httpStatus::CONNECTION_FAILED;
    }

    return httpStatus::SUCCESS;
}

/** Method to send a message over the socket */
httpStatus httpGetHandle::sendMessage(const std::string &message)
{
    /** Send the message */
    ssize_t bytesSent = send(m_clientSocket, message.c_str(), message.length(), 0);
    if (bytesSent == -1)
    {
        std::cerr << "Failed to send message" << std::endl;
        closeConnection();
        return httpStatus::SEND_FAILED;
    }
    return httpStatus::SUCCESS;
}

/** Method to receive a message from the socket */
httpStatus httpGetHandle::receiveMessage(std::string &response)
{
    /** Buffer to hold received data */
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    /** Read data from the socket */
    ssize_t bytesRead;
    while ((bytesRead = recv(m_clientSocket, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        response.append(buffer, bytesRead);
    }

    /** Check for errors during reading */
    if (bytesRead == -1)
    {
        std::cerr << "Failed to receive message" << std::endl;
        return httpStatus::RECEIVE_FAILED;
    }

    return httpStatus::SUCCESS;
}

/** Method to print the response */
void httpGetHandle::printResponse()
{
    /** Buffer to hold received data */
    char buffer[4096];
    std::memset(buffer, 0, sizeof(buffer));

    /** Read data from the socket and print */
    while (read(m_clientSocket, buffer, sizeof(buffer) - 1) > 0)
    {
        std::cout << buffer;
        std::memset(buffer, 0, sizeof(buffer));
    }
}

/** Method to send GET request and receive response */
httpStatus httpGetHandle::sendGetRequest(std::string &response)
{
    /** Create a socket */
    httpStatus status = createSocket();
    if (status != httpStatus::SUCCESS)
        return status;

    /** Extract host and path from URL */
    std::string host = extractHost(m_url);
    std::string path = extractPath(m_url);
    if (host.empty())
    {
        std::cerr << "Invalid URL" << std::endl;
        return httpStatus::INVALID_RESPONSE;
    }

    /** Connect to the server */
    status = connectToServer(host);
    if (status != httpStatus::SUCCESS)
        return status;

    /** Build and send the GET request */
    std::string request = buildGetRequest(host, path);
    status = sendMessage(request);
    if (status != httpStatus::SUCCESS)
        return status;

    /** Print the response */
    printResponse();

    /** Receive the response message */
    status = receiveMessage(response);
    closeConnection();

    return status;
}

} // namespace sh
