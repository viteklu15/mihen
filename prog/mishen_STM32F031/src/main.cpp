
#include "mbed.h"
AnalogIn sensor(PB_1);
DigitalOut led(PA_9);       // выход для мишеней
Serial uart_1(USBTX, USBRX); // tx, rx
int comand = 0;              // переменная для получения команды
bool flag_on = false;

int main()
{
    uart_1.printf("uart on");
    while (1)
    {

        if (uart_1.readable()) // ждет есть ли команды с uart
        {
            comand = uart_1.getc(); // передаем команду в переменную 
            if (comand == 50) // по какой команде будет включатся мишень 
            {
                flag_on = true;
                uart_1.printf(" команда получена  %d )\r\n", comand);
            }
        }
        if (flag_on) // для включение светодиодов и просмотра датчика удара
        { 
            led = 1;
            if (sensor.read_u16() > 2000)
            {
                led = 0;
                flag_on = false;
                //uart_1.printf("удар  (%d)", sensor.read_u16());
                uart_1.printf("%d\r\n", 1);
            }
        }
    }
}
