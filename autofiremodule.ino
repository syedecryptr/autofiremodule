
float threshold=32;
int outputpin=0;
int buzzer = 7;
void setup()
{
   Serial.begin(9600);
   pinMode(buzzer, OUTPUT);
}
void loop()
{
  float temp = check_temp();
  
  if (temp > threshold)
  {
    send_sms();
    while(1)
      {
        float temp = check_temp();
        if(temp > threshold && temp < threshold + 2)
        {
          digitalWrite(buzzer, HIGH);
          delay (1000);
          digitalWrite(buzzer, LOW);
          delay (1500);
        }
        else if(temp >= threshold + 2 && temp < threshold + 3)
        {
          digitalWrite(buzzer, HIGH);
          delay (500);
          digitalWrite(buzzer, LOW);
          delay (500);
        }
        else if(temp >= threshold + 3)
        {
          digitalWrite(buzzer, HIGH);
          delay (100);
          digitalWrite(buzzer, LOW);
          delay (100);
        }
        else
        {
          break;
        } 
      }
   }
}

float check_temp()
{
  int rawvoltage=analogRead(outputpin);
  float millivolts= (rawvoltage/1024.0) * 5000;
  float celsius= millivolts/10;
  Serial.print(celsius);
  Serial.print(" degrees Celsius, ");
  Serial.println(threshold);
  delay(1000);
  return celsius;
}

void send_sms()
{
    Serial.print("\r");
    delay(1000);
    Serial.print("AT+CMGF=1\r");
    delay(1000);
    Serial.print("AT+CMGS=\"+919649383855\"\r");
    delay(1000);
    Serial.print("EMERGENCY!! Suspected fire in the house \r");
    delay(1000);
    Serial.write(0x1A);
    delay(1000);
}