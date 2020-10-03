#define S1 A0    //pins for sensor
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A4
#define S6 A5

#define M1 1     //pins for motor driver
#define M2 2
#define M3 3
#define M4 4
#define M5 5
#define M6 6

void setup() 
{
  Serial.begin(9600);
  pinMode(S1,INPUT);      /*input pins for the sensor*/
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  pinMode(S5,INPUT);
  pinMode(S6,INPUT);
}

const int Sense=900;   //This value needs to be set after optimization of the sensors - Make an optimization script for sensors

char y[7];
void sensor_read()
{
  int i, x[6];
  x[0]=analogRead(S1);
  x[1]=analogRead(S2);
  x[2]=analogRead(S3);
  x[3]=analogRead(S4);
  x[4]=analogRead(S5);
  x[5]=analogRead(S6);
  //x[6]=analogRead(A6);
  for(i=0;i<6;i++)
  {
    if(x[i]<Sense)
      y[i]='B';
    else
      y[i]='W';
    Serial.println(y[i]);
  }
}

String s;
void motor_control()
{
  for(int i=0; i<6; i++)
    s=y[i];

  //TRACK 1 
  if (s=="BBBWWW")
    forward();

  else if(s=="BBBBWW")  
    right();

  else if(s=="BBBBBW")
    hardright();

  else if(s=="BBBBBB")
     back();

  else if(s=="BBWWWW")    //common case for both tracks
      right();

  else if(s=="BWWWWW")
      back();

  else if(s=="WWWWWW")
      back();

    //TRACK 2
   else if(s=="BBWWBB")
      forward();

   else if(s=="BBWBBB")
      left();

   else if(s=="BBBWBB")
      right();

   else if(s=="BWBBBB")
      back();

   else if(s=="BBBBWB")
      back();

   else if(s=="WWWWBB")
      left();

}

//left->anticlockwise     right->clockwise   for motor
void forward()
{
    digitalWrite(M1,LOW);
    digitalWrite(M2,HIGH);
    analogWrite(M3,255);
    digitalWrite(M4,HIGH);
    digitalWrite(M5,LOW);
    analogWrite(M6,255);
}
void back()
{
    digitalWrite(M1,HIGH);
    digitalWrite(M2,LOW);
    analogWrite(M3,255);
    digitalWrite(M4,LOW);
    digitalWrite(M5,HIGH);
    analogWrite(M6,255);
}
void left()
{
    digitalWrite(M1,LOW);
    digitalWrite(M2,HIGH);
    analogWrite(M3,200);
    digitalWrite(M4,HIGH);
    digitalWrite(M5,LOW);
    analogWrite(M6,255);
}
void right()
{
    digitalWrite(M1,LOW);
    digitalWrite(M2,HIGH);
    analogWrite(M3,255);
    digitalWrite(M4,HIGH);
    digitalWrite(M5,LOW);
    analogWrite(M6,200);
}
void hardleft()
{
    digitalWrite(M1,LOW);
    digitalWrite(M2,LOW);
    analogWrite(M3,0);
    digitalWrite(M4,HIGH);
    digitalWrite(M5,LOW);
    analogWrite(M6,240);
}
void hardright()
{
    digitalWrite(M1,LOW);
    digitalWrite(M2,HIGH);
    analogWrite(M3,240);
    digitalWrite(M4,LOW);
    digitalWrite(M5,LOW);
    analogWrite(M6,0);
}

void loop() 
{
  sensor_read();
  motor_control();
}

void bluetooth_module()
{
   if (Serial.available())
 {
    char c= Serial.read();
    Serial.println(c);

     if(c=='F')
       forward();

     else if(c=='B')
       back();

     else if(c=='L')
       left();

     else if(c=='R')
       right();
  }
}
