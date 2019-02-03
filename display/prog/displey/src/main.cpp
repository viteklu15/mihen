#include "mbed.h"
EventQueue eventQueue(/* event count */ 50 * EVENTS_EVENT_SIZE);
DigitalOut datapin(PA_1);
DigitalOut latchpin(PC_13);
DigitalOut clockpin(PA_2);
int milisek, sec, sec2, minut, comand = 0;
int d_1, d_2, d_3, d_4, tohki = 10;
bool flag_start, flag_start2 = false; // флад для запуска игры
Serial uart_1(USBTX, USBRX);          // tx, rx
Serial JDY_40(PB_10, PB_11);          // tx, rx

bool in_out_JDY_40(int canal)
{
  JDY_40.printf("%d\r\n", canal); // отправляем всем команду для включения 1
  int can = 0;
  bool can_ok = false;

  for (size_t i = 0; i < 5; i++)
  {
    for (int i = 0; i < 10000; i++)
    {
      if (JDY_40.readable())
      {

        can = JDY_40.getc();
        if (can == 48 + canal)
        {
          can_ok = true;
        }
      }
    }
    if (can_ok)
    {
      break;
    }
    else
    {
      JDY_40.printf("%d\r\n", canal); // передаем еще раз
    }
  }

  return can_ok;
}

void displey(int D1, int D2, int D3, int D4)
{
  uart_1.printf(" tablo %d%d%d%d \r\n", D1, D2, D3, D4);
  const int number[12][8] = {
      {0, 1, 1, 1, 1, 1, 1}, // 0
      {0, 0, 0, 0, 1, 1, 0}, // 1
      {1, 0, 1, 1, 0, 1, 1}, // 2
      {1, 0, 0, 1, 1, 1, 1}, // 3
      {1, 1, 0, 0, 1, 1, 0}, // 4
      {1, 1, 0, 1, 1, 0, 1}, // 5
      {1, 1, 1, 1, 1, 0, 0}, // 6
      {0, 0, 0, 0, 1, 1, 1}, // 7
      {1, 1, 1, 1, 1, 1, 1}, // 8
      {1, 1, 0, 0, 1, 1, 1}, // 9
      {0, 0, 0, 0, 1, 0, 0}, // - 10
      {0, 0, 0, 0, 0, 0, 0}  //   11 что бы было пусто

  };

  latchpin = 0;

  for (int i = 0; i <= 7; i++)
  {
    datapin = number[D1][i];
    clockpin = 1;
    clockpin = 0;
  }

  for (int i = 0; i <= 7; i++)
  {
    datapin = number[D2][i];
    clockpin = 1;
    clockpin = 0;
  }
  for (int i = 0; i <= 7; i++)
  {
    datapin = number[D3][i];
    clockpin = 1;
    clockpin = 0;
  }
  for (int i = 0; i <= 7; i++)
  {
    datapin = number[D4][i];
    clockpin = 1;
    clockpin = 0;
  }
  latchpin = 1;
}

void start_displey()
{
  if (flag_start and sec < 5)
  {
    sec++;
    displey(11, 10, sec, 10);
    uart_1.printf(" sec %d \r\n", sec);
    if (sec == 5)
    {
      flag_start2 = true; // запускаем отщет времени
      flag_start = false;
    }
  }
}

void taim_out() // щитаем время
{
  if (flag_start2)
  {
    milisek++;
    sec = milisek / 10;
    sec2 = sec % 60;
    minut = sec / 60;
    d_4 = milisek % 10;
    d_3 = sec % 10;
    d_2 = sec2 / 10;
    d_1 = minut % 10;
    displey(d_1, d_2, d_3, d_4);
    if (sec > 598) {
      flag_start2 = false;
    }
    
  }
}

void comand_READ() // проверяем какая команда пришла
{
  if (uart_1.readable()) // ждет есть ли команды с uart
  {
    comand = uart_1.getc(); // передаем команду в переменную  от блютус
    if (comand == 115)      // по какой команде будет включатся мишень "s"
    {
      sec = 0;
      milisek = 0;
      flag_start2= false;
      uart_1.printf(" команда получена  %d )\r\n", comand);

      if (in_out_JDY_40(1) and in_out_JDY_40(2) and in_out_JDY_40(3) and in_out_JDY_40(4) and in_out_JDY_40(5))
      {
        uart_1.printf(" vse_mish ok\r\n");
        flag_start = true; // запуск отщета на старт
      }
      else
      {
        uart_1.printf(" ne vse miheni otvetili\r\n");
      }
    }
  }
}

int main()
{
  eventQueue.call_every(100, taim_out);       // run every 100 ms
  eventQueue.call_every(1000, start_displey); // run every 100 ms
  eventQueue.call_every(10, comand_READ);     // run every 10 ms
  eventQueue.dispatch_forever();
  return 0;
}