#pragma once

#include "Idevice.hpp"
#include <vector>

namespace sh {

class led : public Idevice 
{
public:
  led();
  ~led() = default;

  bool run(devices status_dev) override;
};

} // namespace sh