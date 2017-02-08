/******************************************************************************
SFE_DRV2605L.cpp
SFE_DRV2605L Library CPP File
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
#endif

#include <Wire.h>
#include <Sparkfun_DRV2605L.h>

SFE_HMD_DRV2605L::SFE_HMD_DRV2605L() 
{

}


bool SFE_HMD_DRV2605L::begin() 
{
  Wire.begin();
  //Get a read from the status register
  //Want this to Read 0xE0, any other value than 0 and you have tripped the over-current protection=wrong motor
  uint8_t status = readDRV2605L(STATUS_REG);
  Serial.print("Status Register 0x"); 
  Serial.println(status, HEX);
 
 
  return true;
}

//Select Mode
 //Write 0x00 to get out of standby and use internal trigger (using GO command)
 //Write 0x01 to get out of standby + use External Trigger (edge triggered)
 //Write 0x02 to get out of standby + External Trigger (level triggered)
 //Write 0x03 to get out of standby + PWM input and analog output
 //Write 0x04 to use Audio to Vibe
 //Write 0x05 to use real time playback
 //Write 0x06 to perform a diagnostic - result stored in diagnostic bit in register 0x00
 //Write 0x07 to run auto calibration
 
void SFE_HMD_DRV2605L::Mode(uint8_t mod)
{
	writeDRV2605L(MODE_REG, mod);	
}

//Select ERM or LRA 
//Set Motor Type Using the Feedback Control Register
//Set ERM or LRA
//Example: 0X39 0011 1001: ERM Mode, 4x Brake factor, Medium Gain, 1.365x Back EMF
//Example: 0xB9 1011 1001: LRA MODE, 4X Brake Factor, Medium Gain, 7.5x Back EMF 
void SFE_HMD_DRV2605L::MotorSelect(uint8_t val)
{
	writeDRV2605L(FEEDBACK_REG, val);
	
	//uint8_t motor = readDRV2605L(FEEDBACK_REG);
    //Serial.print("Feedback Register/Motor Selector 0x"); Serial.println(motor, HEX);
}


//Select Library
void SFE_HMD_DRV2605L::Library(uint8_t lib)
{
	writeDRV2605L(LIB_REG, lib);
}

//Select waveform from list of waveform library effects 
//data sheet page 60. This function selects the sequencer
//and the effects from the library. 
void SFE_HMD_DRV2605L::Waveform(uint8_t seq, uint8_t wav)
 {
  writeDRV2605L(WAVESEQ1+seq, wav);
 }

 //Go command
void SFE_HMD_DRV2605L::go() 
{
  writeDRV2605L(GO_REG, 1);
}

//Stop Command
void SFE_HMD_DRV2605L::stop() 
{
  writeDRV2605L(GO_REG, 0); //write 0 back to go bit to diable internal trigger
}

//Select real time playback features 
void SFE_HMD_DRV2605L::RTP(uint8_t val)
{
  writeDRV2605L(RTP_REG, val); // Default 0x00, the mode (reg 0x01) must be set to 5 for this to work
  //uint8_t rtp = readDRV2605L(RTP_REG);
  //Serial.print("Real-Time Playback Register 0x"); Serial.println(rtp, HEX); //expect to see 0x00
}

 //Select overdrive time offset values
 void SFE_HMD_DRV2605L::overdrive(uint8_t drive)
 {
	 writeDRV2605L(OVERDRIVE_REG, drive);
 }
 
 //Select Sustain Time offset, positive values
 void SFE_HMD_DRV2605L::SusPOS(uint8_t pos)
 {
	 writeDRV2605L(SUSTAINOFFSETPOS_REG, pos);
 }
 
 //Select Sustain Time offset, negative values
 void SFE_HMD_DRV2605L::SusNEG(uint8_t neg)
 {
	 writeDRV2605L(SUSTAINOFFSETNEG_REG, neg);
 }
 
 //Select Brake Time offset values
 void SFE_HMD_DRV2605L::breaktime(uint8_t brk)
 {
	 writeDRV2605L(BREAKTIME_REG, brk);
 }
 
  //Select Audio-to-Vibe control values
 void SFE_HMD_DRV2605L::Audio2Vibe(uint8_t a2v)
 {
	 writeDRV2605L(AUDIOCTRL_REG, a2v);
 }
 
 
 //Select Audio-to-Vibe minimum input level values
 void SFE_HMD_DRV2605L::AudMin(uint8_t min)
 {
	 writeDRV2605L(AUDMINLVL_REG, min);
 }
 
 
 //Select Audio-to-Vibe minimum input level values
 void SFE_HMD_DRV2605L::AudMax(uint8_t max)
 {
	 writeDRV2605L(AUDMAXLVL_REG, max);
 }
 
//Select Audio-to-Vibe minimum input level values
 void SFE_HMD_DRV2605L::AudMinDrive(uint8_t mnd)
 {
	 writeDRV2605L(AUDMINDRIVE_REG, mnd);
 } 
 
 //Select Audio-to-Vibe maximum input level values
 void SFE_HMD_DRV2605L::AudMaxDrive(uint8_t mxd)
 {
	 writeDRV2605L(AUDMAXDRIVE_REG, mxd);
 } 
 
  //Select Rated Voltage 
 void SFE_HMD_DRV2605L::ratevolt(uint8_t rat)
 {
	 writeDRV2605L(RATEDVOLT_REG, rat);
 } 
 
 //Select overdrive clamp voltage values 
 void SFE_HMD_DRV2605L::clamp(uint8_t clp)
 {
	 writeDRV2605L(OVERDRIVECLAMP_REG, clp);
 } 
 
 //Control 1 register : datasheet page 44
 void SFE_HMD_DRV2605L::cntrl1(uint8_t c1)
 {
	 writeDRV2605L(CONTROL1_REG, c1);
 } 
 
  //Control 2 register : datasheet page 45
 void SFE_HMD_DRV2605L::cntrl2(uint8_t c2)
 {
	 writeDRV2605L(CONTROL2_REG, c2);
 } 
 
  //Control 3 register : datasheet page 48
 void SFE_HMD_DRV2605L::cntrl3(uint8_t c3)
 {
	 writeDRV2605L(CONTROL3_REG, c3);
 } 
 
  //Control 4 register : datasheet page 49
 void SFE_HMD_DRV2605L::cntrl4(uint8_t c4)
 {
	 writeDRV2605L(CONTROL4_REG, c4);
 } 
 
  //Control 5 register : datasheet page 50
 void SFE_HMD_DRV2605L::cntrl5(uint8_t c5)
 {
	 writeDRV2605L(CONTROL5_REG, c5);
 } 
 
  //Select LRA Open Loop Period Values 
 void SFE_HMD_DRV2605L::OLP(uint8_t olp)
 {
	 writeDRV2605L(OLP_REG, olp);
 } 
 
//Read the voltage monitor values 
//vdd=Vbatt[7:0] x 5.6V/255
 void SFE_HMD_DRV2605L::Vbatt(void)
 {
  uint8_t VBATT=readDRV2605L(VBATMONITOR_REG);
  //Serial.print("Battery Voltage 0x"); 
  //Serial.println(VBATT, HEX);
 } 

//Read the LRA resonance period register 
//LRA Period(us) = LRA_Period[7:0] x 98.46us 
 void SFE_HMD_DRV2605L::LRAPER(void)
 {
	 uint8_t PER = readDRV2605L(LRARESPERIOD_REG);
	// Serial.print("LRA resonance period 0x");
	 //Serial.println(PER, HEX);
 }
 
 
//Read function
uint8_t SFE_HMD_DRV2605L::readDRV2605L(uint8_t reg) 
{
  uint8_t var ;
   // Enable I2C Read
    Wire.beginTransmission(I2C_ADDR);
    Wire.write((byte)reg);
    Wire.endTransmission();
    Wire.requestFrom((byte)I2C_ADDR, (byte)1);
    var = Wire.read();

 
  return var;
}

//Write Function 
void SFE_HMD_DRV2605L::writeDRV2605L(uint8_t where, uint8_t what)
{
   // Enable I2C write
    Wire.beginTransmission(I2C_ADDR);
    Wire.write((byte)where);
    Wire.write((byte)what);
    Wire.endTransmission();
}




