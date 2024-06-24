#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


const unsigned int TEMP_SENSOR_PIN = 0;
const float SUPPLY_VOLTAGE = 5.0;
const unsigned int BAUD_RATE = 9600;
int LED = 11;
int FAN = 10;
float number; // Declare the variable as a global variable
int hour;
int minute;
int second;
int hourw;
int minutew;
int secondw;
int counter = 0;
double times[7];
void setTime(int h, int m, int s);
void increaseMin();
void increaseHr();
void checkTime();

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED, OUTPUT);
  pinMode(FAN, OUTPUT);
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight
  lcd.setCursor(0,0);
  lcd.begin(16, 2);
  setTime(6, 22, 50);
  hourw = 6;
  minutew = 23;
  secondw = 0;
  

}

void loop() {
  number = get_temperature(); // Assign the temperature value from the function to the global variable
  Serial.print(number);
  Serial.println(" C");
  Serial.print("\t");
  lcd.print(number);
  lcd.print(" C");
  checkTime();
  increaseHr();
  increaseMin();
  Serial.print(hour);
  Serial.print("\t");
  Serial.print(minute);
  Serial.print("\t");
  Serial.print(second);
  Serial.print("\t");
  Serial.print(times[0]);
  Serial.print("\t");  
  delay(1000);
  lcd.clear();

  if (number >= 32) {
    digitalWrite(LED, HIGH);
    digitalWrite(FAN, HIGH);
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(FAN, LOW);
  }
}

const float get_temperature() {
  const int sensor_voltage = analogRead(TEMP_SENSOR_PIN);
  const float voltage = sensor_voltage * SUPPLY_VOLTAGE / 1024;
  const float temperature = (voltage * 1000 - 500) / 10;
  return temperature; // Return the temperature value instead of "number"
}
void setTime(int h, int m, int s)
{
  hour = h;
  minute = m;
  second = s;
}
void increaseMin()
{
  if(second >= 59)
  {
    minute++;
    second = 0;
  }
  else
  {
    second++;
  }
}
void increaseHr()
{
  if(minute >= 59)
  {
    if(hour >= 23)
    {
    hour = 0;
    minute = 0;
    }
  
  else
  {
    hour++;
  }
  }
}

void checkTime()
{
  if(hour == hourw && minute == minutew && second == secondw)
  {
    times[counter] = number;
    if(counter == 6)
    {
      counter =0;
    }
    else
    {
       counter++;
    }

  }
}


