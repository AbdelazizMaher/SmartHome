#include "src/serviceManager/serviceManager.hpp"

int main()
{
    /** Create an instance of the service manager */
    sh::serviceManager serviceManager{};

    /** Flag to control the main loop */
    bool continueRunning = true;

    /** Main loop to continuously process incoming requests */
    while (continueRunning)
        continueRunning = serviceManager.processRequest();

    /** Exit the program */
    return 0;
}