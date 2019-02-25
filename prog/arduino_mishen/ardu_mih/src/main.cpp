#include <Arduino.h>

const int wakeUpPin = 2;

bool flag_prer = false;
int skolko_rabotat = 5; //в секундах
int kol_sek = 0;        //в секундах

bool on_off = false;
String riad_serial = "";

long tamer_sec = 0;

void loop2()
{
  if (kol_sek < skolko_rabotat - 1)
  {
    while (Serial.available()) // проверяем команды которые пришли с com порта
    {
      char inChar = Serial.read();
      riad_serial += inChar;
      if (inChar == '\n')
      {       
        if (riad_serial.indexOf("M1") != -1)
        {
          String Voltage = riad_serial.substring(2);
          Voltage.trim();
          int on_M = Voltage.toInt();
          if (on_M == 1)
          {
            on_off = true;
            Serial.print("M11\n ");
          }
          else
          {
            on_off = false;
            //Serial.println("false");
            Serial.print("M10\n ");
          }
        }
        riad_serial = "";
      }
    }
  }
  if ((millis() - tamer_sec) > 1000)
  {
    tamer_sec = millis();
    kol_sek++;
  }
}

void wakeUp()
{
  kol_sek = 0;
}

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(wakeUpPin, INPUT);
  Serial.begin(9600);
  detachInterrupt(0);
}

void loop()
{
  attachInterrupt(0, wakeUp, CHANGE);
  if (kol_sek < skolko_rabotat)
  {
    loop2();
  }
  else
  {
    Serial.print("Sleep \n ");
  // Serial.println(10, HEX);
    delay(1000);
    //sleepMode(SLEEP_POWER_DOWN);
    //sleep(); // Go to sleep
  }
}