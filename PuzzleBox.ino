#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);
int value_1 = digitalRead(0);   //Pin Switch number 1
int value_2 = digitalRead(1);   //Pin Switch number 2
int value_3 = digitalRead(2);   //Pin Switch number 3
int value_4 = digitalRead(3);   //Pin Switch number 4
int value_5 = digitalRead(4);   //Pin Switch number 5
int LEDpin = 6;                 //Pin LED

//Variables for the binary code to work
int switch_1 = 0;
int switch_2 = 0;
int switch_3 = 0;
int switch_4 = 0;
int switch_5 = 0;
int switch_total = 0;

String lcd_print(String text1, String text2) {
  lcd.init();                      // initialize the LCD 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);              // Sets cursor to the top row of the LCD
  lcd.print(text1);                // Changing first row
  lcd.setCursor(0,1);              // Sets cursor to the bottom row of the LCD
  lcd.print(text2);                // Changing second row
}

int user_input() {
//  Serial.println(value_1, value_2, value_3, value_4, value_5);
  if (value_1 == HIGH) {
    switch_1 = 1;
  }
  if (value_2 == HIGH) {
    switch_2 = 2;
  }
  if (value_3 == HIGH) {
    switch_3 = 4;
  }
  if (value_4 == HIGH) {
    switch_1 = 8;
  }
  if (value_5 == HIGH) {
    switch_1 = 16;
  }
  int switch_total = switch_1 + switch_2 + switch_3 + switch_4 + switch_5;
}

void led_morse() {
  // 0 is a space, 1 is a dot, 2 is a dash, 3 is the separator between words
  int morse[] = {1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 2, 2, 3, 2, 2, 0, 1, 2, 0, 2, 1, 0, 2, 1, 2, 2, 3, 1, 1, 1, 0, 1, 1, 0, 2, 1, 1, 0, 1, 0, 1, 1, 1, 3, 2, 1, 1, 0, 2, 2, 2, 0, 1, 0, 1, 1, 1, 3, 1, 2, 3, 2, 1, 2, 1, 0, 1, 1, 0, 1, 2, 1, 0, 2, 1, 2, 1, 0, 1, 2, 1, 1, 0, 1, 3, 1, 1, 1, 1, 0, 1, 2, 0, 1, 1, 1, 2, 0, 1, 0, 1, 1, 2, 2, 1, 1};
  for (int i = 0; i < 106; i++) {
    if (morse[i] == 0) {
      delay (2000);
      }
    else if (morse[i] == 1) {
      digitalWrite(LEDpin,HIGH);
      delay (500);
      digitalWrite(LEDpin,LOW);
      delay (500);
      }
    else if (morse[i] == 2) {
      digitalWrite(LEDpin,HIGH);
      delay (1000);
      digitalWrite(LEDpin, LOW);
      delay (500);
      }
    else {
      delay (3000);
      }
    Serial.println(morse[i]);
    
  }
}

void lock(bool open_lock){
  if (open_lock == false) {
    delay (1500);
    myservo.write(180);
  }
  else {
    delay(1500);
    myservo.write(20);
  }
}

void setup() {
  myservo.attach(7);       //Initializing lock
  myservo.write(180);
  lock(true);
  Serial.begin(9600);      //Initializing morse
  pinMode(value_1, INPUT_PULLUP);     //Initializing switch
  pinMode(value_2, INPUT_PULLUP);     //Initializing switch
  pinMode(value_3, INPUT_PULLUP);     //Initializing switch
  pinMode(value_4, INPUT_PULLUP);     //Initializing switch
  pinMode(value_5, INPUT_PULLUP);     //Initializing switch
  int value_1 = digitalRead(0);   //Pin Switch number 1
  int value_2 = digitalRead(1);   //Pin Switch number 2
  int value_3 = digitalRead(2);   //Pin Switch number 3
  int value_4 = digitalRead(3);   //Pin Switch number 4
  int value_5 = digitalRead(4);   //Pin Switch number 5
  int LEDpin = 6;                 //Pin LED
  //Start displaying and running the box
}

void loop() {
  lcd_print("Welcome to Pbox", "Have Fun!");
  delay (5000);
  lcd_print("Morse code    ^^", "Look at LED   ||");
  delay (5000);
  led_morse();
  lcd_print("Morse Done", "Did it work?");
  lock(false);
  Serial.println();
  led_morse();
  delay (50000);
  user_input();
  if (switch_total == 2) {
      lcd_print("Congratulations!", "Open the box");
      lock(false);
  }
  else {
    lcd_print("Wrong Answer", "Try Again");
  }
  delay(1000);
}
