#include "led.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

namespace sh {

led::led()
{
    possible_names.assign({"led"});
}

bool led::run(devices status_dev)
{
    std::cout << "Device: " << status_dev.name << " Status: " << status_dev.status << std::endl;

    if (last_status != status_dev.status)
    {
        last_status = status_dev.status;

        int fd = 1/*open("/dev/led-home", O_WRONLY)*/;
        std::cout << " opening /dev/led-home " << std::endl;
        if (fd < 0)
            return false;

        if (status_dev.status)
        {
            int ret = 1 /*write(fd, "1", 1)*/;
            std::cout << " setting /dev/led-home " << std::endl;
            if (ret < 0)
            {
                return false;
            }
        }
        else
        {
            int ret = 1 /*write(fd, "0", 1)*/;
            std::cout << " reseting /dev/led-home " << std::endl;
            if (ret < 0)
            {
                return false;
            }
        }

        //close(fd);
    }
    return true;
}

} // namespace sh