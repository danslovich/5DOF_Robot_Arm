/*******************************************************************************
*
**
**  Provided by DynamixelShield library examples
**
**
*******************************************************************************/
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

#define MAX_BAUD  5
const int32_t buad[MAX_BAUD] = {57600, 115200, 1000000, 2000000, 3000000};

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

//This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  // put your setup code here, to run once:
  int8_t index = 0;
  int8_t found_dynamixel = 0;

  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);   //set debugging port baudrate to 115200bps
  while(!DEBUG_SERIAL);         //Wait until the serial port is opened
    
  for(int8_t protocol = 1; protocol < 3; protocol++) {
    // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
    dxl.setPortProtocolVersion((float)protocol);
    DEBUG_SERIAL.print("SCAN PROTOCOL ");
    DEBUG_SERIAL.println(protocol);
    
    for(index = 0; index < MAX_BAUD; index++) {
      // Set Port baudrate.
      DEBUG_SERIAL.print("SCAN BAUDRATE ");
      DEBUG_SERIAL.println(buad[index]);
      dxl.begin(buad[index]);
      for(int id = 0; id < DXL_BROADCAST_ID; id++) {
        //iterate until all ID in each buadrate is scanned.
        if(dxl.ping(id)) {
          DEBUG_SERIAL.print("ID : ");
          DEBUG_SERIAL.print(id);
          DEBUG_SERIAL.print(", Model Number: ");
          DEBUG_SERIAL.println(dxl.getModelNumber(id));
          found_dynamixel++;
        }
      }
    }
  }
  
  DEBUG_SERIAL.print("Total ");
  DEBUG_SERIAL.print(found_dynamixel);
  DEBUG_SERIAL.println(" DYNAMIXEL(s) found!");
}

void loop() {
  // put your main code here, to run repeatedly:
}
