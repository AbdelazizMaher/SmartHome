#include "clientHandler.hpp"

namespace sh {

clientHandler::~clientHandler()
{

}

Status clientHandler::createSocket()
{
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if( m_serverSocket == -1 )
    {
        std::cerr << "Failed to create socket" << std::endl;
        return Status::SOCKET_CREATION_FAILED;
    }
    return Status::SUCCESS;
}

void clientHandler::closeConnection(SocketState socket) 
{
    if( socket == SocketState::CLOSE_SERVER_SOCKET ||  socket == SocketState::CLOSE_ALL )
    {
        if ( m_serverSocket != -1 ) 
        {
            close(m_serverSocket);
            m_serverSocket = -1;
        }
    }

    if( socket == SocketState::CLOSE_CLIENT_SOCKET ||  socket == SocketState::CLOSE_ALL )
    {
        if ( m_clientSocket != -1 ) 
        {
            close(m_clientSocket);
            m_clientSocket = -1;
        } 
    }
   
}

Status clientHandler::acceptClient()
{
    socklen_t clientAddrLength = sizeof(m_clientAddress);
    m_clientSocket = accept(m_serverSocket, (struct sockaddr*)&m_clientAddress, &clientAddrLength);
    if( m_clientSocket == -1 )
    {
        std::cerr << "Failed to accept client connection" << std::endl;
        return Status::ACCEPT_FAILED;
    }
    return Status::SUCCESS;
}

std::string clientHandler::receiveMessage(Status& status)
{
    if ( m_clientSocket == -1 ) 
    {
        std::cerr << "No client connected" << std::endl;
        status = Status::NOT_CONNECTED;
        return "";
    } 

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytesRead = recv(m_clientSocket, buffer, sizeof(buffer) - 1, 0);    
    if (bytesRead == -1) 
    {
        std::cerr << "Failed to receive data." << std::endl;
        closeConnection(SocketState::CLOSE_ALL);       
        status = Status::RECEIVE_FAILED;
        return "";
    }
    status = Status::SUCCESS;

    return std::string(buffer);    
}

Status clientHandler::sendMessage(const std::string& message)
{
    if ( m_clientSocket == -1 ) 
    {
        std::cerr << "No client connected" << std::endl;
        return Status::NOT_CONNECTED;
    }  

    ssize_t bytesSent = send(m_clientSocket, message.c_str(), message.size(), 0);
    if (bytesSent == -1) 
    {
        std::cerr << "Failed to send message" << std::endl;
        return Status::SEND_FAILED;
    }

    return Status::SUCCESS;
}

Status clientHandler::initConnection()
{
    Status status = createSocket();
    if ( status != Status::SUCCESS ) 
        return status;

    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_port = htons(m_port);
    m_serverAddress.sin_addr.s_addr = INADDR_ANY;
    if( bind(m_serverSocket, (struct sockaddr*)&m_serverAddress, sizeof(m_serverAddress)) == -1 )
    {
        std::cerr << "Failed to bind to port" << std::endl;
        closeConnection(SocketState::CLOSE_ALL);
        return Status::BIND_FAILED;
    }

    if( listen(m_serverSocket, 5) == -1 )
    {
        std::cerr << "Failed to listen on socket" << std::endl;
        closeConnection(SocketState::CLOSE_ALL);
        return Status::LISTEN_FAILED;
    }

    std::cout << "Server listening on port " << m_port << "..." << std::endl;
    return Status::SUCCESS;
}

std::pair<Status, std::string> clientHandler::requestHandle()
{
    Status status = acceptClient();
    if ( status != Status::SUCCESS ) 
        return {status,""};

    std::string request { receiveMessage(status) };
    std::cout << "Received GET request: " << request << std::endl;

    if ( request.substr(0, 3) == "GET" ) 
    {
        std::string response = "HTTP/1.1 200 OK\r\n"
                               "Content-Length: 7\r\n"
                               "\r\n"
                               "Success";
        sendMessage(response);
    }
     else 
     {
        std::string response = "HTTP/1.1 400 Bad Request\r\n"
                               "Content-Length: 11\r\n"
                               "\r\n"
                               "Bad Request";
        sendMessage(response);
    } 

    auto bodyPosition = request.find("\r\n\r\n");
     if( bodyPosition != std::string::npos )  
     {
        std::cerr << "Failed to find body position." << std::endl;
        closeConnection(SocketState::CLOSE_CLIENT_SOCKET);
        return {Status::RECEIVE_FAILED, ""};
     }     

     std::cout << bodyPosition << std::endl;
     request = request.substr(bodyPosition + 4);
     closeConnection(SocketState::CLOSE_CLIENT_SOCKET);
}

}