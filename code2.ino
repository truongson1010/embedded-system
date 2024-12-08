#include <Servo.h>
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
DHT dht; 
LiquidCrystal_I2C lcd(0x27,16,2); 
const int servopin =9;
Servo servo; 
float temperature;
const int frequency1 = 1000;
const int frequency2 = 3000;
const int button1 = 5;
const int button2 = 6;
const int button3 = 7;
const int bulb = 8;
const int led0 = 11;
const int led1 = 4;
const int led2 = 3;
const int led3 = 2;
const int temp1 = 28;
const int temp2 = 35;
const int temp3 = 15;
const int temp4 = 8;
const int temp5 = 45;
void setup() {
    Serial.begin(9600);
    servo.attach(servopin);
    servo.write(0);
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
   temperature = dht.getTemperature(); 
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("temperature:");
   lcd.setCursor(12,0);
   lcd.print(temperature);
   lcd.print((char)223); 
   lcd.print("C");
   digitalWrite(led1,HIGH);
   digitalWrite(led0,HIGH);
   bool State1 = digitalRead(button1) == LOW;
   bool State2 = digitalRead(button2) == LOW;
   bool State3 = digitalRead(button3) == LOW;
   Serial.print("but1: ");
   Serial.println(State1);
   Serial.print("but2: ");
   Serial.println(State2);
   Serial.print("but3: ");
   Serial.println(State3);
   delay(500);
   digitalWrite(led2,LOW);
   digitalWrite(led3,LOW);
   digitalWrite(bulb,LOW);
   if((temperature > temp1 && temperature < temp2) || State1) {
    servo.write(90);
    digitalWrite(led3,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(bulb,LOW);
    noTone(12);
    delay(1000);
   }  else if((temperature < temp1 && temperature > temp3) || State2) {
    servo.write(0);
    digitalWrite(led3,LOW); 
    digitalWrite(led2,HIGH);
    digitalWrite(bulb,HIGH); 
    tone(12,frequency1);
   } else if((temperature < temp3 && temperature > temp4)  || (temperature > temp2 && temperature < temp5) || State3) {
    servo.write(0);
    digitalWrite(led3,LOW);
    digitalWrite(led2,LOW); 
    digitalWrite(bulb,LOW);
    tone(12,frequency2); 
   } else {
    servo.write(0);
    digitalWrite(led3,LOW);
    digitalWrite(led2,LOW); 
    digitalWrite(bulb,LOW);
    noTone(12);
   }
}
