#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int MinuteIN = 11;
const int SecondIN = 10;
const int RunIN    =  9;
const int StopIN   =  8;

const int buzzer = 12;

int MinuteBotton =  0;
int SecondBotton =  0;

int MinuteTimes  =  0;
int SecondTimes  =  0;

unsigned long MTimes =  0;
unsigned int  STimes =  0;

unsigned long Time   =  0;
unsigned long RunTime   = 0;
unsigned long RunTime2   = 0;

unsigned long LCDTime = 0;

int i =0;

void setup(){
    pinMode(MinuteIN,INPUT);
    pinMode(SecondIN,INPUT);
    pinMode(RunIN   ,INPUT);
    pinMode(StopIN,INPUT);
    lcd.init();
    lcd.backlight();

}

void loop(){
    MinuteBotton = digitalRead(MinuteIN);

    if(MinuteBotton == 1){
        MinuteTimes++;
        tone(buzzer,262,100);
        delay(200);
    }

    SecondBotton = digitalRead(SecondIN);

    if(SecondBotton == 1){
        SecondTimes++;
        tone(buzzer,262,100);
        delay(200);
    }

    if(SecondTimes > 60){
        lcd.init();
        SecondTimes = 0;
    }

    MTimes = MinuteTimes *  1000;
    STimes = SecondTimes *  1000;

    Time = MTimes * 60 + STimes;

    if(digitalRead(RunIN) == 1){
        tone(buzzer,262,100);
        lcd.setCursor(7,1);
        lcd.print("RUN!");
        RunTime = (millis()/1000) + (Time/1000);
        i = 1;
    }

    RunTime2 = millis()/1000;


    if(RunTime == RunTime2 ){
            tone(buzzer,262,10000);
            i = 0;
            lcd.setCursor(7,1);
            lcd.print("END!");
            lcd.init();
    }

    if(digitalRead(StopIN) == 1){
        i = 0;
        tone(buzzer,262,100);
        delay(100);
        noTone(buzzer);
        lcd.init();
        lcd.setCursor(0,1);
        lcd.print("STOP!");
        lcd.init();
    }

    if(digitalRead(RunIN) == 1 && digitalRead(StopIN) == 1){
        tone(buzzer,262,100);
        i = 0;
        MinuteTimes = 0;
        SecondTimes = 0;
        lcd.setCursor(0,1);
        lcd.print("RESET!");
        lcd.init();
    }

    if(i == 1){
        LCDTime = RunTime - RunTime2;
        lcd.init();
        lcd.setCursor(7,1);
        lcd.print("COUNT!");
        lcd.setCursor(0,1);
        lcd.print(LCDTime);
    }

    lcd.setCursor(0,0);
    lcd.print("M=");
    lcd.print(MinuteTimes);
    lcd.print(":");
    lcd.print("S=");
    lcd.print(SecondTimes);

}
