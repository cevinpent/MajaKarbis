#include <Servo.h>


int fan = 26;
int reelSwitch = 2; // magnetic senso rpin
int switchState; // variable to store reel switch value
const int sensePin = A0;  //This is the Arduino Pin that will read the sensor output
int sensorInput=1;    //The variable we will use to store the sensor input
float temp,voltage;
const int pResistor = A2;
int servopin = 6;
int potentpin = A1;
int angle = 0;
Servo servo1;
int ledinside = 8;
#define redPin 9
#define greenPin 10
#define bluePin 11
const int buzzer = 12;
int buttonpin = 4;
int val;
int value;
long last;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Start the Serial Port at 9600 baud (default)
  pinMode(redPin,OUTPUT);
  pinMode (reelSwitch, INPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(pResistor, INPUT);
  pinMode(buzzer,OUTPUT);

  pinMode(buttonpin, INPUT);
  pinMode(ledinside,OUTPUT);
  pinMode(servopin, OUTPUT);
  pinMode(potentpin, INPUT);
  servo1.attach(servopin);  
 last=millis();
}
void loop() {
  
  // put your main code here, to run repeatedly: 
  //if(last+5000<millis()){
    //last=millis();
    sensorInput = analogRead(sensePin);    //read the analog sensor and store it
    voltage = (sensorInput/1024.0) * 5.0;       //find percentage of input reading
    temp = (voltage - .5) * 100;
    delay(1000);
  //}
  
  switchState = digitalRead(reelSwitch); // read the value of digital interface 2 and assign it to switchState
  if (switchState == HIGH) // when the magnetic sensor detect a signal, LED is flashing
  {
    tone(buzzer, 1440);
    delay(1000);
  }
  else 
  {
    digitalWrite(buzzer, LOW);
  }
  
  angle = analogRead(potentpin);
  angle = map(angle, 0, 1023, 0, 160);
  servo1.write(angle);
  delay(15);
  
  value = analogRead(pResistor);
  if (value > 400){
    digitalWrite(ledinside, HIGH);  //Turn led off
  }
  else{
    digitalWrite(ledinside, LOW); //Turn led on
  }
  
  //tone(buzzer, 200); // Send 1KHz sound signal...
  val = digitalRead(buttonpin);
  if (val == LOW) {
    tone(buzzer, 660);
    delay(400);
    tone(buzzer, 550);
    delay(500);
    tone(buzzer, 440);
    delay(600);
    noTone(buzzer);
    
  }
  else {
    noTone(buzzer);
  }
  
                                    
  

  if(temp < 25 && temp > 18)
  {
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, LOW); 
     
    digitalWrite(fan, LOW);
    
  }
  else if (temp > 25)
  {
    
    digitalWrite(fan, HIGH);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
  else if (temp < 18)
  {
    digitalWrite(bluePin, HIGH);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(fan, LOW);
  }
  

  //Convert to degrees 
 Serial.print("Current Temperature: ");
 Serial.println(temp);
 
 Serial.print("Current pResistor: ");
 Serial.println(pResistor);
 
 Serial.print("Current angle  : ");
 Serial.println(angle);
 
 Serial.print("Current sen  : ");
 Serial.println(reelSwitch);
 
}
