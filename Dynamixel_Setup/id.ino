/*******************************************************************************
*
**
**  Provided by DynamixelShield library examples
**  Modified slightly to assign specific servo id's
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


const uint8_t DEFAULT_DXL_ID = 1;
const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

//This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  /***
  **
  ** Change Present ID to the id acquired when running "scan_dynamixel"
  ** 
  **/
  uint8_t present_id = /**/100/**/;
  uint8_t new_id = 0;
  
  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(57600);
  while(!DEBUG_SERIAL);
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(57600);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  DEBUG_SERIAL.print("PROTOCOL ");
  DEBUG_SERIAL.print(DXL_PROTOCOL_VERSION, 1);
  DEBUG_SERIAL.print(", ID ");
  DEBUG_SERIAL.print(present_id);
  DEBUG_SERIAL.print(": ");
  if(dxl.ping(present_id) == true) {
    DEBUG_SERIAL.print("ping succeeded!");
    DEBUG_SERIAL.print(", Model Number: ");
    DEBUG_SERIAL.println(dxl.getModelNumber(present_id));
    
    // Turn off torque when configuring items in EEPROM area
    dxl.torqueOff(present_id);
    
    // set a new ID for DYNAMIXEL. Do not use ID 200
    new_id = 5;
    if(dxl.setID(present_id, new_id) == true){
      present_id = new_id;
      DEBUG_SERIAL.print("ID has been successfully changed to ");
      DEBUG_SERIAL.println(new_id);

    // set new ID again to ensure completion
      new_id = 5;
      if(dxl.setID(present_id, new_id) == true){
        present_id = new_id;
        DEBUG_SERIAL.print("ID has been successfully established as ");
        DEBUG_SERIAL.println(new_id);
      }else{
        DEBUG_SERIAL.print("Failed to change ID to ");
        DEBUG_SERIAL.println(new_id);
      }
    }else{
      DEBUG_SERIAL.print("Failed to change ID to ");
      DEBUG_SERIAL.println(new_id);
    }
  }
  else{
    DEBUG_SERIAL.println("ping failed!");
  }
}

void loop() {

}
