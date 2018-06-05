void gsmcall()
{
  Serial.println("Calling through GSM Modem");
//set the data rate for the SoftwareSerial port
  delay(2000);
  mySerial.println("ATD81290255XX;"); // ATD81290255XX; -- watch out here for semicolon at the end!!
  Serial.println("Called ATD81290255XX");
  if (mySerial.available())
  Serial.write(mySerial.read());
}
