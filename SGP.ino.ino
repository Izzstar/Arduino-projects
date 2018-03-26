/*PROJECT MADE BY SHAH BHAVYA AND KAIVAN SHAH 
  TOPIC: HOME SECURITY ALARAM SYSTEM 
  REQUIREMENTS: ARUDINO UNO, GSM MODULE, SIM-CARD, PIR SENSOR, BUZZER, LEDs AND A LITTLE BIT OF INTEREST ;) */
const int buzzer = 4; // buzzer to arduino pin 4
int ledpin = 13; // LED to pin 13
int sensor = 2; // SENSOR to pin 2
int calibrationTime = 10; // time taken by sensor to start
long unsigned int lowIn;   //MILLIS()
long unsigned int pause = 1000;  //PAUSE 
boolean lockLow = true; //TREATED AS FLAG VALUE
boolean takeLowTime; //TREATED AS FLAG VALUE
void setup(){
  Serial.begin(9600); //(baudrate set to 9600) speed
  pinMode(buzzer, OUTPUT); //(pin, mode)
  pinMode(ledpin, OUTPUT);
  pinMode(sensor, INPUT);
  digitalWrite(sensor, LOW); //initially we want our sensor to have no motion
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
}
void loop(){
  if(digitalRead(sensor)== HIGH){
    Serial.println("ATD8866114346;"); // ATD COMMAND TO GENERATE CALL 
    Serial.println("Calling  "); // prints response over serial port
    digitalWrite(ledpin, HIGH); //(pin, mode)
    tone(buzzer, 1000); //(pin,frequency)
    delay(10000); // for this much time buzzer LED will be on
    if(lockLow){  
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;            
         Serial.println("-----");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);   //millis() returns unsigned long 
         Serial.println(" sec"); 
        delay(50);
         } 
         takeLowTime = true; 
  }  
  if(digitalRead(sensor)== LOW){
    digitalWrite(ledpin, LOW); 
    noTone(buzzer);
  if(takeLowTime){
    lowIn = millis();
    takeLowTime = false; 
  }
  //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
  
    }
  }
}
