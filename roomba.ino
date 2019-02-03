#include <Servo.h>

Servo myServo; //servo thingy 
const int servoPin = 9;
const int leftPingPin = 12;
const int rightPingPin = 13;
const int rightMotor1 = 5;
const int rightMotor2 = 6;
const int leftMotor2 = 3;
const int leftMotor1 = 11;
const int pumpPin = 2;


// set some offest 

const int angleOffset = 70;

// look at parameters
int wallDist = 50;
int minDist = 50;
int maxSpeed = 156;
float feedBack = 2;




void setup() {
  // put your setup code here, to run once:
  myServo.attach(servoPin);
  myServo.write(angleOffset);

  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);


  pinMode(pumpPin, OUTPUT);

  pumpOff();

  Serial.begin(9600);

}

void loop() {

  // put your main code here, to run repeatedly:
  while(Serial.available() != true){ //run as long as we dont have external instruction 
    
    int left = ping(leftPingPin);
    delay(5);
    int right = ping(rightPingPin);


    Serial.println(left);
    Serial.println(right);

    // start with cheking the left condition
    if (left < minDist){
      stopMotor();
      leftMotor(maxSpeed);
    } else {
      //compute a difference between the wanted distance and acutal distance
      int dif = wallDist - right;
      leftMotor(maxSpeed + (dif*feedBack));
      rightMotor(maxSpeed - (dif*feedBack));
    }
    
  }
  //input detected
  int input = Serial.parseInt();
  if (input = 32){
    leftMotor(maxSpeed/2);
    rightMotor(maxSpeed/2);
  } else if (input = 33){
    stopMotor();
    pumpOn();
    delay(500);
    pumpOff();
  }

}


long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

int ping(int pingPin){
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  return cm;
}

void leftMotor(int spd){
  if (spd>=0){
    if (spd>256){
      spd = 256;
    }
    digitalWrite(leftMotor1, LOW);
    analogWrite(leftMotor2, spd);
  } else {
    if (abs(spd)>256){
      spd = 256;
    }
    digitalWrite(leftMotor2, LOW);
    analogWrite(leftMotor1, abs(spd));
  }
}


void rightMotor(int spd){
  if (spd>=0){
    if (spd>256){
      spd = 256;
    }
    digitalWrite(rightMotor1, LOW);
    analogWrite(rightMotor2, spd);
  } else {
    if (abs(spd)>256){
      spd = 256;
    }
    digitalWrite(rightMotor2, LOW);
    analogWrite(rightMotor1, abs(spd));
  }
}

void stopMotor(){
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW); 
}

void pumpOn(){
  digitalWrite(pumpPin, LOW);  
}


void pumpOff(){
  digitalWrite(pumpPin, HIGH);  
}
