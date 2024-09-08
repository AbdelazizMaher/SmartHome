#include "serviceManager.hpp"

#include "../deviceManager/led.hpp"
#include "../deviceManager/airConditioner.hpp"

namespace sh {

/** Constructor to initialize the service manager */
serviceManager::serviceManager()
{
    m_clientHandler.initConnection();

    /** Add available devices */
    m_deviceManager.add_device(std::make_shared<led>());
    m_deviceManager.add_device(std::make_shared<airConditioner>());
}

/** Method to process incoming requests */
bool serviceManager::processRequest()
{
    /** Handle the request and obtain the status and response */
    auto [status, response] = m_clientHandler.requestHandle();
    /** Return false if the request handling failed */
    if(status != Status::SUCCESS)
        return false;

    /** Output the received message to the console */
    std::cout << "Devices before parsing: " << response << std::endl;  

    /** Parse the response to extract device information and log it */
    auto devices = m_parser.parse(response);
    m_parser.log(devices);

    /** Manage the parsed devices and return the result */
    if(!m_deviceManager.manage(devices))
        return false;

    return true;    
}

} // namespace sh