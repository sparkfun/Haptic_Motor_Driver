/******************************************************************************
SFE_DRV2605L.h
SFE_DRV2605L Library Header File
Mary West @ SparkFun Electronics
Original Creation Date: 11/14/2016


This file prototypes the DRV2605L class, implemented in SFE_HMD_DRV2605L.cpp. In
addition, it defines every register in the DRV2605L.

Development environment specifics:
	IDE: Arduino 1.6.12
	Hardware Platform: Arduino Uno
	Haptic Motor Driver DRV2605L Breakout Version: 1.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
	#include "pins_arduino.h"
#endif

#include <Wire.h>


//I2C address
#define I2C_ADDR 0x5A

//The Status Register (0x00): The Device ID is bits 7-5. For DRV2605L it should be 7 or 111. 
//bits 4 and 2 are reserved. Bit 3 is the diagnostic result. You want to see 0. 
//bit 1 is the over temp flag, you want this to be 0
//bit 0 is  over current flag, you want this to be zero. 
// Ideally the register will read 0xE0.
#define STATUS_REG 0x00 

//The Mode Register (0x01): 
//Default 010000000 -- Need to get it out of Standby
//Set to 0000 0000=0x00 to use Internal Trigger
//Set to 0000 0001=0x01 to use External Trigger (edge mode)(like a switch on the IN pin)
//Set to 0000 0010=0x02 to use External Trigger (level mode)
//Set to 0000 0011=0x03 to use PWM input and analog output
//Set to 0000 0100=0x04 to use Audio to Vibe 
//Set to 0000 0101=0x05 to use Real-Time Playback
//Set to 0000 0110=0x06 to perform a diagnostic test - result stored in Diagnostic bit in register 0x00
//Set to 0000 0111 =0x07 to run auto calibration 
#define MODE_REG 0x01

//The Feedback Control Register (0x1A)
//bit 7: 0 for ERM, 1 for LRA -- Default is 0
//Bits 6-4 control brake factor
//bits 3-2 control the Loop gain
//bit 1-0 control the BEMF gain
#define FEEDBACK_REG 0x1A

//The Real-Time Playback Register (0x02)
//There are 6 ERM libraries. 
#define RTP_REG 0x02

//The Library Selection Register (0x03)
//See table 1 in Data Sheet for 
#define LIB_REG 0x03

//The waveform Sequencer Register (0X04 to 0x0B)
#define WAVESEQ1 0x04 //Bit 7: set this include a wait time between playback                                                                                                                                                                                 
#define WAVESEQ2 0x05
#define WAVESEQ3 0x06
#define WAVESEQ4 0x07
#define WAVESEQ5 0x08
#define WAVESEQ6 0x09
#define WAVESEQ7 0x0A
#define WAVESEQ8 0x0B

//The Go register (0x0C)
//Set to 0000 0001=0x01 to set the go bit
#define GO_REG 0x0C

//The Overdrive Time Offset Register (0x0D)
//Only useful in open loop mode
#define OVERDRIVE_REG 0x0D

//The Sustain Time Offset, Positive Register (0x0E)
#define SUSTAINOFFSETPOS_REG 0x0E

//The Sustain Time Offset, Negative Register (0x0F)
#define SUSTAINOFFSETNEG_REG 0x0F

//The Break Time Offset Register (0x10)
#define BREAKTIME_REG 0x10

//The Audio to Vibe control Register (0x11)
#define AUDIOCTRL_REG 0x11

//The Audio to vibe minimum input level Register (0x12)
#define AUDMINLVL_REG 0x12

//The Audio to Vibe maximum input level Register (0x13)
#define AUDMAXLVL_REG 0x13

// Audio to Vibe minimum output Drive Register (0x14)
#define AUDMINDRIVE_REG 0x14

//Audio to Vibe maximum output Drive Register (0x15)
#define AUDMAXDRIVE_REG 0X15

//The rated Voltage Register (0x16)
#define RATEDVOLT_REG 0x16

//The Overdive clamp Voltage (0x17)
#define OVERDRIVECLAMP_REG 0x17

//The Auto-Calibration Compensation - Result Register (0x18)
#define COMPRESULT_REG 0x18

//The Auto-Calibration Back-EMF Result Register (0x19)
#define BACKEMF_REG 0x19

//The Control1 Register (0x1B)
//For AC coupling analog inputs and 
//Controlling Drive time 
#define CONTROL1_REG 0x1B

//The Control2 Register (0x1C)
//See Data Sheet page 45
#define CONTROL2_REG 0x1C

//The COntrol3 Register (0x1D)
//See data sheet page 48
#define CONTROL3_REG 0x1D

//The Control4 Register (0x1E)
//See Data sheet page 49
#define CONTROL4_REG 0x1E

//The Control5 Register (0x1F)
//See Data Sheet page 50
#define CONTROL5_REG 0X1F

//The LRA Open Loop Period Register (0x20)
//This register sets the period to be used for driving an LRA when 
//Open Loop mode is selected: see data sheet page 50.
#define OLP_REG 0x20

//The V(Batt) Voltage Monitor Register (0x21)
//This bit provides a real-time reading of the supply voltage 
//at the VDD pin. The Device must be actively sending a waveform to take 
//reading Vdd=Vbatt[7:0]*5.6V/255
#define VBATMONITOR_REG 0x21

//The LRA Resonance-Period Register 
//This bit reports the measurement of the LRA resonance period
#define LRARESPERIOD_REG 0x22


class SFE_HMD_DRV2605L 
{
 public:

  SFE_HMD_DRV2605L(void);
  bool begin(void);
  void writeDRV2605L(uint8_t reg, uint8_t val);
  uint8_t readDRV2605L(uint8_t reg);
  void Mode(uint8_t mode);
  void MotorSelect(uint8_t val);
  void RTP(uint8_t val);
  void Library(uint8_t val);
  void Waveform(uint8_t seq, uint8_t wav);
  void go(void);
  void stop(void);
  void overdrive(uint8_t drive);
  void SusPOS(uint8_t pos);
  void SusNEG(uint8_t neg);
  void breaktime(uint8_t brk);
  void Audio2Vibe(uint8_t a2v);
  void AudMin(uint8_t min);
  void AudMax(uint8_t max);
  void AudMinDrive(uint8_t mnd);
  void AudMaxDrive(uint8_t mxd);
  void ratevolt(uint8_t rat);
  void clamp(uint8_t clp);
  void cntrl1(uint8_t c1);
  void cntrl2(uint8_t c2);
  void cntrl3(uint8_t c3);
  void cntrl4(uint8_t c4);
  void cntrl5(uint8_t c5);
  void OLP(uint8_t olp);
  void Vbatt(void);
  void LRAPER(void);
  
 private:

};

