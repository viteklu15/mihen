#include <Arduino.h>

#include <EEPROM.h>
#include <ESP8266WiFi.h>
//#include <PubSubClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
WiFiClient wclient;

byte ip_1[] = {192, 168, 1, 2};
//PubSubClient client(wclient);

String str = "";
boolean conf = false;
String html_header = "<html>\
 <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\
 <head>\
   <title>Wi-Fi Termostat</title>\
   <style>\
     body { background-color: #ffffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\
   </style>\
 </head>";

const char *host = "OTA";
String ssid = "ELTEX-DB48";
String pass = "GP21116934";
//IPAddress ip(192, 168, 1, 1); //статический IP
//IPAddress gateway(192, 168, 1, 1);
//IPAddress subnet(255, 255, 255, 0);
const char *ssid_ap = "IoT";      //имя точки доступа
const char *pass_ap = "12345678"; //пароль точки доступа

byte count_con = 0; // колличество подключений к wi-fi AP
#define BUFFER_SIZE 100
String bufer;
long evTimeconn;

boolean flagconn = 1; // флаг для однакратного подключения к wi fi
uint8_t PowerPin = 2;

bool PowerOn, PowerOn1, PowerOn2, PowerOn3, PowerOn4, PowerOn5 = false;
String riad_serial = "";
String buf = "";
int mih1_sens, mih2_sens, mih3_sens, mih4_sens, mih5_sens = 0;
int zaryad_1, zaryad_2, zaryad_3, zaryad_4, zaryad_5;
int milisek, sec, sec1, sec2, minut, comand = 0;
int d_1, d_2, d_3, d_4, tohki = 10;
long tamer_5sec, tamer_10mil, tamer_budilnika, tamer_bud, tamer_50mil;
int max_udar = 500;
bool m1, m2, m3, m4, m5, flag_delay = false;
void proveryaem_mish()
{
  if (mih1_sens > max_udar)
  {
    PowerOn1 = false;
    mih1_sens = 0;
  }
  if (mih2_sens > max_udar)
  {
    PowerOn2 = false;
    mih2_sens = 0;
  }
  if (mih3_sens > max_udar)
  {
    PowerOn3 = false;
    mih3_sens = 0;
  }
  if (mih4_sens > max_udar)
  {
    PowerOn4 = false;
    mih4_sens = 0;
  }
  if (mih5_sens > max_udar)
  {
    PowerOn5 = false;
    mih5_sens = 0;
  }
}
void on_off_mish_ser()
{
  if (tamer_bud > 9){
  if (m1)
  {
    PowerOn1 = true;
  }
  else
  {
    PowerOn1 = false;
  }
  if (m2)
  {
    PowerOn2 = true;
  }
  else
  {
    PowerOn2 = false;
  }
  if (m3)
  {
    PowerOn3 = true;
  }
  else
  {
    PowerOn3 = false;
  }
  if (m4)
  {
    PowerOn4 = true;
  }
  else
  {
    PowerOn4 = false;
  }
  if (m5)
  {
    PowerOn5 = true;
  }
  else
  {
    PowerOn5 = false;
  }
  }
}
void zapusk_tamera_10mil()
{
  if (sec == 5)
  {
    if (millis() - tamer_10mil > 100)
    {
      if (PowerOn)
      {
        tamer_10mil = millis();
        milisek++;
        sec1 = milisek / 10;
        sec2 = sec1 % 60;
        minut = sec1 / 60;
        d_4 = milisek % 10;
        d_3 = sec1 % 10;
        d_2 = sec2 / 10;
        d_1 = minut % 10;
        // displey(d_1, d_2, d_3, d_4);
        if (sec1 > 598)
        {
          PowerOn = false;
        }
        // Serial.print(d_1);
        //Serial.print(d_2);
        // Serial.print(d_3);
        // Serial.println(d_4);
      }
    }
  }
  else
  {
    milisek = 0;
  }
}
void deley_50milsec(){
  if (((millis() - tamer_50mil) > 100))
  {
    tamer_50mil = millis();
    flag_delay = !flag_delay;

  }
  }
