#include "airConditioner.hpp"
#include <iostream>

namespace sh {

airConditioner::airConditioner()
{
  possible_names.assign({"ac","airconditioner"});
}

bool airConditioner::run(devices status_dev)
{
    std::cout << "Device: " << status_dev.name << " Status: " << status_dev.status << std::endl;

    if (last_status != status_dev.status)
    {
        last_status = status_dev.status;

        //TODO
        std::cout << " Dummy airconditioner " << std::endl;
    }
    return true;
}

} // namespace sh
