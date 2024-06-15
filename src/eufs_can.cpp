#include "../include/eufs_can.hpp"

void eufs::can::CAN::InitializeCanBus(unsigned long timeout_ms, bool report_flag) {
 
  // Allow for baudrate to be changed from parameter file
  while (CAN_OK != this->begin(CAN_1000KBPS)) {
    Serial.println("CAN bus failed to initialize. Retrying...");
    delay(timeout_ms);
  }

  Serial.println("CAN Bus initialized!");

  if (report_flag) {
    this->ReportCanBusStatus();
  }

};

void eufs::can::CAN::ReportCanBusStatus() {
  // TODO (Khalid): Format report message here
  Serial.println("Include report here");
};
