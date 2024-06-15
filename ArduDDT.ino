// #include <fmt.h>

#include "include/eufs_can.hpp"

eufs::can::CAN can_interface;

const uint8_t rear_motor_pin_1 = 2;
const uint8_t rear_motor_pin_2 = 3;
const uint8_t steering_pin_1 = 4;
const uint8_t steering_pin_2 = 5;

const uint8_t enable_motor_pin = 9;
const uint8_t enable_steering_pin = 10;

void setup()
{
    // Initialize the Serial port
    Serial.begin(115200);

    // Construct and initialize the CAN Bus
    can_interface.InitializeCanBus(100, true);

    pinMode(rear_motor_pin_1, OUTPUT);
    pinMode(rear_motor_pin_2, OUTPUT);
    pinMode(steering_pin_1, OUTPUT);
    pinMode(steering_pin_2, OUTPUT);
    pinMode(enable_motor_pin, OUTPUT);
    pinMode(enable_steering_pin, OUTPUT);

}

int count = 160;

void loop() {

    uint8_t len = 0;
    uint8_t buf[8];

    // Get torque commands from the car 0x511 AI2VCU_DRIVE_F
    // Get steering commands from the car 0x513 AI2VCU_STEER

    // Set the brightness of the LEDD

    digitalWrite(steering_pin_1, LOW);
    digitalWrite(steering_pin_2, HIGH);
    digitalWrite(rear_motor_pin_1, LOW);
    digitalWrite(rear_motor_pin_2, HIGH);

    while (count <= 255){
        analogWrite(enable_motor_pin, count);   
        Serial.print("Forward with duty cycle: ");
        Serial.println(count);
        count = count + 20;
        delay(500);
    }

    count = 160;

    if (CAN_MSGAVAIL == can_interface.checkReceive()) {         // check if data coming
        can_interface.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
        unsigned long can_id = can_interface.getCanId();

        if (can_id == 0x511) { 
            
        }

    delay(10);

    }

}
