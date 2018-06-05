#include <Wire.h>         
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial serialgps(2, 3); //--> GPS
SoftwareSerial mySerial(10, 11); // RX, TX --> GSM
 
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

// Sensor and pins variables
int pulsePin = 0;
int buzzer=5;
int call=6;
int location=7;

volatile int BPM;    
volatile int Signal;
volatile int IBI = 600;
volatile boolean Pulse = false;
volatile boolean QS = false;

void setup(){
  Serial.begin(9600);
  serialgps.begin(9600);
  mySerial.begin(9600);
  Serial.println("Heart Beat Monitoring");
  lcd.begin(16,2);              
  lcd.backlight(); 
  lcd.setCursor(0,0);         
  delay(1000);
  lcd.write("Heart Beat ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.write("Monitering");
  delay(1000);

  // Sets up to read Pulse Sensor signal every 2mS
  interruptSetup();

  pinMode(buzzer, OUTPUT);
  pinMode(call, INPUT);
  pinMode(location, INPUT);
  digitalWrite(call, HIGH);
  digitalWrite(location, HIGH);
  delay(1000);
}

void loop(){
  
  // If heart beat is found
  if (QS == true) {
    // Print heart rate      
      lcd.clear();
      lcd.write("Heart Beat Rate:");
      lcd.setCursor(0,1);
      lcd.print(BPM);
      Serial.print("Heart Beat Rate: ");            
      Serial.println(BPM);
  
    if(BPM>120)
    {
      for(int i=0; i<3;i++)
      {
      digitalWrite(buzzer,HIGH);
      delay(250);
      digitalWrite(buzzer,LOW);
      delay(250);
      }
      
      if(!(digitalRead(call)))
      {
      Serial.println("Calling...");
      lcd.clear();
      lcd.write("Calling...");
      gsmcall();
      delay(10000);
      }
      
      if(!digitalRead(location))
      {
      Serial.println("Location Tracking...");
      lcd.clear();
      lcd.write("Location Tracking...");
      gpslocation();
      delay(10000);
      }
     }
    // Reset the Quantified Self flag for next time      
    QS = false;                       
   }
    delay(6000);
}