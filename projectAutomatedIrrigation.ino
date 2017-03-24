#include <LiquidCrystal.h>
#include <dht.h>
#define DHT11_PIN 9
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
dht DHT;

char dry[] = "SOIL DRY        ";
char damp[] = "SOIL DAMP      ";
char wet[] = "SOIL WET        ";
char wateringAlert[] = "WATERING IN:";
char currentlyWatering[] = "CURRENTLY";
char currentlyWateringCont[] = "WATERING: ";
int wateringCounter = 5;
int timeCounter = 30;
void setup() {
  //Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  //Serial.println(sensorValue);

  int chk = DHT.read11(DHT11_PIN);
  lcd.begin(16,2); 
  lcd.print("Temp: ");
  lcd.print(Fahrenheit(DHT.temperature));
  lcd.print((char)223);
  lcd.print("F");
  lcd.setCursor(0,2);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  delay(2000);

  lcd.begin(16, 2);
  lcd.print("GARDEN CONDITION");
  lcd.setCursor(0,2);
  if (sensorValue > 300)
  {
    lcd.print(dry);
    delay(3000);
    Water();
    return;
  }
  if (sensorValue > 230)
  {
    lcd.print(damp);
    delay(3000);
  }
  if (sensorValue < 230)
  {
    lcd.print(wet);
    delay(3000);
  }
  lcd.clear();
}

void Water() {
  while (wateringCounter > 0) 
  {
    lcd.begin(16, 2);
    lcd.print(wateringAlert);
    lcd.setCursor(0, 2);
    lcd.print(wateringCounter);
    delay(1000);
    wateringCounter--;
  }
  lcd.begin(16, 2);
  lcd.print(currentlyWatering);
  lcd.setCursor(0, 2);
  lcd.print(currentlyWateringCont);
  for (int i = 0; i < 30; i++)
  {
    lcd.setCursor(10, 2);
    lcd.print(timeCounter);
    timeCounter--;
    delay(1000);
    
    //WATER PLANTS HERE
    
  }
  wateringCounter = 5;
  timeCounter = 30;
  lcd.clear();
}

double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

