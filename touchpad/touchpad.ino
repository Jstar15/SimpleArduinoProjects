 
#include <Mouse.h>
#include <PS2Mouse.h>

//set touch pad pins
const int MOUSE_DATA = 5;
const int MOUSE_CLOCK = 6;

// set pin numbers for mouse buttons:
const int buttonPin = 8;     // the number of the pushbutton pin
const int buttonPin2 = 7;     // the number of the pushbutton pin

// variables will change states for each button:
int buttonState = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status

PS2Mouse mouse(MOUSE_CLOCK, MOUSE_DATA, STREAM); //initiate mouse object

void setup(){ 
  Serial.begin(9600);
  mouse.initialize(); //input pin 6 , 5
  Mouse.begin(); //output usb  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop(){
  int data[2];
  mouse.report(data);

  //move cursor according to touchpad
  int x = data[1] * 2; // X Movement Data
  int y = data[2] * (-1) * 2; //Y Movement Data (invert y axis)
  Mouse.move(x, y); // move mouse cursor accordingly given x and y

  //initiate mouse right click if button is clicked if not release
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
      Mouse.press(MOUSE_RIGHT);
  } else{
      Mouse.release(MOUSE_RIGHT);
    }
    
  //initiate mouse left click if button is clicked if not release
  buttonState2 = digitalRead(buttonPin2);
  if (buttonState2 == HIGH) {
      Mouse.press();
  } else{
      Mouse.release();
    }
}
