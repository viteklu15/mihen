#include <Arduino.h>

const int wakeUpPin = 2;

int skolko_rabotat = 5; //в секундах
int kol_sek = 0;        //в секундах

int analog_sens_ciramik = 3; //pc3
int val_sens_ciramik, bat = 0;
int analog_bat = 2; //pc2
int out_led = 13;   // выход для светодиода
int bit_0 = 7;
int bit_1 = 8;
int bit_2 = 9;
String M_bit = "";
String Z_bit = "";

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
        if (riad_serial == M_bit + "1\n")
        {
          on_off = true;
          Serial.print(M_bit + 1 + "\n");
        }
        else
        {
          on_off = false;
          Serial.print(M_bit + 0 + "\n");
        }

        riad_serial = ""; // обнуляем переменную стринг 
        bat = analogRead(analog_bat);
        bat = map(bat, 0, 1023, 0, 100);
        Serial.print(Z_bit);
        Serial.print(bat);
        Serial.print("\n");
      }
    }
    if (on_off)
    {
      digitalWrite(out_led, HIGH);
      val_sens_ciramik = analogRead(analog_sens_ciramik);
      if (val_sens_ciramik > 300)
      {
        Serial.print(M_bit + val_sens_ciramik + "\n"); // передаем данные сенсора
      }
    }
    else
    {
      digitalWrite(out_led, LOW);
    }
  }
  if (((millis() - tamer_sec) > 1000) & !on_off)
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
  pinMode(out_led, OUTPUT);
  pinMode(wakeUpPin, INPUT);
  pinMode(bit_0, INPUT_PULLUP);
  pinMode(bit_1, INPUT_PULLUP);
  pinMode(bit_2, INPUT_PULLUP);
  Serial.begin(9600);
  detachInterrupt(0);

  if ((digitalRead(bit_2) == 0) & (digitalRead(bit_1) == 1) & (digitalRead(bit_0) == 0))
  {
    M_bit = "M5";
    Z_bit = "Z5";
  }
  else if ((digitalRead(bit_2) == 0) & (digitalRead(bit_1) == 1) & (digitalRead(bit_0) == 1))
  {
    M_bit = "M4";
    Z_bit = "Z4";
  }
  else if ((digitalRead(bit_2) == 1) & (digitalRead(bit_1) == 0) & (digitalRead(bit_0) == 0))
  {
    M_bit = "M3";
    Z_bit = "Z3";
  }
  else if ((digitalRead(bit_2) == 1) & (digitalRead(bit_1) == 0) & (digitalRead(bit_0) == 1))
  {
    M_bit = "M2";
    Z_bit = "Z2";
  }
  else if ((digitalRead(bit_2) == 1) & (digitalRead(bit_1) == 1) & (digitalRead(bit_0) == 1))
  {
    M_bit = "M1";
    Z_bit = "Z1";
  }
  Serial.print(M_bit);
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