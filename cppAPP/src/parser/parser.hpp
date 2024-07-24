#pragma once

#include "deviceManager/Idevice.hpp"
#include "nlohmann/json.hpp"
#include <vector>
#include <iostream>

namespace sh {

class parser
{
public:
     /** Default constructor */   
    parser() = default;
    /** Default destructor */ 
    ~parser() = default; 

    /** Method to parse JSON string into vector of devices struct */
    std::vector<devices> parse(const std::string &msg);

    /** Method to log the details of devices */
    void log(std::vector<devices> &dev);

private:
    /** Method to convert JSON object to devices struct */
    devices parse_device(const nlohmann::json &jsonData);
};

} // namespace sh