#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht.h>
dht DHT;


LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup(){
  delay(2000);
  Serial.begin(9600);
  pinMode(A0, INPUT); // gas Sensor
  pinMode(A1, INPUT); // soil Moisture
  pinMode(4, OUTPUT); // relay
  pinMode(3, OUTPUT); // buzzer

  lcd.begin();
  lcd.backlight();
}

void loop()
{
  digitalWrite(4, HIGH);
  int temp = (int)readTemp();
  int humidity = (int)readHumidity(); 
  int soilMoisture = readSoilMoisture();

  int gasValue = readgasValue();
  LcdPrint(temp, humidity, gasValue, soilMoisture);

 if(gasValue > 400 || temp > 36 || humidity < 60){
   BuzzerPlay();
 }
  if(soilMoisture>900){
   waterIrrigation();
  }
}

int readTemp(){
  int readData = DHT.read11(2);
	float t = DHT.temperature;
  delay(2000);
  Serial.println(t);
  return t;
}

int readHumidity(){
  int readData = DHT.read11(2);
	float h = DHT.humidity;
  delay(2000);
  Serial.println(h);
  return h;
}

int readSoilMoisture(){
  Serial.println(analogRead(1));
  return analogRead(1);
}

void waterIrrigation(){
 digitalWrite(4, LOW);
 delay(5000);
 digitalWrite(4, HIGH);
}

float readgasValue(){
  Serial.println(analogRead(0));
  return analogRead(0);
}

void BuzzerPlay(){
  digitalWrite(3 ,HIGH);
  delay(2000);
  digitalWrite(3 ,LOW);
}

void LcdPrint(int Temprature , int Humidity , int gasValue , int soilMoisture){
    delay(2000);
    lcd.print("Temperature : ");
    lcd.setCursor(13, 0);
    lcd.print(Temprature);
    delay(2000);
    lcd.clear();
    lcd.print("Humidity : ");
    lcd.setCursor(10, 0);
    lcd.print(Humidity);
    delay(2000);
    lcd.clear();
    lcd.println("GasValue :");
    lcd.setCursor(10, 0);
    lcd.print(gasValue);
    delay(2000);
    lcd.clear();
    lcd.println("Moisture : ");
    lcd.setCursor(10, 0);
    lcd.print(soilMoisture);
    delay(2000);
    lcd.clear();
}
