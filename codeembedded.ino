#include <Servo.h>
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
DHT dht; 
LiquidCrystal_I2C lcd(0x27,16,2); 
int servopin =9;
Servo servo; 
int frequency1 = 1000;
int frequency2 = 3000;
int button1 = 5;
int button2 = 6;
int button3 = 7;
int bulb = 8;
int led0 = 11;
int led1 = 4;
int led2 = 3;
int led3 = 2;
void setup() {
    Serial.begin(9600);
    servo.attach(servopin);
    pinMode(A0,INPUT);
    lcd.init (); 
    lcd.backlight();
    dht.setup(A0); 
    pinMode(12, OUTPUT);
    pinMode(button1,INPUT_PULLUP);
    pinMode(button2,INPUT_PULLUP);
    pinMode(button3,INPUT_PULLUP);
    pinMode(bulb,OUTPUT);
    pinMode(led0,OUTPUT);
    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    pinMode(led3,OUTPUT);
}
void loop() {
   int temperature = dht.getTemperature(); 
   lcd.setCursor(0,0);
   lcd.print("temperature:");
   lcd.setCursor(13,0);
   lcd.print(temperature);
   lcd.print((char)223); 
   lcd.print("C");
   digitalWrite(led1,HIGH);
   digitalWrite(led0,HIGH);
   int but1 = digitalRead(button1);
   int but2 = digitalRead(button2);
   int but3 = digitalRead(button3);
   Serial.print("but1: ");
   Serial.println(but1);
   delay(1000);
   Serial.print("but2: ");
   Serial.println(but2);
   delay(1000);
   Serial.print("but3: ");
   Serial.println(but3);
   Serial.println(temperature);
   delay(1000);
   digitalWrite(led2,LOW);
   digitalWrite(led3,LOW);
   digitalWrite(bulb,LOW);
   if(temperature>1){
   if((29 < temperature < 35))
   {
    digitalWrite(led3,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(bulb,LOW);
    servo.write(180); 
    delay(100);
   }
   else if((15 <= temperature <= 29))
   {
    servo.detach();
    digitalWrite(led3,LOW); 
    digitalWrite(led2,HIGH);
    digitalWrite(bulb,HIGH); 
    tone(12,frequency1);
   }
   else if((6 < temperature < 15) || (35 < temperature < 40))
   {
    servo.detach();
    digitalWrite(led3,LOW);
    digitalWrite(led2,LOW); 
    digitalWrite(bulb,LOW);
    tone(12,frequency2); 
   }
   }
   if(temperature==0){
   if((but1==0)&&(but2==1)&&(but3==1))
   {
    servo.write(180);
    noTone(12); 
    digitalWrite(led2,LOW);
    digitalWrite(bulb,LOW);
    digitalWrite(led3,HIGH);
    delay(100);
    }

    else if((but2==0)&&(but1==1)&&(but3==1))
   {
    servo.detach();
    digitalWrite(led3,LOW); 
    digitalWrite(led2,HIGH);
    digitalWrite(bulb,HIGH); 
    tone(12,frequency1);
   }

    else if((but3==0)&&(but1==1)&&(but2==1))
   {
    servo.detach();
    digitalWrite(led3,LOW);
    digitalWrite(led2,LOW); 
    digitalWrite(bulb,LOW);
    tone(12,frequency2); 
}

  else if((but1==1)&&(but2==1)&&(but3==1))
   {
    noTone(12);
    servo.detach();
    digitalWrite(led3,LOW); 
    digitalWrite(led2,LOW);
    digitalWrite(bulb,LOW); 
   }
   }
}