#include <Servo.h>

Servo base, up, forward, claw; 
void pos_write (int pos);

void setup()
{
  base.attach(3);
  forward.attach(5);
  up.attach(6);
  claw.attach(9);
  
  pos_write(1090);
  pos_write(2050);
  pos_write(3110);
  pos_write(4060);
  Serial.begin(9600);
}

void loop()
{
 
 if (Serial.available())
  {
    char flag = Serial.read();
    int pos = Serial.parseInt();
    pos_write(pos);     
  }
}


void pos_write (int pos)
{

  if (pos>=1000&&pos<=1180)
  {
    pos=map(pos,1000,1180,0,180);
    base.write(constrain(pos,0,180));
  }
  
  if (pos>=2000&&pos<=2180)
  {
    pos=map(pos,2000,2180,0,180);
    forward.write(constrain(pos,0,180));
  }
  
  if (pos>=3000&&pos<=3180)
  {
    pos=map(pos,3000,3180,0,180);
    up.write(constrain(pos,0,180)); 
  }
  
  if (pos>=4000&&pos<=4180)
  {
    pos=map(pos,4000,4180,0,180);
    claw.write(constrain(pos,0,180));
  }
  
  delay (10);
}
