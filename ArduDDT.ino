#include "include/eufs_can.hpp"

void setup()
{
    // Initialize the Serial port
    Serial.begin(115200);

    // Construct and initialize the CAN Bus
    eufs::can::CAN can_interface;
    can_interface.InitializeCanBus(100, true);

}

void loop()
{
    Serial.println("Test");
}
