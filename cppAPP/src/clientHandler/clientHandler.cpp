#include "clientHandler.hpp"

namespace sh {

/** Default constructor implementation */
clientHandler::clientHandler() : m_port(222), m_serverSocket(-1), m_clientSocket(-1)
{
}

/** Destructor implementation */
clientHandler::~clientHandler()
{
    /** Close all connections on destruction */
    closeConnection(SocketState::CLOSE_ALL);
}

/** Create the server socket */
Status clientHandler::createSocket()
{
    /** Create a socket using IPv4 and TCP */
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    /** Check if socket creation failed */
    if (m_serverSocket == -1)
    {
        /** Print error message if socket creation failed */
        std::cerr << "Failed to create socket" << std::endl;
        return Status::SOCKET_CREATION_FAILED;
    }
    return Status::SUCCESS;
}

/** Close the specified connections */
void clientHandler::closeConnection(SocketState socket)
{
    /** Close the server socket if specified */
    if (socket == SocketState::CLOSE_SERVER_SOCKET || socket == SocketState::CLOSE_ALL)
    {
        if (m_serverSocket != -1)
        {
            close(m_serverSocket);
            m_serverSocket = -1;
        }
    }

    /** Close the client socket if specified */
    if (socket == SocketState::CLOSE_CLIENT_SOCKET || socket == SocketState::CLOSE_ALL)
    {
        if (m_clientSocket != -1)
        {
            close(m_clientSocket);
            m_clientSocket = -1;
        }
    }
}

/** Accept a client connection */
Status clientHandler::acceptClient()
{
    /** Length of client address structure */
    socklen_t clientAddrLength = sizeof(m_clientAddress);
    /** Accept the client connection */
    m_clientSocket = accept(m_serverSocket, (struct sockaddr *)&m_clientAddress, &clientAddrLength);
    /** Check if accepting client connection failed */
    if (m_clientSocket == -1)
    {
        std::cerr << "Failed to accept client connection" << std::endl;
        return Status::ACCEPT_FAILED;
    }
    return Status::SUCCESS;
}

/** Receive a message from the client */
std::string clientHandler::receiveMessage(Status &status)
{
    /** Check if there is no client connected */
    if (m_clientSocket == -1)
    {
        std::cerr << "No client connected" << std::endl;
        status = Status::NOT_CONNECTED;
        return "";
    }

    /** Buffer to store received message */
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    /** Receive the message from the client */
    ssize_t bytesRead = recv(m_clientSocket, buffer, sizeof(buffer) - 1, 0);
    /** Check if receiving message failed */
    if (bytesRead == -1)
    {
        std::cerr << "Failed to receive data." << std::endl;
        closeConnection(SocketState::CLOSE_CLIENT_SOCKET);
        status = Status::RECEIVE_FAILED;
        return "";
    }
    status = Status::SUCCESS;

    /** Return the received message as a string */
    return std::string(buffer, bytesRead);
}

/** Send a message to the client */
Status clientHandler::sendMessage(const std::string &message)
{
    /** Check if there is no client connected */
    if (m_clientSocket == -1)
    {
        std::cerr << "No client connected" << std::endl;
        return Status::NOT_CONNECTED;
    }

    /** Send the message to the client */
    ssize_t bytesSent = send(m_clientSocket, message.c_str(), message.size(), 0);
    /** Check if sending message failed */
    if (bytesSent == -1)
    {
        std::cerr << "Failed to send message" << std::endl;
        return Status::SEND_FAILED;
    }

    return Status::SUCCESS;
}

/** Initialize the server socket connection */
Status clientHandler::initConnection()
{
    /** Create the server socket */
    Status status = createSocket();
    if (status != Status::SUCCESS)
        return status;

    /** Set up the server address structure */
    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_port = htons(m_port);
    m_serverAddress.sin_addr.s_addr = INADDR_ANY;
    /** Bind the socket to the specified port */
    if (bind(m_serverSocket, (struct sockaddr *)&m_serverAddress, sizeof(m_serverAddress)) == -1)
    {
        std::cerr << "Failed to bind to port" << std::endl;
        closeConnection(SocketState::CLOSE_ALL);
        return Status::BIND_FAILED;
    }

    /** Listen for incoming connections */
    if (listen(m_serverSocket, 5) == -1)
    {
        std::cerr << "Failed to listen on socket" << std::endl;
        closeConnection(SocketState::CLOSE_ALL);
        return Status::LISTEN_FAILED;
    }

    /** Print message indicating server is listening */
    std::cout << "Server listening on port " << m_port << "..." << std::endl;
    return Status::SUCCESS;
}

/** Handle a client request */
std::pair<Status, std::string> clientHandler::requestHandle()
{
    /** Accept a client connection */
    Status status = acceptClient();
    if (status != Status::SUCCESS)
        return {status, ""};

    /** Receive the client request */
    std::string request{receiveMessage(status)};
    std::cout << "Received GET request: " << request << std::endl;

    /** Check if the request is a GET request */
    if (request.substr(0, 3) == "GET")
    {
        /** Send a success response if it's a GET request */
        std::string response = "HTTP/1.1 200 OK\r\n"
                               "Content-Length: 7\r\n"
                               "\r\n"
                               "Success";
        status = sendMessage(response);
    }
    else
    {
        /** Send a bad request response if it's not a GET request */
        std::string response = "HTTP/1.1 400 Bad Request\r\n"
                               "Content-Length: 11\r\n"
                               "\r\n"
                               "Bad Request";
        status = sendMessage(response);
    }

    /** Find the position of the body in the request */
    auto bodyPosition = request.find("\r\n\r\n");
    /** Check if finding the body position failed */
    if (bodyPosition != std::string::npos)
    {
        std::cerr << "Failed to find body position." << std::endl;
        closeConnection(SocketState::CLOSE_CLIENT_SOCKET);
        return {Status::RECEIVE_FAILED, ""};
    }

    /** Print the body position */
    std::cout << bodyPosition << std::endl;
    /** Extract the body from the request */
    request = request.substr(bodyPosition + 4);
    /** Close the client socket */
    closeConnection(SocketState::CLOSE_CLIENT_SOCKET);

    return {status, request};
}

} // namespace sh
