#include <Servo.h>

Servo base, up, forward, claw; 
int a=90, b=50,c=110,d=60;
int speed=20;

void pos_write (char mode, int pos);
void pos_base (int pos);
void pos_forward (int pos);
void pos_up (int pos);
void pos_claw (int pos);


void setup()
{
  base.attach(3);
  forward.attach(5);
  up.attach(6);
  claw.attach(9);
  
  Serial.begin(9600);
  
  pos_write('M',a+1000);
  pos_write('M',b+2000);
  pos_write('M',c+3000);
  pos_write('M',d+4000);
}

void loop()
{
 
 if (Serial.available())
  {
    char flag = Serial.read();
    int pos = Serial.parseInt();
    pos_write(flag, pos);     
  }
}


void pos_write (char mode, int pos)
{
switch (mode)
  {
    case 'M':
    {
      if (pos>=1000&&pos<=1180)
      {
        pos=map(pos,1000,1180,0,180);
        pos=constrain(pos,0,180);
        pos_base(pos);        
      }
  
      if (pos>=2000&&pos<=2180)
      {
        pos=map(pos,2000,2180,0,180);
        pos=constrain(pos,0,180);
        pos_forward(pos);                 
      }
      
      if (pos>=3000&&pos<=3180)
      {
        pos=map(pos,3000,3180,0,180);
        pos=constrain(pos,0,180);
        pos_up(pos);
      }
      
      if (pos>=4000&&pos<=4180)
      {
        pos=map(pos,4000,4180,0,180);
        pos=constrain(pos,0,180);
        pos_claw(pos);
      }
      break;
    }
    
    case 'S':
    {
      speed=pos;
      break;
    }
  }  
}

void pos_base(int pos)
{
  if (a<pos)
  {
    for (a;a<=pos;a+=2)
    {
      base.write(a);
      delay(20-speed);
    }
  } 
  
  if (a>pos)
  {
    for (a;a>=pos;a-=2)
    {
      base.write(a);
      delay(20-speed);
    }
  }  
}

void pos_forward(int pos)
{
  if (b<pos)
  {
    for (b;b<=pos;b+=2)
    {
      forward.write(b);
      delay(20-speed);
    }
  }  
      
  if (b>pos)
  {
    for (b;b>=pos;b-=2)
    {
      forward.write(b);
      delay(20-speed);
    }
  }  
}

void pos_up(int pos)
{
  if (c<pos)
  {
    for (c;c<=pos;c+=2)
    {
      up.write(c);
      delay(20-speed);
    }
  }  
      
  if (c>pos)
  {
    for (c;c>=pos;c-=2)
    {
      up.write(c);
      delay(20-speed);
    }
  }  
}

void pos_claw(int pos)
{
  if (d<pos)
  {
    for (d;d<=pos;d+=2)
    {
      claw.write(d);
      delay(20-speed);
    }
  }  
      
  if (d>pos)
  {
    for (d;d>=pos;d-=2)
    {
      claw.write(d);
      delay(20-speed);
    }
  }  
}
