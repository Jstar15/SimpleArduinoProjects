///
/// \file  TestRDA5807M.ino
/// \brief An Arduino sketch to operate a SI4705 chip based radio using the Radio library.
///
/// \author Matthias Hertel, http://www.mathertel.de
/// \copyright Copyright (c) 2014 by Matthias Hertel.\n
/// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
///
/// \details
/// This sketch implements a "as simple as possible" radio without any possibility to modify the settings after initializing the chip.\n
/// The radio chip is initialized and setup to a fixed band and frequency. These settings can be changed by modifying the 
/// FIX_BAND and FIX_STATION definitions. 
///
/// Open the Serial console with 57600 baud to see the current radio information.
///
/// Wiring
/// ------ 
/// The RDA5807M board/chip has to be connected by using the following connections:
/// | Arduino UNO pin    | Radio chip signal  | 
/// | -------------------| -------------------| 
/// | 3.3V (red)         | VCC                | 
/// | GND (black)        | GND                | 
/// | A5 or SCL (yellow) | SCLK               | 
/// | A4 or SDA (blue)   | SDIO               | 
/// The locations of the pins on the UNO board are written on the PCB.
/// The locations of the signals on the RDA5807M side depend on the board you use.
///
/// More documentation and source code is available at http://www.mathertel.de/Arduino
///
/// ChangeLog:
/// ----------
/// * 05.12.2014 created.
/// * 19.05.2015 extended.

#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include <RDA5807M.h>

// ----- Fixed settings here. -----

#define FIX_BAND     RADIO_BAND_FM   ///< The band that will be tuned by this sketch is FM.
#define FIX_STATION   9620
#define FIX_VOLUME   8              ///< The volume that will be set by this sketch is level 4.
RDA5807M radio;    // Create an instance of Class for RDA5807M Chip

RADIO_FREQ preset[] = {
  9620, //captial fm
  10385, //radio capital  nottingham
  10660, //smooth east midlands
  9750 //kemit
};

int presetindex = 0;
int val = 0;       // variable to store the value coming from the sensor
int oldval = 0;
/// Setup a FM only radio configuration
/// with some debugging on the Serial port


void setup() {
    
  // open the Serial port
  Serial.begin(57600);
  Serial.println("Radio...");
  delay(500);

  // Initialize the Radio 
  radio.init();

  // Enable information to the Serial port
  radio.debugEnable();

  // Set all radio setting to the fixed values.
  radio.setBandFrequency(FIX_BAND, FIX_STATION);
  radio.setVolume(FIX_VOLUME);
   //radio.setBassBoost(true);
  radio.setMono(false);
  radio.setMute(false);
} // 


/// show the current chip data every 3 seconds.
void loop() {
  val = analogRead(0);    // read the value from the sensor
  val = val*0.05; 
  Serial.println(val);
  if (val > oldval+8 || val < oldval-8){
      presetindex = presetindex +1;
      if(presetindex == 4 ){
        presetindex = 0;  
        }
        radio.setBandFrequency(FIX_BAND, preset[presetindex]);
      //radio.setVolume(val);
     //next station
   }
   oldval = val;
     // Send the value just read down the serial cable
  char s[12];
  radio.formatFrequency(s, sizeof(s));
  Serial.print("Station:"); 
  Serial.println(s);
  
  Serial.print("Radio:"); 
  radio.debugRadioInfo();
  
  Serial.print("Audio:"); 
  radio.debugAudioInfo();

  delay(400);
} // loop

// End.
