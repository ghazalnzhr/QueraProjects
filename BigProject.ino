// https://wokwi.com/arduino/projects/321493786668565075
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/* LCD Setup */
LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

/* Button steup */
const int buttonPin = 13;    // the number of the pushbutton pin

int buttonPushCounter;
int buttonState;
int lastButtonState;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastButtonPushed = 0;  // the last time the output pin was toggled
unsigned long patience = 50;    // the debounce time; increase if the output flickers


void setup()
{
  /* LCD Setup */
  lcd.init();                  
  lcd.init();
  // Print the menu to the LCD
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Waves 1");
  lcd.setCursor(7,0);
  lcd.print("Jumper 2");
  lcd.setCursor(0, 1);
  lcd.print("Timer 3");
  lcd.setCursor(7, 1);
  lcd.print("Info 4");

  /* Button Setup */
  pinMode(buttonPin, INPUT);

  /* DEBUG */
  Serial.begin(9600);
}


void loop()
{
  /* lcd.setCursor(5, 0);
  lcd.print("!");
  delay(300);
  lcd.clear(); */

  /* Button keeping */
  // read the state of the button
  int buttonState = digitalRead(buttonPin);

    // Compare the previous state of the push button to its new state
  if (buttonState != lastButtonState) { // if the state changed, due to noise or pressing:
    lastButtonPushed = millis();
    handleButtonPressed(buttonState);
  }
  lastButtonState = buttonState;


  if (buttonPushCounter == 1) {
  if ((millis() - lastButtonPushed) > patience) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
      lcd.clear();
      lcd.print("Waves!");
    } else if (buttonPushCounter == 2) {
    lcd.setCursor(13, 0);
    lcd.print("*");
  }
  }

}

void handleButtonPressed(int buttonState) {
    // If the state has changed, increment the counter
    if (buttonState == HIGH) {
      // If the current state is HIGH, then the button went from off to on
      buttonPushCounter++; // Increment
      Serial.println("on");
      Serial.println("Number of pushes:");
      Serial.println(buttonPushCounter);
    } else {
      // If the button state was LOW, then the push button is off
      Serial.println("off");
    } // Wait for 50 ms to avoid bouncing
    delay(50);
}
