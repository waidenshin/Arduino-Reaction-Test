#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  Serial.flush();
  Serial.println(0);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  randomSeed(analogRead(0));
  unsigned int quant = 3;
  unsigned int result = 0;
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("REACTION TEST");
  delay(1500);
  lcd.clear();
  lcd.print("Quickly press");
  lcd.setCursor(0,1);
  lcd.print("opposite buttons");
  delay(2000);
  lcd.clear();
  lcd.print("Choose number");
  lcd.setCursor(0,1);
  lcd.print("of repeats");
  delay(2000);
  lcd.clear();
  lcd.print("X  O  O  O");
  lcd.setCursor(0,1);
  lcd.print("3  5  7  10  OK");
  do                                      // choosing an amount of tests (3, 5, 7 or 10)
  {     
    if (!digitalRead(9)) {
      quant = 10;
      lcd.clear();
      lcd.print("O  O  O  X");
      lcd.setCursor(0,1);
      lcd.print("3  5  7  10  OK");
      }
    if (!digitalRead(10)) {
      quant = 7;
      lcd.clear();
      lcd.print("O  O  X  O");
      lcd.setCursor(0,1);
      lcd.print("3  5  7  10  OK");
      }
    if (!digitalRead(11)) {
      quant = 5;
      lcd.clear();
      lcd.print("O  X  O  O");
      lcd.setCursor(0,1);
      lcd.print("3  5  7  10  OK");
      }
    if (!digitalRead(12)) {
      quant = 3;
      lcd.clear();
      lcd.print("X  O  O  O");
      lcd.setCursor(0,1);
      lcd.print("3  5  7  10  OK");
      }
    delay(1);
  } while (digitalRead(8));
  lcd.clear();
  lcd.print(quant);
  lcd.print(" repeats");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("START IN");
  lcd.print(" 3");
  delay(1000);
  lcd.print(" 2");
  delay(1000);
  lcd.print(" 1");
  delay(1000);
  lcd.clear();
  
  for (int i = 1; i <= quant; i++) {                // testing the time of reaction i times
    delay(1000);
    int num = random(3, 8);                         // random selection of diode that will light up
    digitalWrite(num, 1);
    unsigned int start0 = millis();
    do                                              // waiting for user presses the button
    {
      delay(1);
    } while ( digitalRead(num + 5) );           // each button must be joined to pin with number, equals pin number of corresponding diode + 5
    unsigned int result0 = millis() - start0;   // time when buttton was pressed minus time when countdown was started
    result = result + result0;
    lcd.print(i);
    lcd.print(". ");
    lcd.print(result0);
    lcd.print(" ms");
    Serial.println(result0);
    delay(1000);
    digitalWrite(num, 0);
    lcd.clear();
  }
  
  delay(1000);
  lcd.print("FINAL RESULT:");
  lcd.setCursor(0,1);
  lcd.print(result/quant);  // final result is average of all results, "result" is summary of all results
  lcd.print(" ms");
  delay(1500);
  lcd.clear();
  lcd.print(result/quant);
  lcd.print(" ms / RESET");
  lcd.setCursor(0,1);
  lcd.print("WITH ANY BUTTON");

  Serial.println(0);
}

void loop()
{ 
  void(* resetFunc) (void) = 0;
  
  if (!digitalRead(8) || !digitalRead(9) || !digitalRead(10) || !digitalRead(11) || !digitalRead(12)) {  // restart condition
  resetFunc();
  }
  delay(50);
}