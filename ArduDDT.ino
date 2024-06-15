// #include <fmt.h>

#include "include/eufs_can.hpp"
#include "include/can_frame_id/ai2vcu_drive_f.hpp"
#include "include/can_frame_id/ai2vcu_steering.hpp"

eufs::can::CAN can_interface;
eufs::can::message::DriveCanMessage drive_can_msg(0x511);
eufs::can::message::SteeringCanMessage steering_can_msg(0x513);

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

    if (CAN_MSGAVAIL == can_interface.checkReceive()) {         // check if data coming
        can_interface.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
        unsigned long can_id = can_interface.getCanId();

        if (can_id == 0x511) { 
            drive_can_msg.ExtractDataFrame(buf); 
            drive_can_msg.ParseData();
            // Serial.println("I am inside 0x511");
        } else if (can_id == 0x513) {
            steering_can_msg.ExtractDataFrame(buf);
            steering_can_msg.ParseData();
            // Serial.println("I am inside 0x513");
        }

    }

    // Get torque commands from the car 0x511 AI2VCU_DRIVE_F
    // Get steering commands from the car 0x513 AI2VCU_STEER

    digitalWrite(steering_pin_1, LOW);
    digitalWrite(steering_pin_2, HIGH);
    analogWrite(enable_steering_pin, 255);


    digitalWrite(rear_motor_pin_1, LOW);
    digitalWrite(rear_motor_pin_2, HIGH);
    analogWrite(enable_motor_pin, drive_can_msg.CalculateNormalizedAxleTorque());
    
    // Turn right
    if (steering_can_msg.get_command_steering() < 0) {
        digitalWrite(steering_pin_1, LOW);
        digitalWrite(steering_pin_2, HIGH);
        Serial.println("Turning right");
    } else if (steering_can_msg.get_command_steering() > 0 ) {
        digitalWrite(steering_pin_1, HIGH);
        digitalWrite(steering_pin_2, LOW);
        Serial.println("Turning left");
    } else {
        digitalWrite(steering_pin_1, LOW);
        digitalWrite(steering_pin_2, LOW);
    }

    uint8_t steering_pwm_val = steering_can_msg.CalculateNormalizedSteering();
    analogWrite(enable_steering_pin, steering_pwm_val);
    // Serial.println(steering_can_msg.get_command_steering());
    Serial.println(steering_pwm_val);

    // Serial.println(drive_can_msg.CalculateNormalizedAxleTorque());

    // while (count <= 255){
    //     analogWrite(enable_motor_pin, count);   
    //     Serial.print("Forward with duty cycle: ");
    //     Serial.println(count);
    //     count = count + 20;
    //     delay(500);
    // }

    // count = 160;

}
