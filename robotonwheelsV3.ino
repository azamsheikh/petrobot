#include <IRremote.h>

#include <Servo.h>

Servo neckservo; 
Servo faceservo;
int RECV_PIN = 7;         
IRrecv receiver(RECV_PIN);  
decode_results results;    
 
int trigPin = 11;  
int echoPin = 12;   
long duration, cm, inches;
int panic = 0; 
int eyeOne = 6;
int eyeTwo = 8;



void setup() {
 
  Serial.begin (9600);
  
  neckservo.attach(9);  // attaches the servo on pin 9 to the servo object
  faceservo.attach(10);  // attaches the servo on pin 10 to the servo object


  neckservo.write(90);
  faceservo.write(90);
  
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); 

  
  pinMode(eyeOne, OUTPUT);  //eye  ONE 
  pinMode(eyeTwo, OUTPUT);  //eye  tWO

  

 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

for(int i =0;i<10;i++)
{
measureDistanceincm();
}







  
}
 
void loop() {
  digitalWrite(eyeOne, HIGH);
  digitalWrite(eyeTwo, HIGH);

   int PIRsensorValue = analogRead(A0);
   
    int randNumber = random(1, 2);
   if(randNumber == 1)
   {
      ////////////////running pir sensor procedure/////////////////

obstacleavoiding();
     

   }
   
   else{
    obstacleavoiding();
   }




  
  
     }    ////////////void loop ends here//////////




void obstacleavoiding(){


top:
  

 cm = measureDistanceincm();
 inches = measureDistanceininches();
  Serial.println(cm);

   if(panic >= 3){
    panicprocedure();
    panic = 0;
    inches =100; }
    else{}

  
 
  if(cm <= 50  || cm >= 1000){

   



    
  panic++;
  wait(1000);
  backward(200);
   wait(1000);
    for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
   
   faceservo.write(pos);   
   
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  
  wait(500);
  left(200);
  wait(500);
  int leftdistance = measureDistanceincm();
  if(leftdistance >=30){
    goto top;
  }
   wait(500);
   right(200);
   wait(500);
   right(200);
   wait(500);
   int rightdistance = measureDistanceincm();
   if(rightdistance >=30){
   goto top;
  }
   wait(500);
   left(200);
   wait(1000);
   if(rightdistance > leftdistance && rightdistance > 50){
   right(200);
   wait(500);
   }
   else if(rightdistance < leftdistance && leftdistance > 50){
   left(200);
   wait(500);
   }
   else{
   backward(200);
   }
   wait(500);
   }
   else{
    faceservo.write(90);  
   forward();
   }

  
}
















     
int right(int x){
     analogWrite(2, 0); 
     analogWrite(3, 250);                        //right
     analogWrite(4, 250); 
     analogWrite(5, 0);
     delay(x);
}
int left(int x){
     analogWrite(2, 250); 
     analogWrite(3, 0);                        //right
     analogWrite(4, 0); 
     analogWrite(5, 250);
     delay(x);
}

void forward(){

  analogWrite(2, 250); 
    analogWrite(3, 0);                        //forward
    analogWrite(4, 250); 
     analogWrite(5, 0);
      
    }


int backward(int x){
     analogWrite(2, 0); 
    analogWrite(3, 250);                        //backward
    analogWrite(4, 0); 
     analogWrite(5, 250);
     delay(x);
  
}


int wait(int x){
     digitalWrite(2, LOW); 
     digitalWrite(3, LOW);                        //stop
     digitalWrite(4, LOW); 
     digitalWrite(5, LOW); 
     delay(x);
  
}








void panicprocedure(){

for(int i=0;i<5;i++){
digitalWrite(eyeOne, LOW);
digitalWrite(eyeTwo, LOW);
delay(300);
digitalWrite(eyeOne, HIGH);
digitalWrite(eyeTwo, HIGH);
delay(300);
}


int randNumber = random(1, 2);
if(randNumber == 1)
{
  right(300);
}
else if(randNumber == 2)
{
  left(300);
}

wait(3000);


}

int measureDistanceincm(){
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;    
  inches = (duration/2) / 74;  
  Serial.println(cm);
  delay(100);
  return cm;
}


int measureDistanceininches(){
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;    
  inches = (duration/2) / 74;  
  Serial.println(cm);
  delay(100);
  return inches;
}







void fixer(){



  
}
