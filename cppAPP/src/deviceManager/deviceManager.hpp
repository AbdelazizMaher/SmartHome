#pragma once

#include "Idevice.hpp"
#include <memory>
#include <vector>

namespace sh {

class deviceManager
{
public:
    deviceManager() = default;
    ~deviceManager() = default;

  void add_device(std::shared_ptr<Idevice> device);
  bool manage(std::vector<devices> status_dev);

private:
  std::vector<std::shared_ptr<Idevice>> m_devices; 
};    

}

