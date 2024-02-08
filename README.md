This is a Lhong-mae-ping song 8 bit code.
Use interrupt method to made it.
How it's work ?
Ans. Use interrupt as void IRAM_ATTR _____() 2 function. At first void IRAM_ATTR onTimer() to define frequency note buzzer use with timerAttachInterrupt(My_timer, &onTimer, true); by My_timer = timerBegin(0, 80, true);
     it use timer 0 and set prescale to 80 so 1 tick is 1 uSec, &onTimer is point to void IRAM_ATTR onTimer(), timerAlarmEnable(My_timer); to enable the alarm and  timerAlarmWrite(My_timer, x , true); to set alarm 
     every x = 10000000 equal to 1 sec. Another void IRAM_ATTR onButton() to get signal button to adjust speed song and trig LED to check botton bounce use with attachInterrupt(BUTTON, &onButton, RISING); by BUTTON 
     is to get input from button, &onButton is point to void IRAM_ATTR onButton(), RISING is use to interrupt when signal from button switch from low to high. Overall function void play(int Octaves) is use to run         song note with rhyhm, frequency is up to octaves assign this function must put in void ioop() function.
