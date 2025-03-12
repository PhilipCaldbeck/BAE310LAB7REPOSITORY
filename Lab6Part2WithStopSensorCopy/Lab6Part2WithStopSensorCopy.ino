/*
  SparkFun Inventor’s Kit
  Circuit 5B - Remote Control Robot

  Control a two wheeled robot by sending direction commands through the serial monitor.
  This sketch was adapted from one of the activities in the SparkFun Guide to Arduino.
  Check out the rest of the book at
  https://www.sparkfun.com/products/14326

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/
const int trigPin = 6;

const int echoPin = 7;

float duration, distance;

//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;           //speed control pin on the motor driver for the left motor
const int BIN2 = 9;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;           //control pin 1 on the motor driver for the left motor

int switchPin = 7;             //switch to turn the robot on and off

const int driveTime = 20;      //this is the number of milliseconds that it takes the robot to drive 1 inch
                               //it is set so that if you tell the robot to drive forward 25 units, the robot drives about 25 inches

const int turnTime = 8;        //this is the number of milliseconds that it takes to turn the robot 1 degree
                               //it is set so that if you tell the robot to turn right 90 units, the robot turns about 90 degrees

                               //Note: these numbers will vary a little bit based on how you mount your motors, the friction of the
                               //surface that your driving on, and fluctuations in the power to the motors.
                               //You can change the driveTime and turnTime to make them more accurate

String botDirection;           //the direction that the robot will drive in (this change which direction the two motors spin in)
String speed;               //the distance to travel in each direction
int angularVelocity;

/********************************************************************************/
void setup()
{
  pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);           //begin serial communication with the computer

  //prompt the user to enter a command
  Serial.println("Enter a direction followed by a speed");
  Serial.println("slow, or medium, or fast");
  Serial.println("Example command: f slow");


 
}

/********************************************************************************/
void loop()
{
  {
    duration = pulseIn(echoPin, HIGH);

   distance = (duration*0.0343)/2;
   if (distance < 10)
    {
      {
        rightMotor(0);
        leftMotor(0);
      }
    }

   Serial.print("Distance:  ");
   Serial.println(distance);
   delay(100);
  }
  if (digitalRead(7) == LOW)
  {                                                     //if the switch is in the ON position
    if (Serial.available() > 0)                         //if the user has sent a command to the RedBoard
    {
      botDirection = Serial.readStringUntil(' ');       //read the characters in the command until you reach the first space
      speed = Serial.readStringUntil('\n');           //read the characters in the command until you reach the second space
      
      if(speed == "slow")
        {
          angularVelocity = 75;
        }
     else if(speed == "medium")
     {
        angularVelocity = 130;
      }
      else if (speed == "fast")
      {
        angularVelocity = 250;
      }
      else if (speed == "")
        {
          angularVelocity = 0;
        }
      
      Serial.print(botDirection);
      Serial.print(" ");
      Serial.println(angularVelocity);

      if (botDirection == "f")                         //if the entered direction is forward
      {
         rightMotor(angularVelocity);                                //drive the right wheel forward
          leftMotor(angularVelocity);                                 //drive the left wheel forward
      }
      else if (botDirection == "b")                         //if the entered direction is forward
      {
         rightMotor(-angularVelocity);                                //drive the right wheel forward
          leftMotor(-angularVelocity);                                 //drive the left wheel forward
      }
      else if (botDirection == "l")                         //if the entered direction is forward
      {
          rightMotor(angularVelocity);                                //drive the right wheel forward
          leftMotor(-angularVelocity);                                 //drive the left wheel forward
      }
      else if (botDirection == "r")                         //if the entered direction is forward
      {
          rightMotor(-angularVelocity);                                //drive the right wheel forward
          leftMotor(angularVelocity);                                 //drive the left wheel forward
      }
      else if (botDirection == "stop") 
      {
        rightMotor(0);
        leftMotor(0);
      }
      
    }
  }
  else
  {
    rightMotor(0);                                  //turn the right motor off
    leftMotor(0);                                   //turn the left motor off
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

}

/********************************************************************************/
void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void leftMotor(int motorSpeed)                        //function for driving the left motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}
//I just needed to modify this for LAB 7.
const int PWMB = 10; //speed control pin on the motor driver for the left motor
const int BIN2 = 9; //control pin 2 on the motor driver for the left motor
const int BIN1 = 8; //control pin 1 on the motor driver for the left motor.
//I added some more stuff.