void on_off_posle_servera()
{

  if (tamer_bud < 10)
  {
    if (PowerOn1)
    { deley_50milsec();
      if (!m1 && flag_delay )
      {
        flag_delay = false;
        Serial.print("M11\n");        
      }
    }
    else
    {  deley_50milsec();
      if (m1 && flag_delay)
      { 
        flag_delay = false;
        Serial.print("M10\n");       
      }
    }

    if (PowerOn2)
    { deley_50milsec();
      if (!m2 && flag_delay)
      {
        flag_delay = false;
        Serial.print("M21\n");        
      }
    }
    else
    {  deley_50milsec();
      if (m2 && flag_delay)
      {
        flag_delay = false;
        Serial.print("M20\n");        
      }
    }
    if (PowerOn3)
    { deley_50milsec();
      if (!m3 && flag_delay)
      {
        flag_delay = false;
        Serial.print("M31\n");        
      }
    }
    else
    {deley_50milsec();
      if (m3 && flag_delay)
      { flag_delay = false;
        Serial.print("M30\n");        
      }
    }
    if (PowerOn4)
    {deley_50milsec();
      if (!m4 && flag_delay)
      { 
        flag_delay = false;
        Serial.print("M41\n");        
      }
    }
    else
    {  deley_50milsec();
      if (m4 && flag_delay)
      { flag_delay = false;
        Serial.print("M40\n");        
      }
    }
    if (PowerOn5)
    {deley_50milsec();
      if (!m5 && flag_delay)
      { flag_delay = false;
        Serial.print("M51\n");        
      }
    }
    else
    {deley_50milsec();
      if (m5 && flag_delay)
      {flag_delay = false;
        Serial.print("M50\n");        
      }
    }
  }
  if (((millis() - tamer_budilnika) > 1000))
  {
    tamer_budilnika = millis();
    if (tamer_bud < 10)
    {
      tamer_bud++;
    }
    else
    {
      on_off_mish_ser();
      tamer_bud = 1;
    }
  }
}
void tamin_5sec()
{
  if (PowerOn)
  {
    if (((millis() - tamer_5sec) > 1000) & (sec < 5))
    {
      tamer_5sec = millis();
      sec++;
      if (sec == 1)
      {
        tamer_bud = 1;
        PowerOn1 = true;
        PowerOn2 = true;
        PowerOn3 = true;
        PowerOn4 = true;
        PowerOn5 = true;       
      }
      Serial.println(sec);  
    }  
  }
  else
  {
    if (sec == 5)
    {
      PowerOn1 = false;
      PowerOn2 = false;
      PowerOn3 = false;
      PowerOn4 = false;
      PowerOn5 = false;
      sec = 0;
    }
  }
}

