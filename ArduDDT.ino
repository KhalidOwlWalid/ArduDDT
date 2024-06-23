// #include <fmt.h>

#include "include/eufs_can.hpp"
#include "include/can_frame_id/ai2vcu_drive_f.hpp"
#include "include/can_frame_id/ai2vcu_steering.hpp"
#include "include/motor_controller.hpp"

eufs::can::CAN can_interface;
eufs::can::message::DriveCanMessage drive_can_msg(0x511);
eufs::can::message::SteeringCanMessage steering_can_msg(0x513);

eufs::hardware::motor::DC drive_motor;
eufs::hardware::motor::DC steering_motor;

void setup()
{
    // Initialize the Serial port
    Serial.begin(115200);

    // Construct and initialize the CAN Bus
    can_interface.InitializeCanBus(100, true);

    // TODO: Return assertion, ensure that this is correctly initialized
    // If not, return error, and loop
    // Setup the motor with the necessary parameters
    drive_motor.InitializeMotor(2, 3, 9);
    steering_motor.InitializeMotor(4, 5, 10);
    Serial.println("Motor initialized!");

}

void loop() {

    uint8_t len = 0;
    uint8_t msg_buffer[8];

    if (CAN_MSGAVAIL == can_interface.checkReceive()) {         // check if data coming
        can_interface.readMsgBuf(&len, msg_buffer);    // read data,  len: data length, msg_buffer: data msg_buffer
        unsigned long can_id = can_interface.getCanId();

        // TODO: I think I can simply abstract this process here
        if (can_id == 0x511) { 
            drive_can_msg.ExtractDataFrame(msg_buffer); 
            drive_can_msg.ParseData();
        } else if (can_id == 0x513) {
            steering_can_msg.ExtractDataFrame(msg_buffer);
            steering_can_msg.ParseData();
        }

    }

    // Controls the rear motor
    uint8_t pwm_val = drive_can_msg.CalculateNormalizedAxleTorque();
    drive_motor.ControlMotorSpeed(pwm_val);
    drive_motor.ControlMotorDirection(LOW, HIGH);
    
    uint8_t steering_pwm_val = steering_can_msg.CalculateNormalizedSteering();
    if (steering_can_msg.get_command_steering() < -2) {
        steering_motor.ControlMotorSpeed(steering_pwm_val);
        steering_motor.ControlMotorDirection(LOW, HIGH);
        Serial.println("Turning right");
    } else if (steering_can_msg.get_command_steering() > 2 ) {
        steering_motor.ControlMotorSpeed(steering_pwm_val);
        steering_motor.ControlMotorDirection(HIGH, LOW);
        Serial.println("Turning left");
    } else {
        steering_motor.ControlMotorSpeed(steering_pwm_val);
        steering_motor.ControlMotorDirection(LOW, LOW);
        Serial.println("Wheels straight");
    }

}