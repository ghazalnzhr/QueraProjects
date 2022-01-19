// Countdown in hh:mm:ss format on LCD

/* Link 
https://wokwi.com/arduino/projects/320920656704176724
*/

// Countdown variable in minutes
unsigned long baseTime = 2; // Timer is set to two minutes

/* Variables and constants */
// LCD Setup
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

/* LED Setup */
// Red
const int oneRed = 2;
const int twoRed = 3;
const int threeRed = 4;
const int fourRed = 5;

// Yellow
const int oneYellow = 13;
const int twoYellow = 14;
const int threeYellow = 15;

// Green
const int oneGreen = 16;
const int twoGreen = 17;
const int threeGreen = 18;

// Time Constants
unsigned long int secondsPerMinute = 60;
unsigned long int secondsPerHour = 60 * 60;

// Timer utils
// The format should be hh:mm:ss
unsigned long hours = 0;
unsigned long minutes = 0;
unsigned long seconds = 0;

// timeLeft in seconds
unsigned long timeLeft;
double delta;

// Buzzer utils
int buzzerPin = 6;

// Total time for delta calculation
unsigned long totalTime;

// Prevent buzzer from ringing at the start
bool firstTime = true;

/* Time convertion functions */
unsigned long secondsToMinute(unsigned long val) {
  return val / secondsPerMinute;
}

unsigned long millisToHours(unsigned long val) {
  return val / secondsPerHour;
}

// For `baseTime` convertion
unsigned long minutesToSeconds(unsigned long val) {
  return val * secondsPerMinute;
}

// Time convertor from seconds to hours, minutes and seconds
void timeConvertor(long val) {
  minutes = secondsToMinute(val);
  hours = millisToHours(val);
  seconds = val;

  printTimeToLcd(hours, minutes, seconds);
  // Set a 1 second delay
  delay(1000);
  // After one second, print the new value
  lcd.clear();
}

/* LCD Utils */
void printTimeToLcd(unsigned long hours, unsigned long minutes, unsigned long seconds) {
  // Print hours
  lcd.setCursor(0, 0);
  if (hours < 10) { // Should print a 0 on the left side of the value (to keep the format)
    lcd.print("0");
    lcd.setCursor(1, 0);
    lcd.print(hours);
  } else lcd.print(hours);
  // Print ":"
  lcd.setCursor(2, 0);
  lcd.print(":");
  // Print minutes
  lcd.setCursor(3, 0);
  if (minutes < 10) { // Should print a 0 on the left side
    lcd.print("0");
    lcd.setCursor(4, 0);
    lcd.print(minutes);
  } else lcd.print(minutes);
  // Print ":"
  lcd.setCursor(5, 0);
  lcd.print(":");
  // Print seconds
  lcd.setCursor(6, 0);
  if (seconds < 10) { // Should print a 0 on the left side
    lcd.print("0");
    lcd.setCursor(7, 0);
    lcd.print(seconds);
  } else lcd.print(seconds);

}

/* LED Management */
// Gradually light up LEDs until the time is up
void ledManager(double percentage) {
  double precentLeft = double(1) - percentage;
  Serial.println(precentLeft);
  if (precentLeft >= (double) 0.1) {
    digitalWrite(oneYellow, HIGH);
  } else if (precentLeft >= (double) 0.2) {
    digitalWrite(oneRed, HIGH);
  } else if (precentLeft >= (double) 0.3) {
    digitalWrite(oneGreen, HIGH);
  } else if (precentLeft >= (double) 0.4) {
    digitalWrite(threeYellow, HIGH);
  } else if (precentLeft >= (double) 0.5) {
    digitalWrite(twoYellow, HIGH);
  } else if (precentLeft >= (double) 0.6) {
    digitalWrite(oneYellow, HIGH);
  } else if (precentLeft >= (double) 0.7) {
    digitalWrite(oneRed, HIGH);
  } else if (precentLeft >= (double) 0.8) {
    digitalWrite(twoRed, HIGH);
  } else if (precentLeft >= (double) 0.9) {
    digitalWrite(threeRed, HIGH);
  } else if (precentLeft >= (double) 1) {
    digitalWrite(fourRed, HIGH);
  }
}

void setup() {
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
  pinMode(oneRed, OUTPUT);
  pinMode(twoRed, OUTPUT);
  pinMode(threeRed, OUTPUT);
  pinMode(fourRed, OUTPUT);
  pinMode(oneYellow, OUTPUT);
  pinMode(twoYellow, OUTPUT);
  pinMode(threeYellow, OUTPUT);
  pinMode(oneGreen, OUTPUT);
  pinMode(twoGreen, OUTPUT);
  pinMode(oneGreen, OUTPUT);
  /* for (int jj=14; jj<19;jj++){
    pinMode(jj,OUTPUT);
    }
    for (int ii=2; ii<6;ii++){
    pinMode(ii,OUTPUT);
    } */
  Serial.begin(9600);

}

void loop() {
  // Caculates the delta between the total time and the elapsed time in seconds
  timeLeft = minutesToSeconds(baseTime) - (millis() / 1000);

  // Save the first instance of the time left variable for the lcd before changing it
  // for convertion to hh:mm:ss
  totalTime = timeLeft;
  // Is the timer over?
  if (timeLeft == 0) {
    // handle the start of the timer
    if (firstTime) {
      // The buzzer has passed the inital timer setup
      firstTime = false;
    } else {
      tone(buzzerPin, 1000); // Send 1KHz sound signal...
      delay(1000); // ...for 1 sec
      noTone(buzzerPin);
      lcd.clear();
      lcd.print("Time is over");
      exit(0);
    }
  } else {
    // Converts time to hh:mm:ss
    hours = timeLeft / secondsPerHour;
    timeLeft %= secondsPerHour;

    minutes = timeLeft / secondsPerMinute;
    timeLeft %= secondsPerMinute;

    seconds = timeLeft;

    // Prints the time left to the screen
    printTimeToLcd(hours, minutes, seconds);
    lcd.setCursor(0, 1);
    lcd.print("You have: ");
    lcd.print(totalTime);
    lcd.print("s");
    // Set a 1 second delay
    delay(1000);
    // After one second, print the new value
    lcd.clear();
    delta = ((double) totalTime - (double) millis() / 1000) / (double) 120;
    //delta /= totalTime;
    ledManager(delta);
  }
}