void HTTP_handleRoot(void)
{

  bool stat, stat1, stat2, stat3, stat4, stat5 = false;
  if (server.hasArg("stat"))
  {
    if (strncmp(server.arg("stat").c_str(), "1", 1) == 0)
      stat = true;
  }
  else
  {
    stat = PowerOn;
  }
  if (server.hasArg("stat1"))
  {
    if (strncmp(server.arg("stat1").c_str(), "1", 1) == 0)
      stat1 = true;
  }
  else
  {
    stat1 = PowerOn1;
  }

  if (server.hasArg("stat2"))
  {
    if (strncmp(server.arg("stat2").c_str(), "1", 1) == 0)
      stat2 = true;
  }
  else
  {
    stat2 = PowerOn2;
  }
  if (server.hasArg("stat3"))
  {
    if (strncmp(server.arg("stat3").c_str(), "1", 1) == 0)
      stat3 = true;
  }
  else
  {
    stat3 = PowerOn3;
  }
  if (server.hasArg("stat4"))
  {
    if (strncmp(server.arg("stat4").c_str(), "1", 1) == 0)
      stat4 = true;
  }
  else
  {
    stat4 = PowerOn4;
  }
  if (server.hasArg("stat5"))
  {
    if (strncmp(server.arg("stat5").c_str(), "1", 1) == 0)
      stat5 = true;
  }
  else
  {
    stat5 = PowerOn5;
  }

  String out = "";

  out =
      "<html>\
    <head>\
      <meta charset=\"utf-8\" />\
      <title>Интерактивная мишень</title>\
      <style>\
        body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      </style>\
    </head>\
    <body>\
      <h1>Интерактивная Mишень  1.0</h1>\n";

  if (stat)
  {
    out += "\
      <h2>СТАРТ ИГРЫ : Включено</br>\
      <a href=\"/?stat=0\">Выключить</a></h2>\
      ";
  }
  else
  {
    out += "\
      <h2>СТАРТ ИГРЫ : Выключено</br>\
      <a href=\"/?stat=1\">Включить</a><h2>\
      ";
  }

  if (stat1)
  {
    out += "\
      <h2>мишень 1 1 </br>\
      <a href=\"/?stat1=0\">OFF</a></h2>\
      ";
  }
  else
  {
    out += "\
       <h2>мишень 1 0 </br>\
      <a href=\"/?stat1=1\">ON</a><h2>\
      ";
  }

  if (stat2)
  {
    out += "\
       <h2>мишень 2 1 </br>\
      <a href=\"/?stat2=0\">OFF</a></h2>\
      ";
  }
  else
  {
    out += "\
       <h2>мишень 2 0</br>\
      <a href=\"/?stat2=1\">ON</a><h2>\
      ";
  }

  if (stat3)
  {
    out += "\
       <h2>мишень 3 1 </br>\
      <a href=\"/?stat3=0\">OFF</a></h2>\
      ";
  }
  else
  {
    out += "\
       <h2>мишень 3 0 </br>\
      <a href=\"/?stat3=1\">ON</a><h2>\
      ";
  }

  if (stat4)
  {
    out += "\
       <h2>мишень 4 1 </br>\
      <a href=\"/?stat4=0\">OFF</a></h2>\
      ";
  }
  else
  {
    out += "\
       <h2>мишень 4 0 </br>\
      <a href=\"/?stat4=1\">ON</a><h2>\
      ";
  }

  if (stat5)
  {
    out += "\
       <h2>мишень 5 1 </br>\
      <a href=\"/?stat5=0\">OFF</a></h2>\
      ";
  }
  else
  {
    out += "\
       <h2>мишень 5 0 </br>\
      <a href=\"/?stat5=1\">ON</a><h2> \
      ";
  }

  out += "<h2>мишень_1: Заряд =  ";
  out += 10; //zaryad_1;
  out += "%   ; </h2><h2>мишень_2: Заряд =  ";
  out += 5; //zaryad_2;
  out += "%   ;  </h2><h2>мишень_3: Заряд =  ";
  out += 45; //zaryad_3;
  out += "%   ;  </h2><h2>мишень_4: Заряд =  ";
  out += 100; //zaryad_4;
  out += "%   ;</h2><h2>мишень_5: Заряд =  ";
  out += 99; //zaryad_5;
  out += "%   ;</h2> Время : ";
  out += d_1;
  out += d_2;
  out += d_3;
  out += d_4;
  out += "  ;</h2> </br>";
  out += "\
    </body>\
  </html>";

  server.send(200, "text/html", out);
  if (stat != PowerOn)
  {
    PowerOn = stat;
    tamer_bud = 1;

    if (PowerOn)
      Serial.println("Power is ON");

    else
      Serial.println("Power is OFF");
  }
  if (stat1 != PowerOn1)
  {
    tamer_bud = 1;
    PowerOn1 = stat1;
    if (PowerOn1)
      Serial.println("mishen1 = 1");
    else
      Serial.println("mishen1= 0");
  }
  if (stat2 != PowerOn2)
  {
    tamer_bud = 1;
    PowerOn2 = stat2;
    if (PowerOn2)
      Serial.println("mishen2 = 1");
    else
      Serial.println("mishen2= 0");
  }
  if (stat3 != PowerOn3)
  {
    tamer_bud = 1;
    PowerOn3 = stat3;
    if (PowerOn3)
      Serial.println("mishen3 = 1");
    else
      Serial.println("mishen3= 0");
  }
  if (stat4 != PowerOn4)
  {
    tamer_bud = 1;
    PowerOn4 = stat4;
    if (PowerOn4)
      Serial.println("mishen4 = 1");
    else
      Serial.println("mishen4= 0");
  }
  if (stat5 != PowerOn5)
  {
    tamer_bud = 1;
    PowerOn5 = stat5;
    if (PowerOn5)
      Serial.println("mishen5 = 1");
    else
      Serial.println("mishen5= 0");
  }
}

void http_server()
{
  MDNS.begin(host);
  httpUpdater.setup(&server);
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
  MDNS.addService("http", "tcp", 80);
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);
  delay(100);
  Serial.println("HTTP server started");
  delay(20);
}
void WiFi_AP()
{
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid_ap, pass_ap); // запуск точки доступа
  Serial.println("done");
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
}
void WiFi_STA()
{
  if (flagconn == 1)
  {
    evTimeconn = millis();
    flagconn = 0;
    WiFi_AP(); // то запускаем точу доступа, раз уж пытаемся подключится к wi-fi роутару
  }
  if (millis() - evTimeconn > 2000)
  {
    if (flagconn == 0)
      evTimeconn = millis();
    Serial.print("Connecting to...");
    Serial.println(ssid);
    WiFi.begin(ssid.c_str(), pass.c_str()); // пробуем подключится к роутеру
    delay(10);
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi connected");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    flagconn = 1; //для возврата таймера для следующих попытках подключится к wi-fi после разрыва подключения
    http_server();
  }
}

