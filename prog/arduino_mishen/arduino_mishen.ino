const int wakeUpPin = 2;
bool flag_prer= false;
int col_raz= 0;

long tamer_5sec= 0;


void flag_prer_f()
{
    if (flag_prer){
      
    while(flag_prer){
      //flag_prer= false;
      if ((millis() - tamer_5sec) > 1000){
       
      tamer_5sec = millis();
      if (col_raz<4 ){
      Serial.println("1_raz_prosho"); 
      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
                             // wait for a second
     digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW    
      }
     col_raz++;
     if (col_raz>7){
      sleepMode(SLEEP_POWER_DOWN);// wait for a second  
   sleep(); // Go to sleep
      }
      }
   }

   
    }
}

void wakeUp()
{
  flag_prer= true;
  col_raz= 0;
}


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
  pinMode(wakeUpPin, INPUT);   
   Serial.begin(9600);
    detachInterrupt(0);
    

}





// the loop function runs over and over again forever
void loop() {
   attachInterrupt(0, wakeUp, CHANGE  );
  //sleepMode(SLEEP_POWER_DOWN);// wait for a second  
   //sleep(); // Go to sleep
 flag_prer_f();
}
