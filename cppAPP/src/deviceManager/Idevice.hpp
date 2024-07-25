#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

namespace sh {

struct devices
{
    std::string     _id;
    uint32_t        identifier;
    std::string     name;
    bool            status;
    uint32_t         __v;
};

class Idevice
{
public:
    virtual ~Idevice() = default;

    virtual bool run(devices status) = 0;

    bool contains(std::string name) 
    {
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        return std::find(possible_names.begin(), possible_names.end(), name) != possible_names.end();
    }
protected:
    std::vector<std::string> possible_names;
    bool last_status = false;    
};

} // namespace sh