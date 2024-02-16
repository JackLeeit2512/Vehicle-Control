#include <Servo.h>     
Servo myservo; 

int _status = 0;

// LEFT Motor 
#define in1 14 // D5
#define in2 12 // D6

// RIGHT Motor 
#define in3 13 // D7
#define in4 15 // D8

int state = 0;
int rotVal = 110;

#define servoPIN 5 // D1

// light system
int leftLED = 2;
int rightLED = 0;
int headLED = 10;

int headLedState = 1;


void setupPinMode() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  myservo.attach(servoPIN);
  myservo.write(120);

  // light
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(headLED, OUTPUT);
}

void BlynkLed(int pin){
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
  delay(500);
}

void SignalLeft(int value){
  if(value == 1){
    BlynkLed(leftLED);
  }
  else if(value == 0){
    TurnOff(leftLED);
  }
}

void SignalRight(int value){
  if(value == 1){
    BlynkLed(rightLED);
  }
  else if(value == 0){
    TurnOff(rightLED);
  }
}

void HeadLight(){
  headLedState = !headLedState;
  digitalWrite(headLED, headLedState);
}

void TurnOff(int pin){
  digitalWrite(pin, HIGH);
}

void leftMotor(int speed, int signal){
  if(signal == 0){
    // ledcSetup(pwmChannel_0, 5000, 8);
    // ledcAttachPin(in3, pwmChannel_0);
    // ledcWrite(pwmChannel_0, speed); 
    analogWrite(in3, speed);
  }
  else if(signal == 1){
    // ledcSetup(pwmChannel_1, 5000, 8);
    // ledcAttachPin(in4, pwmChannel_1);
    // ledcWrite(pwmChannel_1, speed); 
    analogWrite(in4, speed);
  }
}

void rightMotor(int speed, int signal){
  if(signal == 0){
    // ledcSetup(pwmChannel_2, 5000, 8);
    // ledcAttachPin(in1, pwmChannel_2);
    // ledcWrite(pwmChannel_2, speed); 
    Serial.println("Bug");
    Serial.println(speed);
    analogWrite(in1, speed);
  }
  else if(signal == 1){
    // ledcSetup(pwmChannel_3, 5000, 8);
    // ledcAttachPin(in2, pwmChannel_3);
    // ledcWrite(pwmChannel_3, speed); 
    analogWrite(in2, speed);
  }
  
}

void Stop(){
  //Serial.println("S");
  leftMotor(0, 0);
  rightMotor(0, 0);
  leftMotor(0, 1);
  rightMotor(0, 1);

  myservo.write(rotVal);
}

void Forward(int speed){
  //if(state == -1) Stop();
  // 0 1 
  Serial.println("Buf 2");
  leftMotor(speed, 0);
  rightMotor(speed, 0);
  state = 1;
}

void Back(int speed){
  //if(state == 1) Stop();
  
  //Serial.println("Back");
  leftMotor(speed, 1);
  rightMotor(speed, 1);
  state = -1;
}

void leftForward(int speed){
  // leftMotor(speed - 50, 1);
  // rightMotor(speed, 0);

  myservo.write(rotVal + 15);
  
}
void rightForward(int speed){
  // rightMotor(speed - 50, 1);
  // leftMotor(speed, 0);

  myservo.write(rotVal - 15);
}
void turnLeft(int speed){
  leftMotor(speed, 1);
  rightMotor(speed, 0);
}
void turnRight(int speed){
  leftMotor(speed, 0);
  rightMotor(speed, 1);
}

void statusCar(int status, int speed){
  if(status == 0){
    Stop();
  }
  else if(status == 1){
    Forward(speed);
  }
  else if(status == 2){
    Back(speed);
  }
}