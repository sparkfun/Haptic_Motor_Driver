// Control the vibration of an ERM motor
// using an AC Coupled Audio Signal into the IN/TRIG pin 

#include <Sparkfun_DRV2605L.h>
#include <Wire.h>

SFE_HMD_DRV2605L HMD;




void setup() 
{
  HMD.begin();
  Serial.begin(9600);
  HMD.Mode(0x04); //Audio INPUT 
  HMD.cntrl1(0xB3); // Set the AC Couple bit in COntrol 1
  HMD.cntrl3(0x62); // Set the Analog bit in Control 3
  HMD.MotorSelect(0x0A);
  HMD.Library(7); //change to 6 for LRA motors 
   
}
void loop() 
{
 }
