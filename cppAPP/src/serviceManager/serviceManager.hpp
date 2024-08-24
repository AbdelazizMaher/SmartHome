#pragma once

#include "../clientHandler/clientHandler.hpp"
#include "../parser/parser.hpp"
#include "../deviceManager/deviceManager.hpp"

namespace sh {

class serviceManager {

public:
  /** constructor */
  serviceManager();
  /** Default destructor */
  ~serviceManager() = default;

  /** Method to process incoming requests */
  bool processRequest();

private:
  /** Client handler to manage connections and requests */
  clientHandler m_clientHandler;
  /** Parser to parse JSON responses into device structures */
  parser m_parser;
  /** Device manager to handle device operations */
  deviceManager m_deviceManager;
};

} // namespace sh