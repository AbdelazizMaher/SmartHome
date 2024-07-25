#include "airConditioner.hpp"
#include <iostream>

namespace sh {

airConditioner::airConditioner()
{
  possible_names.assign({"ac","airconditioner"});
}

bool airConditioner::run(devices status_dev)
{
    std::cout << "airconditioner is running now " << status_dev.name << " status " << status_dev.status << std::endl;

    if (last_status != status_dev.status)
    {
        last_status = status_dev.status;

        
    }
}

} // namespace sh