void setup(void)
{
  delay(2000);
  EEPROM.begin(512); // размер eeprom памяти 512 байт
  Serial.begin(9600);
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(pass);
  WiFi.mode(WIFI_OFF);
  //WiFi.mode(WIFI_STA);
  WiFi_AP();
  http_server();
  // client.set_server(mqtt_server, mqtt_port);
  evTimeconn = millis();
}
void loop()
{

  while (Serial.available()) // проверяем команды которые пришли с com порта
  {
    char inChar = Serial.read();
    riad_serial += inChar;
    if (inChar == '\n')
    {
      //Serial.print("String: ");
      // Serial.println(riad_serial);
      if (riad_serial.indexOf("M1") != -1)
      {
        String Voltage = riad_serial.substring(2);
        Voltage.trim();
        mih1_sens = Voltage.toInt();
      }
      if (riad_serial.indexOf("M2") != -1)
      {
        String Voltage = riad_serial.substring(2);
        Voltage.trim();
        mih2_sens = Voltage.toInt();
      }
      if (riad_serial.indexOf("M3") != -1)
      {
        String Voltage = riad_serial.substring(2);
        Voltage.trim();
        mih3_sens = Voltage.toInt();
      }
      if (riad_serial.indexOf("M4") != -1)
      {
        String Voltage = riad_serial.substring(2);
        Voltage.trim();
        mih4_sens = Voltage.toInt();
      }
      if (riad_serial.indexOf("M5") != -1)
      {
        String Voltage = riad_serial.substring(2);
        Voltage.trim();
        mih5_sens = Voltage.toInt();
      }
      if (riad_serial.indexOf("M11") != -1)
      {
        m1 = true;
      }
      if (riad_serial.indexOf("M21") != -1)
      {
        m2 = true;
      }
      if (riad_serial.indexOf("M31") != -1)
      {
        m3 = true;
      }
      if (riad_serial.indexOf("M41") != -1)
      {
        m4 = true;
      }
      if (riad_serial.indexOf("M51") != -1)
      {
        m5 = true;
      }
      if (riad_serial.indexOf("M10") != -1)
      {
        m1 = false;
      }
      if (riad_serial.indexOf("M20") != -1)
      {
        m2 = false;
      }
      if (riad_serial.indexOf("M30") != -1)
      {
        m3 = false;
      }
      if (riad_serial.indexOf("M40") != -1)
      {
        m4 = false;
      }
      if (riad_serial.indexOf("M50") != -1)
      {
        m5 = false;
      }
      /* if (riad_serial.indexOf("Z1") != -1) // проверяем заряд
      {
        String Voltage = riad_serial.substring(2);
        Voltage.trim();
        zaryad_1 = Voltage.toInt();
      }
      if (riad_serial.indexOf("Z2") != -1) // проверяем заряд
      {
        String Voltage = riad_serial.substring(2);
        Voltage.trim();
        zaryad_2 = Voltage.toInt();
      }
      if (riad_serial.indexOf("Z3") != -1) // проверяем заряд
      {
        String Voltage = riad_serial.substring(2);
        Voltage.trim();
        zaryad_3 = Voltage.toInt();
      }
      if (riad_serial.indexOf("Z4") != -1) // проверяем заряд
      {
        String Voltage = riad_serial.substring(2);
        Voltage.trim();
        zaryad_4 = Voltage.toInt();
      }
      if (riad_serial.indexOf("Z5") != -1) // проверяем заряд
      {
        String Voltage = riad_serial.substring(2);
        Voltage.trim();
        zaryad_5 = Voltage.toInt();
      }*/
      proveryaem_mish();
      on_off_mish_ser(); // включаем выключаем мишени на сервере
      riad_serial = "";
    }
  }

  if (PowerOn)
  {
    if (PowerOn1 || PowerOn2 || PowerOn3 || PowerOn4 || PowerOn5)
    {
    }
    else if (milisek > 1)
    {
      PowerOn = false;
      
    }
  }

  on_off_posle_servera();
  tamin_5sec();
  zapusk_tamera_10mil();
  server.handleClient();
}
