#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>

// -----------------------------------------------------
// Adjust these to match your Wi-Fi and camera server
// -----------------------------------------------------
const char* ssid     = "peterzhu";
const char* password = "peterzhu1021";

// Replace this IP with whatever the ESP32-CAM prints in its Serial Monitor
String cameraServerURL = "http://192.168.1.123/";

// -----------------------------------------------------
// Servo configuration
// -----------------------------------------------------
Servo myservo;
int servoPin = 13;   // Attach servo signal line here
int pos = 0;         // For servo sweep

void setup() {
  Serial.begin(115200);

  // 1. Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("Motor board IP address: ");
  Serial.println(WiFi.localIP());

  // 2. Initialize the servo
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  myservo.setPeriodHertz(50);              // Standard 50 Hz servo
  myservo.attach(servoPin, 500, 2400);     // Min/Max pulse width in microseconds
}

void loop() {
  // 3. Periodically fetch the "flag" from the ESP32-CAM
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(cameraServerURL);           // e.g., "http://192.168.1.123/"
    int httpResponseCode = http.GET();     // Send the GET request

    if (httpResponseCode > 0) {
      // 4. Read the camera's response (should be "0" or "1")
      String payload = http.getString();
      Serial.println("Camera response: " + payload);

      int detectionFlag = payload.toInt(); // Convert string to integer

      // 5. If the flag is 1, activate the servo
      if (detectionFlag == 1) {
        Serial.println("Pigeon detected! Activating servo...");
        
        // Sweep from 0 to 35 degrees
        for (pos = 0; pos <= 35; pos++) {
          myservo.write(pos);
          delay(15);
        }
        delay(3000);

        // Sweep back from 35 to 0
        for (pos = 35; pos >= 0; pos--) {
          myservo.write(pos);
          delay(15);
        }
      }
      else {
        Serial.println("No pigeon detected.");
      }
    }
    else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
  else {
    Serial.println("WiFi disconnected...");
  }

  // 6. Adjust the polling rate as needed (currently 2 seconds)
  delay(2000);
}
