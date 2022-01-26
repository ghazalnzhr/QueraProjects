/* code for printing SRF results to LCD */
#define PIN_TRIG 3
#define PIN_ECHO 4

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop() {
  // Start a new measurement:
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // Read the result:
  float duration = pulseIn(PIN_ECHO, HIGH);
  float distance = (duration / 2) * 0.0344;
  lcd.setCursor(0,0);
  lcd.print("Distance in CM: ");
  lcd.setCursor(0,1);
  lcd.print(distance);
  delay(1000);
}
