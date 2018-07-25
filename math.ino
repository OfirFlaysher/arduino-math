#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "musical_notes.h"

const int BLUE_LED = 4;
const int YELLOW_LED = 10;
const int WHITE_LED = 9; 
const int RED_LED = 11; 
const int GREEN_LED = 7; 
const int BLUE_BUTTON = 2;
const int YELLOW_BUTTON = 5;
const int WHITE_BUTTON = 6;
const int RED_BUTTON = 3;
const int GREEN_BUTTON = 8;
const int BUZZER = 12;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int score = 0;
 
void setup() 
{  
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  pinMode(YELLOW_BUTTON, INPUT_PULLUP);
  pinMode(WHITE_BUTTON, INPUT_PULLUP);
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(BLUE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(WHITE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  
  randomSeed(analogRead(0));

  blinkAll();
}

void loop() 
{
  while(true)
  {
    int operation = random(0, 4);
    char op = 'z';
    int num1 = random(0, 21);
    int num2 = random(0, 21);
    int dividers[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    if(operation == 0)
    {
      op = '+';
    }
    else if(operation == 1)
    {
      op = '-';
      if(num1 - num2 < 0)
      {
        int num = num1;
        num1 = num2;
        num2 = num;
      }
    }
    else if(operation == 2)
    {
      op = 'x';
      num1 = random(0, 10);
      num2 = random(0, 10);
    }
    else
    {
      op = ':';
      int j = 0;
      for(int i = num1; i > 0; i--)
      {
        if(num1 % i == 0)
        {
          dividers[j] = i;
          j++;
        }
      }      
      num2 = dividers[random(0, j)];
    }
    int res = 0;
    int button;
    boolean isCurrect = false;
    int lives = 3;
    while(lives > 0)
    {
      lcd.clear();
      lcd.setCursor(12, 0);
      lcd.print(score);
      lcd.setCursor(0, 1);
      lcd.print(num1);
      lcd.print(" ");
      lcd.print(op);
      lcd.print(" ");
      lcd.print(num2);
      lcd.print(" = ");
      lcd.print(res);
      button = getButtonPressed();
      if(button == 0)
      {
        res++;
      }
      else if(button == 1 && res > 0)
      {
        res--;
      }
      else if(button == 2)
      {
        if((op == '+' && res == num1 + num2) || (op == '-' && res == num1 - num2) ||
            op == 'x' && res == num1 * num2 || op == ':' && res == num1 / num2)
        {
          score++;
          isCurrect = true;
          laugh();
          lives = -1;
        }
        else
        {
          beep(2093,1000);
          lives--;
        }
      }
      else if(button == 3)
      {
        res = res + 10;
      }
      else if(button == 4 && res >= 10)
      {
        res = res - 10;
      }
    }
    if(lives == 0 && score > 0)
    {
      score--;
    }
  }
}

void onOffLED(int color, int x)
{
  if(color == 0)
  {
    digitalWrite(BLUE_LED, x);
  }
  else if(color == 1)
  {
    digitalWrite(YELLOW_LED, x);
  }
  else if(color == 2)
  {
    digitalWrite(WHITE_LED, x);
  }
  else if(color == 3)
  {
    digitalWrite(RED_LED, x);
  }
  else if(color == 4)
  {
    digitalWrite(GREEN_LED, x);
  }
}

void blinkLED(int color, int t)
{
  if(color == 0)
  {
    digitalWrite(BLUE_LED, HIGH);
    delay(t);
    digitalWrite(BLUE_LED, LOW);
  }
  else if(color == 1)
  {
    digitalWrite(YELLOW_LED, HIGH);
    delay(t);
    digitalWrite(YELLOW_LED, LOW);
  }
  else if(color == 2)
  {
    digitalWrite(WHITE_LED, HIGH);
    delay(t);
    digitalWrite(WHITE_LED, LOW);
  }
  else if(color == 3)
  {
    digitalWrite(RED_LED, HIGH);
    delay(t);
    digitalWrite(RED_LED, LOW);
  }
  else if(color == 4)
  {
    digitalWrite(GREEN_LED, HIGH);
    delay(t);
    digitalWrite(GREEN_LED, LOW);
  }
}

void blinkAll()
{
  for(int i = 0; i < 3; i++)
  {  
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(WHITE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(WHITE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    delay(500);
  }
}

void beep(int frequencyInHertz, long timeInMilliseconds)
{ 
  int x;
  long delayAmount = (long)(1000000 / frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));
  for (x = 0; x < loopTime; x++)
  {
    digitalWrite(BUZZER, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(BUZZER, LOW);
    delayMicroseconds(delayAmount);
  }
}

int getButtonPressed()
{
  int led = 5;
  int button;
  while(true)
  {
    if(digitalRead(BLUE_BUTTON) == HIGH)
    {
      led = 0;
      button = BLUE_BUTTON;
    }
    else if(digitalRead(YELLOW_BUTTON) == HIGH)
    {
      led = 1;
      button = YELLOW_BUTTON;
    }
    else if(digitalRead(WHITE_BUTTON) == HIGH)
    {
      led = 2;
      button = WHITE_BUTTON;
    }
    else if(digitalRead(RED_BUTTON) == HIGH)
    {
      led = 3;
      button = RED_BUTTON;
    }
    else if(digitalRead(GREEN_BUTTON) == HIGH)
    {
      led = 4;
      button = GREEN_BUTTON;
    }
    if(led != 5)
    {
      if(led == 0 || led == 1 || led == 3 || led == 4)
      {
        beep(2093, 100);
        blinkLED(led, 300);
      }
      else if(led == 2)
      {
        blinkLED(led, 300);
      }
      return led;
    }
  }
}

void laugh() 
{
  for(int i = 1000; i < 2000; i = i * 1.1) 
  {
    beep(i, 10);
  }
  delay(50);
  for(int i = 1000; i > 500; i = i * 0.9) 
  {
    beep(i, 10);
  }
  delay(50);
  for(int i = 1000; i < 2000; i = i * 1.1) 
  {
    beep(i, 10);
  }
  delay(50);
  for(int i = 1000; i > 500; i = i * 0.9) 
  {
    beep(i, 10);
  }
  delay(50);
  for(int i = 1000; i < 2000; i = i * 1.1) 
  {
    beep(i, 10);
  }
  delay(50);
  for(int i = 1000; i > 500; i = i * 0.9) 
  {
    beep(i, 10);
  }
  delay(50);
  for(int i = 1000; i < 2000; i = i * 1.1) 
  {
    beep(i, 10);
  }
  delay(50);
  for(int i = 1000; i > 500; i = i * 0.9) 
  {
    beep(i, 10);
  }
  delay(50);
}

