#include <BleMouse.h>
#include <Adafruit_MPU6050.h>

#define LEFTBUTTON 19
#define RIGHTBUTTON 18
#define SPEED 10

Adafruit_MPU6050 mpu;
BleMouse bleMouse;

bool sleepMPU = true;
long lastClickTime = 0;
const int debounceDelay = 50; // 50ms debounce delay

void setup() {
  Serial.begin(115200);

  pinMode(LEFTBUTTON, INPUT_PULLUP);
  pinMode(RIGHTBUTTON, INPUT_PULLUP);

  bleMouse.begin();

  delay(1000);

  // Try to initialize MPU!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Sleep MPU till Bluetooth is connected as it seems to interrupt connection
  mpu.enableSleep(sleepMPU);
}

void loop() {
  if (bleMouse.isConnected()) {
    if (sleepMPU) {
      delay(3000);
      Serial.println("MPU6050 awakened!");
      sleepMPU = false;
      mpu.enableSleep(sleepMPU);
      delay(500);
    }

    // Handle mouse movement
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    bleMouse.move(g.gyro.z * -SPEED, g.gyro.x * -SPEED);

    // Handle button clicks with debounce
    unsigned long currentMillis = millis();

    if (!digitalRead(LEFTBUTTON) && (currentMillis - lastClickTime > debounceDelay)) {
      Serial.println("Left click");
      bleMouse.click(MOUSE_LEFT);
      lastClickTime = currentMillis;
    }

    if (!digitalRead(RIGHTBUTTON) && (currentMillis - lastClickTime > debounceDelay)) {
      Serial.println("Right click");
      bleMouse.click(MOUSE_RIGHT);
      lastClickTime = currentMillis;
    }
  }
}
