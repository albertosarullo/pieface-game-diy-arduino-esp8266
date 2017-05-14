/* PieFace
 by Alberto Sarullo <http://www.albertosarullo.com> 
*/ 

#include <Servo.h> 

Servo servoPosition;
Servo servoLaunch;

int rightButtonPin = 4;
int leftButtonPin = 5;
int servoLaunchPin = 0;
int servoPositionPin = 2;

int rightButtonValue;
int leftButtonValue;
int oldRightButtonValue;
int oldLeftButtonValue;

int delta = 0;
int limit = 17;

void setup() 
{ 
  servoPosition.attach(servoPositionPin);
  servoLaunch.attach(servoLaunchPin);
  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
} 

void launch() {
  servoLaunch.write(175); // open (launch)
}

void block() {
  servoLaunch.write(135); // close
}

void loop() 
{ 
  int rightButtonValue = digitalRead(rightButtonPin);
  int leftButtonValue = digitalRead(leftButtonPin);
    
  if (rightButtonValue && !oldRightButtonValue) {
    delta = delta + 1;
  }
  if (leftButtonValue && !oldLeftButtonValue) {
    delta = delta - 1;
  }

  digitalWrite(LED_BUILTIN, !(leftButtonValue || rightButtonValue));

  // min: 55°, max: 125°
  servoPosition.write(90 + delta * 1.7);
  
  if (delta > limit || delta < -limit) {
     launch();
  } else {
     block();
  }

  oldRightButtonValue = rightButtonValue;
  oldLeftButtonValue  = leftButtonValue;
  
  delay(10);
} 

