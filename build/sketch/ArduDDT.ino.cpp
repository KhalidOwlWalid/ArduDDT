#include <Arduino.h>
#line 1 "/home/khalidowlwalid/eufs-master/src/simulation/ArduDDT/ArduDDT.ino"
#include "include/eufs_can.hpp"

#line 3 "/home/khalidowlwalid/eufs-master/src/simulation/ArduDDT/ArduDDT.ino"
void setup();
#line 25 "/home/khalidowlwalid/eufs-master/src/simulation/ArduDDT/ArduDDT.ino"
void loop();
#line 3 "/home/khalidowlwalid/eufs-master/src/simulation/ArduDDT/ArduDDT.ino"
void setup()
{
    // Initialize the Serial port
    Serial.begin(115200);

    // Construct and initialize the CAN Bus
    eufs::can::CAN can_interface;

    // // The initialization needs to be a blocking function to ensure that the
    // // CAN interface is set up correctly. Include a timeout?
    const int test = 1;
    if (can_interface.InitializeCanBus(test)) {
        Serial.println("CAN Bus successfully initialized!");
        
        // Report CAN Bus status should include all of the baudrate settings etc.
        can_interface.ReportCanBusStatus();
    } else {
        Serial.println("CAN Bus failed to initialize. Retrying...");
    };

}

void loop()
{
    Serial.println("Test");
}
