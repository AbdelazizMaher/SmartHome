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
    std::cout << "led is running now " << status_dev.name << " status " << status_dev.status << std::endl;

    if (last_status != status_dev.status)
    {
        last_status = status_dev.status;

        int fd = open("/dev/led", O_WRONLY);
        if (fd < 0)
            return false;

        if (status_dev.status)
        {
            int ret = write(fd, "1", 1);
            if (ret < 0)
            {
                return false;
            }
        }
        else
        {
            int ret = write(fd, "0", 1);
            if (ret < 0)
            {
                return false;
            }
        }

        close(fd);
    }
    return true;
}

} // namespace sh