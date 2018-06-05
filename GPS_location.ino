int year;
byte month, day, hour, minute, second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;
float latitude, longitude;
int c;

void gpslocation()
{
Serial.println("==========================");
Serial.println("GPS");
Serial.println("===========================");

while(serialgps.available()) 
{
c = serialgps.read(); 
if(gps.encode(c)) 
{
gps.f_get_position(&latitude, &longitude);
Serial.print("Lat/Long: "); 
Serial.print(latitude,6); 
Serial.print(","); 
Serial.println(longitude,6); 
Serial.println();
gps.stats(&chars, &sentences, &failed_checksum);
  mySerial.println("AT");
  delay(1000);
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"81290255XX\""); //CHANGE TO DESTINATION NUMBER
  delay(1000);
  mySerial.print("Latitude/Longitude:");
  mySerial.print(latitude,6);
  mySerial.print(",");
  mySerial.print(longitude,6);
  mySerial.write(26);
  delay(10000);
}
}
}