#include <Servo.h>

Servo base, up, forward, claw; 
void pos_write (char c, int pos);
int b;

void setup()
{
  base.attach(3);
  forward.attach(5);
  up.attach(6);
  claw.attach(9);
  pos_write('A',90);
  pos_write('B',50);
  pos_write('C',110);
  pos_write('D',60);
  Serial.begin(9600);
}

void loop()
{
 if (Serial.available())
  {
    char flag = Serial.read();
    int pos = Serial.parseInt();
    pos_write(flag,pos);
  }
}


void pos_write (char c, int pos)
{
  switch(c)
{
  case 'A':
  {
    base.write(constrain(pos,0,180));
    break;
  }
  case 'B':
  {
 
    forward.write(constrain(pos,20,100));
    break;
  }
  case 'C':
  {
    up.write(constrain(pos,40,110));
    break;
  }
  case 'D':
  {
    claw.write(constrain(pos,60,160));
    break;
  }
}
delay (10);
return;
}
