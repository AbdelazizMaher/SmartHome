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
        if (last_status == 1)
          std::cout << " ==== AirConditioner: ON ====" << std::endl;
        else
          std::cout << " ==== AirConditioner: OFF ====" << std::endl;
    }
    return true;
}

} // namespace sh
