#include "serviceManager.hpp"

namespace sh {

serviceManager::serviceManager()
{
    m_clientHandler.initConnection();
}

bool serviceManager::processRequest()
{
    auto [status, response] = m_clientHandler.requestHandle();
    if(status != Status::SUCCESS)
        return false;

    std::cout << "Received message: " << response << std::endl;  

    auto devices = m_parser.parse(response);

    if(!m_deviceManager.manage(devices))
        return false;

    return true;    
}

} // namespace sh