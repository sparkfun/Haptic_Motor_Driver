//DIY Heated Massage Slippers
//Waveforms 16, 17 and 52 cycled to give your feet some TLC
//Use with ERM type Motors
//Try out other libraries (1-5, 7)
//and play around with the Loop Gain, 
//BACKEMF gain, braking factor etc. in
//Feedback register through MotorSelect function

//Hardware Setup 
//LED1 = D9
//LED2 = D10
//LED3 = D11
//Button = D2
//MOSFET = D3
//SCL(HMD) = SCL
//SDA(HMD) = SDA

#include <Sparkfun_DRV2605L.h>
#include <Wire.h>

SFE_HMD_DRV2605L HMD;
uint8_t waveform=16;
uint8_t seq =0;
int buttonPin = 2;
boolean buttonPress = false;
int fetPin = 3;
int led1 = 9;
int led2=10;
int led3=11;
int mode;

void setup() 
{
  HMD.begin();
  HMD.MotorSelect(0x0A);
  HMD.Library(7); //change to 6 for LRA motors 

  //for LEDs and Button:
  pinMode(buttonPin, INPUT);  
  pinMode(fetPin, OUTPUT);  
  pinMode(led1, OUTPUT);  
  pinMode(led2, OUTPUT);  
  pinMode(led3, OUTPUT);  
}
void loop() 
{
  //Heat Intensity w/LED indicator  
  //Increment mode on depress, unless mode = 3, then reset to 0
  if (buttonPress && digitalRead(buttonPin) == LOW)
  {
    mode = mode == 3 ? 0 : mode + 1;
  }
  //Assign button state
buttonPress = digitalRead(buttonPin);
  switch (mode)
  {
    case 0:
      analogWrite(fetPin, 0); //off
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      break;
    case 1:
      analogWrite(fetPin, 85); //33% duty cycle
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      break;
    case 2:
      analogWrite(fetPin, 170); //66% duty cycle
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      break;
    case 3:
      analogWrite(fetPin, 255); //100% duty cycle
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      break;
  }
  uint8_t var=0;
  while(var<25)
  {
  waveform=16;
  HMD.Waveform(seq, waveform);  
  HMD.Waveform(seq+1, 0);    
  HMD.go();
  delay(100);
  var++;
  }
  if(var=25)
  {
  while (var<50)
  {
  waveform=17;
  HMD.Waveform(seq, 17);  
  HMD.Waveform(seq+1, 0);    
  HMD.go();
  delay(500);
  var++;
  }
  }
  if(var=50)
  {
 
  while (var<75)
  {
  waveform=52;
  HMD.Waveform(seq, waveform);  
  HMD.Waveform(seq+1, 0);    
  HMD.go();
  delay(500);
  var++;
  }
  }
  if(var=75)
  {
    var=0;
  }  
 }
