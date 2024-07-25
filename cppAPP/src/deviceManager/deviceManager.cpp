#include "deviceManager.hpp"

namespace sh {

void deviceManager::add_device(std::shared_ptr<Idevice> device)
{
    m_devices.push_back(device);
}

bool deviceManager::manage(std::vector<devices> status_dev)
{
    for (const auto &sd : status_dev)
    { 
        for (const auto &device : m_devices)
        {
            if (device->contains(sd.name))
                device->run(sd);
        }
    }
    return true;
}

} // namespace sh