# 5DOF_Robot_Arm
All Files to create your own 5DOF robot arm using the Dynamixel XL-330.
The Dynamixel XL-330-M288-T micro servos and the Arduino MKR shield were provided by ROBOTIS. 


https://www.robotis.us/

https://www.robotis.us/dynamixel-xl330-m288-t/

https://www.robotis.us/robotis-blog/dynamixel-xl330-mkr-shield/



All parts were 3D printed using an Ender 3 V2 and all associated hardware was purchased on 
amazon. You will need 1/2" m4 machine screws, washers, and bearings. Links below will take 
you to amazon listings for acceptable hardware.


https://www.amazon.com/gp/product/B00F34Z5VC/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1

https://www.amazon.com/gp/product/B082PYSPR6/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1

https://www.amazon.com/gp/product/B07DNZMNT1/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1

https://www.amazon.com/gp/product/B07RFFMWZT/ref=ppx_yo_dt_b_asin_title_o02_s02?ie=UTF8&psc=1


All code was written using the Arduino IDE and the arm was controlled with the Arduino and 
the Arduino MKR shield provided by ROBOTIS.



# Fusion 360
Fusion project files and STLs are provided so that you may use, modify, or make your own 5DOF robot arm. Review the project files before printing to ensure accuracy and that you are able to print them on your printer. Models were printed at a 0.12 layer height.



# Arduino
The Arduino MKR Wifi 1010 and the Arduino MKR Dynamixel shield were used for this project. All of the Arduino Code is provided to setup, test and use your daisy chained Dynamixel Xl-330's. You will need to connect servos individually, and run the "scan_dynamixel" to acquire their default ID's then reset them using "ID" to a value that you may then use within your application to implement IK or FK. the "5DOF_Arm_Test"" file uses ID's 1-5 and performs simple motions to confirm the servo movements are accurate.




Have fun!
