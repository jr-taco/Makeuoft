#include "esp_camera.h"
#include <ESP32Servo.h>  

// ===========================
// Enter your WiFi credentials
// ===========================

Servo myservo;  // Create a Servo object
int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 13;

int pigeonTrue=1;

void setup() {
  // Serial.begin(115200);
  // Serial.setDebugOutput(true);
  // Serial.println();
//  myServo.attach(16);  
  Serial.begin(115200);
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    myservo.setPeriodHertz(50);    // standard 50 hz servo
    myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
    // using default min/max of 1000us and 2000us
    // different servos may require different min/max settings
    // for an accurate 0 to 180 sweep

}
void loop() {
    // myServo.write(0);   // Move servo to 0° (closed)
    // delay(2000);

    // myServo.write(90);  // Move servo to 90° (half-open)
    // delay(2000);
    pigeonTrue = Serial.parseInt();
    if(pigeonTrue==1){
      Serial.println("hi");
      for (pos = 0; pos <= 35; pos += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);    // tell servo to go to position in variable 'pos'
          delay(15);             // waits 15ms for the servo to reach the position
      }
 //     flag=0;
      delay(3000);
//      Serial.println("second hi");
      for (pos = 35; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);    // tell servo to go to position in variable 'pos'
        delay(15);             // waits 15ms for the servo to reach the position
      }
    }
    else {
      Serial.println("no pigeon");
    }
    
   // delay(3000);

    // if(flag==0){
    //   Serial.println("second hi");
    //   for (pos = 35; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    //     myservo.write(pos);    // tell servo to go to position in variable 'pos'
    //     delay(15);             // waits 15ms for the servo to reach the position
    //   }
    //   flag=1;
    // }


}