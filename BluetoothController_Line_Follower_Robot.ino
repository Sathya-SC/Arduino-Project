#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX, TX

#define IN1 9   //RIGHT Motor1  L298 Pin  
#define IN2 8   //RIGHT Motor1  L298 Pin 
#define IN3 7   //LEFT Motor1  L298 Pin  
#define IN4 6   //LEFT Motor1  L298 Pin 
#define ena 10  //RIGHT Motor1  L298 Pin ena 
#define enb 5   //RIGHT Motor1  L298 Pin enb 

#define S_L A0 //ir sensor Left
#define S_R A1 //ir sensor Right

int Mode=0;
int BT_Data;
int Speed=120;

void setup() {
  // put your setup code here, to run once:
  pinMode(S_L,INPUT);
  pinMode(S_R,INPUT);
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);

Serial.begin(9600);
BTSerial.begin(9600);
delay(500); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(BTSerial.available()>0) //Data is sent
  {
    BT_Data=BTSerial.read();
  }    
  
  analogWrite(ena, Speed); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
  analogWrite(enb, Speed); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 

  int S_L = digitalRead(A0);
  int S_R = digitalRead(A1);
  
if(Mode==0)
{
  // Bluetooth Controller Command
  if(BT_Data == 1)
  {
    forword();
  }
  else if(BT_Data == 2)
  {
    backword(); 
  }
  else if(BT_Data == 3)
  {
    turnLeft();
  }
  else if(BT_Data == 4)
  {
    turnRight();
  }
  else if(BT_Data == 5)
  {
    Stop();
  }

  //Voice Controller Command 
  else if(BT_Data == 6)
  {
    forword();
    delay(200);
    BT_Data = 5; 
  }
  else if(BT_Data == 7)
  {
    backword();
    delay(200);
    BT_Data = 5;
  }
  else if(BT_Data == 8)
  {
    turnLeft();  
    delay(200);  
    BT_Data = 5;
  }
  else if(BT_Data == 9)
  {
    turnRight(); 
    delay(200);  
    BT_Data = 5;
  }
  
}
  else
  {    
  //Line Follower Command
  if(S_L==0 && S_R==0)
  {
    forword();
  }
  if(S_L==0 && S_R==1)
  {
    turnLeft(); 
  }
  if(S_L==1 && S_R==0)
  {
    turnRight();
  }
  if(S_L==1 && S_R==1)
  {
    Stop();
  }
  }
  
  delay(10);

  if(BTSerial.available()<0)
 {
   //Bluetooth isn't working
 }
  
}

void forword()
{
  digitalWrite(IN1,HIGH); //Right Motor forword Pin
  digitalWrite(IN2,LOW);  //Right Motor backword Pin
  digitalWrite(IN3,HIGH); //Left Motor backword Pin
  digitalWrite(IN4,LOW);  //Left Motor forword Pin
}

void turnLeft()
{
  digitalWrite(IN1,HIGH); //Right Motor forword Pin
  digitalWrite(IN2,LOW);  //Right Motor backword Pin
  digitalWrite(IN3,HIGH); //Left Motor backword Pin
  digitalWrite(IN4,LOW);  //Left Motor forword Pin
}

void turnRight()
{
  digitalWrite(IN1,LOW);  //Right Motor forword Pin
  digitalWrite(IN2,HIGH); //Right Motor backword Pin
  digitalWrite(IN3,LOW);  //Left Motor backword Pin
  digitalWrite(IN4,HIGH); //Left Motor forword Pin
}

void backword()
{
  digitalWrite(IN1,LOW);  //Right Motor forword Pin
  digitalWrite(IN2,HIGH); //Right Motor backword Pin
  digitalWrite(IN3,HIGH); //Left Motor backword Pin
  digitalWrite(IN4,LOW); //Left Motor forword Pin
}

void Stop()
{
  digitalWrite(IN1,LOW);  //Right Motor forword Pin
  digitalWrite(IN2,LOW); //Right Motor backword Pin
  digitalWrite(IN3,LOW); //Left Motor backword Pin
  digitalWrite(IN4,LOW); //Left Motor forword Pin
}
