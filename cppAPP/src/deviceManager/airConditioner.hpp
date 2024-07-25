#pragma once

#include "Idevice.hpp"
#include "clientHandler/httpGetHandle.hpp"

namespace sh {
class airConditioner : public Idevice {

public:
  airConditioner();
  ~airConditioner() = default;

  bool run(devices status_dev) override;

};
} // namespace sh