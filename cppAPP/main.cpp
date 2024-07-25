#include "src/serviceManager/serviceManager.hpp"

int main()
{
    sh::serviceManager serviceManager{};

    bool continueRunning = true;
    while (continueRunning)
        continueRunning = serviceManager.processRequest();

    return 0;
}