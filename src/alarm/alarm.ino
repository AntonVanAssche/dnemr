// Defining the pins.
#define trigPin 2       // Trigger pin of the ultrasonic sensor.
#define echoPin 3       // Echo pin of the ultrasonic sensor.
#define buzzPin 4       // Buzzer pin.
#define ledPin 5        // LED pin.
#define buttonPin 6     // Button pin.

// Defining the variables.
long duration;          // Variable for the duration of sound wave travel.
float distance;         // Variable for the distance measurement.
int currentState;       // Variable for storing the current state.
int previousState;      // Variable for storing the previous state.
String toggle = "off";  // Variable for storing the toggle state.

void setup() {
   // Start serial communication at 9600 bps.
   Serial.begin(9600);

   // Setting the `trigPin`, `buzzPin` and `ledPin` as outputs.
   pinMode(trigPin, OUTPUT);
   pinMode(buzzPin, OUTPUT);
   pinMode(ledPin, OUTPUT);

   // Setting the `echoPin` and `buttonPin` as inputs.
   pinMode(echoPin, INPUT);
   pinMode(buttonPin, INPUT);

   // Setting the current button state.
   currentState = digitalRead(buttonPin);
}

void playSound() {
   for(int i=0; i<80; i++) {
      // Power the buzzer for 1 ms.
      digitalWrite(buzzPin, HIGH);
      delay(1);

      // Turn off the buzzer for 1 ms.
      digitalWrite(buzzPin, LOW);
      delay(1);
   }
}

void blinkLED() {
   // Power the LED for 1 s.
   digitalWrite(ledPin, HIGH);
   delay(100);

   // Turn off the LED for 1 s.
   digitalWrite(ledPin, LOW);
   delay(100);
}

float getDistance() {
   // Set trigPin output to LOW.
   digitalWrite(trigPin, LOW);

   // Wait for 2 microseconds.
   delayMicroseconds(2);

   // Set trigPin output to HIGH.
   digitalWrite(trigPin, HIGH);

   // Wait for 10 microseconds.
   delayMicroseconds(10);

   // Set trigPin output to LOW.
   digitalWrite(trigPin, LOW);

   // Read echoPin input.
   duration = pulseIn(echoPin, HIGH);

   // Calculate distance between the sensor and the object.
   distance = (duration / 2) * 0.034;

   // Print the distance.
   return distance;
}

void loop() {
   // Save the previous button state.
   previousState = currentState;

   // Read the current button state.
   currentState = digitalRead(buttonPin);

   // If the current state is different from the previous state, then the button has been pressed.
   if(previousState == HIGH && currentState == LOW) {
      // If the toggle state is "on", then turn it off.
      // When the toggle state is "off", then turn it on.
      // We need to use the `equals()` method because we are comparing 2 strings with each other.
      if (toggle.equals("on")) {
         toggle = "off";
         Serial.println("Alarm: off");
      } else {
         toggle = "on";
         Serial.println("Alarm: on");
      }
   }

   // If the distance is less or equal to 20 cm
   // and the toggle state is "on", trigger the alarm.
   // else set the output of the buzzer and LED to LOW.
   if (getDistance() <= 20 && toggle == "on") {
      // Call the `playSound` method.
      playSound();

      // Call the `blinkLED` method.
      blinkLED();

      Serial.println("Alarm triggered!");
   } else {
      // Turn off the buzzer and the LED.
      digitalWrite(buzzPin, LOW);
      digitalWrite(ledPin, LOW);

      // Serial.println();
   }

   // Wait for 1 s.
   delay(100);
}

