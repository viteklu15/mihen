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
long tamer_5sec, tamer_10mil;
int sec, milisek = 0;
int max_udar = 500;
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
void zapusk_tamera_10mil()
{
  if (sec == 5)
  {
    if (millis() - tamer_10mil > 100)
    {

      tamer_10mil = millis();
      milisek++;

      Serial.println(milisek);
    }
  }
  else
  {
    milisek = 0;
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
      if (sec == 5){
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
    if(sec == 5){
    PowerOn1 = false;
    PowerOn2 = false;
    PowerOn3 = false;
    PowerOn4 = false;
    PowerOn5 = false;
    
  }sec = 0;
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
      <h1>Интерактивная мишень 1.0</h1>\n";
 

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

  out += " <h2>мишень 1: Заряд = ";
  out += 12;
  out += " %   ";

  if (stat1)
  {
    out += "\
       Включено</br>\
      <a href=\"/?stat1=0\">OFF</a></h2>\
      ";
  }
  else
  {
    out += "\
       Выключено</br>\
      <a href=\"/?stat1=1\">ON</a><h2>\
      ";
  }
  
  out += " <h2>мишень 2: Заряд = ";
  out += 12;
  out += " %   ";
  
  if (stat2)
  {
    out += "\
       Включено</br>\
      <a href=\"/?stat2=0\">OFF</a></h2>\
      ";
  }
  else
  {
    out += "\
       Выключено</br>\
      <a href=\"/?stat2=1\">ON</a><h2>\
      ";
  }

  out += " <h2>мишень 3: Заряд = ";
  out += 12;
  out += " %   ";
  if (stat3)
  {
    out += "\
       Включено</br>\
      <a href=\"/?stat3=0\">OFF</a></h2>\
      ";
  }
  else
  {
    out += "\
       Выключено</br>\
      <a href=\"/?stat3=1\">ON</a><h2>\
      ";
  }

  out += " <h2>мишень 4: Заряд = ";
  out += 12;
  out += " %   ";
  if (stat4)
  {
    out += "\
       Включено</br>\
      <a href=\"/?stat4=0\">OFF</a></h2>\
      ";
  }
  else
  {
    out += "\
       Выключено</br>\
      <a href=\"/?stat4=1\">ON</a><h2>\
      ";
  }
  out += " <h2>мишень 5: Заряд = ";
  out += 12;
  out += " %   ";
  if (stat5)
  {
    out += "\
       Включено</br>\
      <a href=\"/?stat5=0\">OFF</a></h2>\
      ";
  }
  else
  {
    out += "\
       Выключено</br>\
      <a href=\"/?stat5=1\">ON</a><h2>\
      ";
  }

  out += "\
    </body>\
  </html>";

  server.send(200, "text/html", out);
  if (stat != PowerOn)
  {
    PowerOn = stat;

    if (PowerOn)
      Serial.println("Power is ON");
    else
      Serial.println("Power is OFF");
  }
  if (stat1 != PowerOn1)
  {
    PowerOn1 = stat1;
    if (PowerOn1)
      Serial.println("mishen1 = 1");
    else
      Serial.println("mishen1= 0");
  }
  if (stat2 != PowerOn2)
  {
    PowerOn2 = stat2;
    if (PowerOn2)
      Serial.println("mishen2 = 1");
    else
      Serial.println("mishen2= 0");
  }
  if (stat3 != PowerOn3)
  {
    PowerOn3 = stat3;
    if (PowerOn3)
      Serial.println("mishen3 = 1");
    else
      Serial.println("mishen3= 0");
  }
  if (stat4 != PowerOn4)
  {
    PowerOn4 = stat4;
    if (PowerOn4)
      Serial.println("mishen4 = 1");
    else
      Serial.println("mishen4= 0");
  }
  if (stat5 != PowerOn5)
  {
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
  /*
    WiFiClient client;
 
  if (client.connect(ip_1, 80))
    {
    client.print( "GET /get.php?");
    client.print("test=1");    
    client.println( " HTTP/1.1");
    client.print( "Host:" );
    //client.println(ip_1);
    client.println( "Connection: close" );
        client.println();
        client.println();

   delay(10000); 

}
*/

  while (Serial.available()) // проверяем команды которые пришли с com порта
  {
    char inChar = Serial.read();
    riad_serial += inChar;
    if (inChar == '\n')
    {
      Serial.print("String: ");
      Serial.println(riad_serial);
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
      proveryaem_mish();
      riad_serial = "";
    }
  }

  // if (WiFi.status() != WL_CONNECTED)
  // { // при разрывах wi-fi подключения
  //    WiFi.mode(WIFI_AP_STA);
  //   WiFi_STA();
  //  }
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

  tamin_5sec();
  zapusk_tamera_10mil();
  server.handleClient();
}
