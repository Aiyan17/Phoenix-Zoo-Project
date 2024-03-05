#include <Servo.h>

Servo myservo;
int buttonPin = 12;
int ultrasonicTrigPin = 7;
int ultrasonicEchoPin = 6;
int ledPins[] = {8, 9, 10, 11}; // LEDs
int timeToRoll = 2000; // Time to roll in milliseconds
int distanceThreshold = 10; // Distance in centimeters to activate

void setup() {
  myservo.attach(3);
  pinMode(buttonPin, INPUT);
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  if (digitalRead(buttonPin) == HIGH || isObjectDetected()) {
    activateFoodDispenser();
  }
}

boolean isObjectDetected() {
  digitalWrite(ultrasonicTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin, LOW);

  long duration = pulseIn(ultrasonicEchoPin, HIGH);
  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  return (distance < distanceThreshold);
}

void activateFoodDispenser() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], HIGH); // Turn on all LEDs
  }

  myservo.write(180); // Move servo to release food
  delay(2000); // Wait for 2 seconds (adjust as needed)
  myservo.write(0); // Return servo to the initial position
  delay(1000); // Wait for 1 second (adjust as needed)

  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW); // Turn off all LEDs
  }

  delay(timeToRoll); // Wait for the specified time before allowing another activation
}


