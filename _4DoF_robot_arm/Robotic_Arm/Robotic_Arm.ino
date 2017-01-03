/*  Arduino Robotic Arm with Grab
 *  More info: http://www.ardumotive.com/
 *  Dev: Michalis Vasilakis Data: 12/12/2016 Ver: 1.1 */

#include <Servo.h>

//Create servo objects to control servo motors
Servo up_down;  
Servo forward_backward;
Servo rotate;
Servo grab;

//Constants
const int startBT = 7;
const int teachBT = 8;
const int buzzer = 9;
const int potForwardBackward = A3;
const int potUpDown = A2;
const int potRotate = A1;
const int potGrab = A0;
//Max and Min values for servos ! Change them to meet your setup !
const int minGrab=180;
const int maxGrab=126;
const int minRotate=0;
const int maxRotate=100;
const int minUpDown=5;
const int maxUpDown=100;
const int minForwardBackward=160;
const int maxForwardBackward=80;
//-------------------------------------//
//Variables
int readUpDown,readForwardBackward,readRotate,readGrab,readTeach,readStart;
int teachUpDown[100],teachForwardBackward[100],teachRotate[100],teachGrab[100];
boolean started =false;
int index = 1;
int stepSpeed = 20; //Change this to fo faster!

void setup() {
  //Attach Servo motors
  forward_backward.attach(3);
  up_down.attach(4);
  rotate.attach(5); //portokali xontro
  grab.attach(6);  
  //Inputs-Outputs
  pinMode(teachBT, INPUT_PULLUP);
  pinMode(startBT, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  //Do a smooth movement on startup, from home potion to pot position:
  readInputs();
  goHome();
  goPot();
}

void loop() {
  if (!started){
    readInputs();
    moveServos();
    if (readTeach==LOW){
      savePosition();
      tone(buzzer,500);
      delay(500);
      noTone(buzzer);
    }
    if (readStart==LOW){
      tone(buzzer,700);
      started=true;
      delay(1000);
      noTone(buzzer);
    }
  }
  else{
    goHome();
    runTeach();
  }
}

void readInputs(){
  //Read potentiometers
  readUpDown = analogRead(potUpDown);
  readUpDown = map(readUpDown,0,1023,minUpDown,maxUpDown);
  readForwardBackward = analogRead(potForwardBackward);
  readForwardBackward = map(readForwardBackward,0,1023,minForwardBackward,maxForwardBackward);
  readRotate = analogRead(potRotate);
  readRotate = map(readRotate,0,1023,minRotate,maxRotate);
  readGrab = analogRead(potGrab);
  readGrab = map(readGrab,0,1023,minGrab,maxGrab);
  //Read buttons
  readTeach = digitalRead(teachBT);
  readStart = digitalRead(startBT);
  delay(50);
}
void moveServos(){
  up_down.write(readUpDown);
  forward_backward.write(readForwardBackward);
  rotate.write(readRotate);
  grab.write(readGrab);
}

void savePosition(){
  teachUpDown[index] = readUpDown;
  teachForwardBackward[index] = readForwardBackward;
  teachRotate[index] = readRotate;
  teachGrab[index] = readGrab;
  index++;
}

void runTeach(){
  for (int i=0; i<index-1; i++){
    if (teachRotate[i] < teachRotate[i+1]){
      for (int j = teachRotate[i]; j<= teachRotate[i+1]; j++){
        rotate.write(j);
        delay(stepSpeed);
      }
    }
    else if (teachRotate[i] > teachRotate[i+1]){
      for (int j = teachRotate[i]; j>= teachRotate[i+1]; j--){
        rotate.write(j);
        delay(stepSpeed);
      }  
    }
    else{
      rotate.write(teachRotate[i]);
    }
    if (teachGrab[i] < teachGrab[i+1]){
      for (int j = teachGrab[i]; j<= teachGrab[i+1]; j++){
        grab.write(j);
        delay(stepSpeed);
      }
    }
    else if (teachGrab[i] > teachGrab[i+1]){
      for (int j = teachGrab[i]; j>= teachGrab[i+1]; j--){
        grab.write(j);
        delay(stepSpeed);
      } 
    }
    else{
      grab.write(teachGrab[i]);
    }
    if (teachForwardBackward[i] < teachForwardBackward[i+1]){
      for (int j = teachForwardBackward[i]; j<= teachForwardBackward[i+1]; j++){
        forward_backward.write(j);
        delay(stepSpeed);
      }
    }
    else if (teachForwardBackward[i] > teachForwardBackward[i+1]){
      for (int j = teachForwardBackward[i]; j>= teachForwardBackward[i+1]; j--){
        forward_backward.write(j);
        delay(stepSpeed);
      }
    }
    else{
      forward_backward.write(teachForwardBackward[i]);
    }
    if (teachUpDown[i] < teachUpDown[i+1]){
      for (int j = teachUpDown[i]; j<= teachUpDown[i+1]; j++){
        up_down.write(j);
        delay(stepSpeed);
      }
    }
    else if (teachUpDown[i] > teachUpDown[i+1]){
      for (int j = teachUpDown[i]; j>= teachUpDown[i+1]; j--){
        up_down.write(j);
        delay(stepSpeed);
      }
    }
    else{
      up_down.write(teachUpDown[i]);
    }
  }
  started=false;
}

//Change values if it's necessary...
void goHome(){
  if (readForwardBackward < 80){
      for (int j = readForwardBackward; j<=80; j++){
        forward_backward.write(j);
        delay(stepSpeed);
      }
    }
    else if (readForwardBackward > 80){
      for (int j = readForwardBackward; j>=80; j--){
        forward_backward.write(j);
        delay(stepSpeed);
      }
    }
    else{
      forward_backward.write(80);
    }
    if (readUpDown < 32){
      for (int j = readUpDown; j<=32; j++){
        up_down.write(j);
        delay(stepSpeed);
      }
    }
    else if (readUpDown > 32){
      for (int j = readUpDown; j>=32; j--){
        up_down.write(j);
        delay(stepSpeed);
      }
    }
    else{
      up_down.write(32);
    }
    if (readRotate < 0){
      for (int j = readRotate; j<=0; j++){
        rotate.write(j);
        delay(stepSpeed);
      }
    }
    else if (readRotate > 0){
      for (int j = readRotate; j>=0; j--){
        rotate.write(j);
        delay(stepSpeed);
      }
    }
    else{
      rotate.write(0);
    }
    if (readGrab < 148){
      for (int j = readGrab; j<=148; j++){
        grab.write(j);
        delay(stepSpeed);
      }
    }
    else if (readGrab > 148){
      for (int j = readGrab; j>=148; j--){
        grab.write(j);
        delay(stepSpeed);
      }
    }
    else{
      grab.write(148);
    }
    //Always start from home position
    teachForwardBackward[0]= 80;
    teachUpDown[0]=32;
    teachRotate[0]=0;
    teachGrab[0]=148;
}

void goPot(){
    if (0 > readRotate){
      for (int j = 0; j>=readRotate; j--){
        rotate.write(j);
        delay(stepSpeed);
      }
    }
    else if (readRotate > 0){
      for (int j = 0; j<=readRotate; j++){
        rotate.write(j);
        delay(stepSpeed);
      }
    }
    else{
      rotate.write(readRotate);
    }
    if (readGrab > 148){
      for (int j = 148; j<=readGrab; j++){
        grab.write(j);
        delay(stepSpeed);
      }
    }
    else if (readGrab < 148){
      for (int j = 148; j>=readGrab; j--){
        grab.write(j);
        delay(stepSpeed);
      }
    }
    else{
      grab.write(readGrab);
    }
  if (80 > readForwardBackward){
      for (int j = 80; j>=readForwardBackward; j--){
        forward_backward.write(j);
        delay(stepSpeed);
      }
    }
    else if (80 < readForwardBackward){
      for (int j = 80; j<=readForwardBackward; j++){
        forward_backward.write(j);
        delay(stepSpeed);
      }
    }
    else{
      forward_backward.write(readForwardBackward);
    }
    if (32 > readUpDown){
      for (int j = 32; j>=readUpDown; j--){
        up_down.write(j);
        delay(stepSpeed);
      }
    }
    else if (readUpDown > 32){
      for (int j = 32; j<=readUpDown; j++){
        up_down.write(j);
        delay(stepSpeed);
      }
    }
    else{
      up_down.write(readUpDown);
    }
}

