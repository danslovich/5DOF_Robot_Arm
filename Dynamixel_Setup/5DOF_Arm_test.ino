/*******************************************************************************
*
**  Name: Daniel Slovich
**  Date: 5/7/21
**  Info: Application to setup and test 5DOF robot arm
**        with daisy chained Dynamixel XL-330 micro servos.
**        
**  Note: To assign individual servo id's, connect servos       
**        one at a time and run "scan_dynamixel.ino"
**        and gather default id from serial monitor. 
**        Then run "id.ino" and assigned the desired ID. 
**        Do this for each motor separately before assembly.
*        
*******************************************************************************/

/* NOTE: Please check if your DYNAMIXEL supports Profile Control
* Supported Products : MX-28(2.0), MX-64(2.0), MX-106(2.0), All X series(except XL-320)
* PRO(A) series / PRO+ series
* Designed and tested using the XL-330
*/

#include <DynamixelShield.h>

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
  #define DEBUG_SERIAL SerialUSB    
#else
  #define DEBUG_SERIAL Serial
#endif

//DXL ID's set prior using "scan_dynamixel" and "id"
const uint8_t DXL_1 = 1;
const uint8_t DXL_2 = 2;
const uint8_t DXL_3 = 3;
const uint8_t DXL_4 = 4;
const uint8_t DXL_5 = 5;
const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

//This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  DEBUG_SERIAL.begin(115200);
  // Set baud rate for DXLs
  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Check if active
  dxl.ping(DXL_1);
  dxl.ping(DXL_2);
  dxl.ping(DXL_3);
  dxl.ping(DXL_4);
  dxl.ping(DXL_5);

  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(DXL_1);
  dxl.torqueOff(DXL_2);
  dxl.torqueOff(DXL_3);
  dxl.torqueOff(DXL_4);
  dxl.torqueOff(DXL_5);
  dxl.setOperatingMode(DXL_1, OP_POSITION);
  dxl.setOperatingMode(DXL_2, OP_POSITION);
  dxl.setOperatingMode(DXL_3, OP_POSITION);
  dxl.setOperatingMode(DXL_4, OP_POSITION);
  dxl.setOperatingMode(DXL_5, OP_POSITION);
  dxl.torqueOn(DXL_1);
  dxl.torqueOn(DXL_2);
  dxl.torqueOn(DXL_3);
  dxl.torqueOn(DXL_4);
  dxl.torqueOn(DXL_5);

  // Set DXLs acceleration and velocity
  dxl.writeControlTableItem(PROFILE_ACCELERATION, DXL_1, 50);//shoulder 4:1 planetary ratio
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_1,130);
  dxl.writeControlTableItem(PROFILE_ACCELERATION, DXL_2, 50);//shoulder 4:1 planetary ratio
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_2,130);
  dxl.writeControlTableItem(PROFILE_ACCELERATION, DXL_3, 50);//elbow 1:1
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_3, 50);
  dxl.writeControlTableItem(PROFILE_ACCELERATION, DXL_4, 50);//wrist 1:1
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_4, 130);
  dxl.writeControlTableItem(PROFILE_ACCELERATION, DXL_5, 200);//eef 1:1
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_5, 200);

  // Set Home position in angle(degree)
  // These positions correspond to all joints aligned vertically
  // run program to set servo home angles before connecting hardware links/joints
  // Take consideration when assembling to preserve these positions!
  dxl.setGoalPosition(DXL_5, 180.0, UNIT_DEGREE); //shoulder - rotational
  dxl.setGoalPosition(DXL_4, 180.0, UNIT_DEGREE); //shoulder - angular
  dxl.setGoalPosition(DXL_3, 270.0, UNIT_DEGREE); //elbow    - angular
  dxl.setGoalPosition(DXL_2, 180.0, UNIT_DEGREE); //wrist    - rotational
  dxl.setGoalPosition(DXL_1, 180.0, UNIT_DEGREE); //EEF      - angular
  delay(2500);
}

void loop() {
  // Wave hello
  dxl.setGoalPosition(DXL_2, 360.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_3, 200.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_5, 80.0, UNIT_DEGREE);
  delay(1500);
  dxl.setGoalPosition(DXL_5, 280.0, UNIT_DEGREE);
  delay(500);
  dxl.setGoalPosition(DXL_5, 80.0, UNIT_DEGREE);
  delay(500);
  dxl.setGoalPosition(DXL_5, 280.0, UNIT_DEGREE);
  delay(500);
  dxl.setGoalPosition(DXL_5, 80.0, UNIT_DEGREE);
  delay(500);
  dxl.setGoalPosition(DXL_2, 0.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_3, 340.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_5, 280.0, UNIT_DEGREE);
  delay(1500);
  dxl.setGoalPosition(DXL_5, 280.0, UNIT_DEGREE);
  delay(500);
  dxl.setGoalPosition(DXL_5, 80.0, UNIT_DEGREE);
  delay(500);
  dxl.setGoalPosition(DXL_5, 280.0, UNIT_DEGREE);
  delay(500);
  dxl.setGoalPosition(DXL_5, 80.0, UNIT_DEGREE);
  delay(500);

  // Return to home
  dxl.setGoalPosition(DXL_5, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_4, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_3, 270.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_2, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_1, 180.0, UNIT_DEGREE);
  delay(1500);

  // Test all joint movements
  dxl.setGoalPosition(DXL_1, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_2, 270.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_3, 250.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_4, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_5, 280.0, UNIT_DEGREE);
  delay(1000);
  dxl.setGoalPosition(DXL_1, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_2, 90.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_3, 290.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_4, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_5, 80.0, UNIT_DEGREE);
  delay(1000);
  dxl.setGoalPosition(DXL_1, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_2, 270.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_3, 250.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_4, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_5, 280.0, UNIT_DEGREE);
  delay(1000);
  dxl.setGoalPosition(DXL_1, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_2, 90.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_3, 290.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_4, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_5, 80.0, UNIT_DEGREE);
  delay(1000);
  dxl.setGoalPosition(DXL_1, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_2, 270.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_3, 250.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_4, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_5, 280.0, UNIT_DEGREE);
  delay(1000);
  dxl.setGoalPosition(DXL_1, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_2, 90.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_3, 290.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_4, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_5, 80.0, UNIT_DEGREE);
  delay(2500);
  dxl.setGoalPosition(DXL_1, 360.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_4, 360.0, UNIT_DEGREE);
  delay(2500);
  dxl.setGoalPosition(DXL_1, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_2, 270.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_3, 250.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_4, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_5, 280.0, UNIT_DEGREE);
  delay(2500);
  dxl.setGoalPosition(DXL_1, 0.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_4, 0.0, UNIT_DEGREE);
  delay(2500);
  dxl.setGoalPosition(DXL_5, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_4, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_3, 270.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_2, 180.0, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_1, 180.0, UNIT_DEGREE);
  //end
  delay(10000000);
  
}
