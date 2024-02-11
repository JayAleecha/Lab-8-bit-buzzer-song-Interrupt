#include <Arduino.h>

#define BUZZER 19
#define BUTTON 15
#define LED 18
hw_timer_t *My_timer = NULL;

double c = 1000000/(2*16.35) , D = 1000000/(2*18.35) , E = 1000000/(2*20.60) , F = 1000000/(2*21.83) , 
       G = 1000000/(2*24.50) , A = 1000000/(2*27.50) , B = 1000000/(2*30.87) , C = 1000000/(2*32.70) , Stop = 8000000;

double Slow = 2.5;

int Octaves = 0;

double song[] = {Stop,Stop,Stop,G,  Stop,G,Stop,G,  A,G,E,G,  Stop,A,Stop,C,  Stop,Stop,Stop,Stop,  G,A,G,C,  G,A,G,C,  E,D,G,E,
                 Stop,Stop,Stop,Stop,  G,c,D,E,  D,E,G,E,  D,c,E,D,  Stop,Stop,Stop,Stop,  G,c,D,E,  D,E,G,E,  D,c,E,D,
                 Stop,G,Stop,A,  Stop,c,Stop,D,  E,D,G,D,  E,D,c,A,  Stop,c,D,E,  Stop,G,Stop,A,  G,A,C,A,  G,E,Stop,G};

double rhythm[] = {1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,
                   1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,
                   1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1};

// This is the Timer ISR. It is automatically called 
// on a timer alarm event.
void IRAM_ATTR onTimer() {
  digitalWrite(BUZZER, !digitalRead(BUZZER));
}

void IRAM_ATTR onButton() {
  digitalWrite(LED, !digitalRead(LED));
  if(Slow > 0.5){
    Slow -= 0.5;
  }else{
    Slow = 2.5;
  }
}

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  My_timer = timerBegin(0, 80, true);   // use timer 0 and set prescale to 80 so 1 tick is 1 uSec
  timerAttachInterrupt(My_timer, &onTimer, true); // point to the ISR
  // timerAlarmWrite(My_timer, 1000000 , true);  // set alarm every 1 sec
  // timerAlarmEnable(My_timer);  // enable the alarm
  //timerAttachInterrupt(My_timer, &onButton, true); // point to the ISR
  timerAlarmEnable(My_timer);  // enable the alarm
  attachInterrupt(BUTTON, &onButton, RISING);
}

void play(int Octaves) {
    timerAlarmEnable(My_timer);
  for(int i = 0 ; i < sizeof(song)/sizeof(song[0]) ; i++){
    Serial.print("Speed = ");
    Serial.print(((5-Slow)/0.5)-4);
    Serial.print(" Song note Frequency = ");
    Serial.println(10000000/(song[i]*2));    
    timerAlarmWrite(My_timer, song[i]/pow(2,Octaves), true);
    delay(((Slow*500)-100)/rhythm[i]);
  }
}

void loop() {

  play(4);

}