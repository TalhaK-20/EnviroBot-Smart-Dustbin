
#include <Servo.h>   //servo library
Servo servo;

int trigPin = 5;     //This pin is used for the motion sensor to transmit the sound pulses (input)  
int echoPin = 6;     //This pin is used for the motion sensor to catch the sound pulses when hit with the object (output)
int servoPin = 7;    
long duration, dist, average;   
long aver[3];       //array for average


  void setup(){       
    Serial.begin(9600);
    servo.attach(servoPin);   
    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT);  
    servo.write(0);          //Close cap on power on
    delay(100);
    servo.detach(); 
  } 


  void measure(){  
    digitalWrite(10,HIGH);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    dist = (duration/2) / 29.1;          //Obtain distance  
  }


  void loop() { 
    for(int i=0;i<=2;i++){   //Average distance
      measure();               
      aver[i]=dist;            
      delay(200);            //Delay between measurements
    }

    dist=(aver[0]+aver[1]+aver[2])/3;    

    if(dist<50){
     servo.attach(servoPin);
     servo.write(0);    //Motor bar is at normal position (starting position 0 degree) 
     delay(3000);       //After 3 seconds   
     servo.write(90);   //Move the motor bar to 90 degree 
    }

    Serial.print(dist);

  }
