#pragma omce

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
private:
    virtual ~Idevice() = default;
};

} // namespace sh