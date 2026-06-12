/*************************************************
 * ESP32 Smart Obstacle Detection & Warning System
 * Author: Milad Mohseni
 *
 * Sensor:
 * IR-08H Obstacle Sensor
 *
 * Features:
 * -----------------------------------------
 * OLED Dashboard
 * Obstacle Counter
 * Detection Timer
 * Status LEDs
 * Audible Alarm
 * Event-Based Detection
 *************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =====================================
// OLED
// =====================================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1);

// =====================================
// PIN DEFINITIONS
// =====================================

#define OBSTACLE_SENSOR 27

#define GREEN_LED 15
#define ORANGE_LED 2
#define RED_LED 4

#define BUZZER 14

// =====================================
// VARIABLES
// =====================================

unsigned long obstacleCounter = 0;

bool previousObstacleState = false;

unsigned long obstacleStartTime = 0;

unsigned long obstacleDuration = 0;

// =====================================
// SETUP
// =====================================

void setup()
{
  Serial.begin(115200);

  pinMode(OBSTACLE_SENSOR, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  Wire.begin(21,22);

  // Passive buzzer PWM

  ledcAttach(BUZZER, 1000,8);

  // OLED

  if(!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C))
  {
    while(true);
  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(5,20);
  display.println("IR-08H");

  display.display();

  delay(2000);
}

// =====================================
// LOOP
// =====================================

void loop()
{
  int obstacleState =
      digitalRead(OBSTACLE_SENSOR);

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0,0);
  display.println("SMART OBSTACLE SYS");

  // =====================================
  // OBSTACLE DETECTED
  // =====================================

  if(obstacleState == LOW)
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(ORANGE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);

    // Loud tone

    ledcWriteTone(BUZZER, 1000);

    // New obstacle event

    if(previousObstacleState == false)
    {
      obstacleCounter++;

      obstacleStartTime = millis();

      previousObstacleState = true;
    }

    obstacleDuration =
        (millis() - obstacleStartTime)
        / 1000;

    display.setCursor(0,15);
    display.println("OBSTACLE!");

    display.setCursor(0,30);
    display.print("Count: ");
    display.println(obstacleCounter);

    display.setCursor(0,45);
    display.print("Time: ");
    display.print(obstacleDuration);
    display.println("s");

    Serial.println("OBSTACLE DETECTED");
  }

  // =====================================
  // CLEAR AREA
  // =====================================

  else
  {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(ORANGE_LED, LOW);
    digitalWrite(RED_LED, LOW);

    ledcWriteTone(BUZZER, 0);

    previousObstacleState = false;

    obstacleDuration = 0;

    display.setCursor(0,15);
    display.println("AREA CLEAR");

    display.setCursor(0,30);
    display.print("Count: ");
    display.println(obstacleCounter);

    display.setCursor(0,45);
    display.println("Monitoring");

    Serial.println("AREA CLEAR");
  }

  display.display();

  delay(100);
}