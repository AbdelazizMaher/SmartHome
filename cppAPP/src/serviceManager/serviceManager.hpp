#pragma once

#include "../clientHandler/clientHandler.hpp"
#include "../parser/parser.hpp"
#include "../deviceManager/deviceManager.hpp"

namespace sh {

class serviceManager {

public:
  serviceManager();
  ~serviceManager() = default;

  bool processRequest();

private:
  clientHandler m_clientHandler;
  parser m_parser;
  deviceManager m_deviceManager;
};

} // namespace sh