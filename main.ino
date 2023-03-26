#define BLINKER_BLE
#define servoPin 32
#define motorA1Pin 26
#define motorA2Pin 27
#define motorB1Pin 33
#define motorB2Pin 25

#include <Blinker.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

BlinkerButton Button1("leftUP");
BlinkerButton Button2("leftSTOP");
BlinkerButton Button3("leftDOWN");
BlinkerButton Button4("rightUP");
BlinkerButton Button5("rightSTOP");
BlinkerButton Button6("rightDOWN");
BlinkerSlider Slider("servo");

int counter = 0;

void button1_callback(const String& state) {
  climbL(1);
}
void button2_callback(const String& state) {
  climbL(0);
}
void button3_callback(const String& state) {
  climbL(-1);
}

void button4_callback(const String& state) {
  climbR(1);
}
void button5_callback(const String& state) {
  climbR(0);
}
void button6_callback(const String& state) {
  climbR(-1);
}

void slider_callback(int32_t value) {
  ledcWrite(8, value);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(17, 16);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  BLINKER_DEBUG.stream(Serial);

  ledcSetup(8, 50, 16);
  ledcAttachPin(servoPin, 8);
  ledcWrite(8, 4750);

  pinMode(motorA1Pin, OUTPUT);
  pinMode(motorA2Pin, OUTPUT);
  pinMode(motorB1Pin, OUTPUT);
  pinMode(motorB2Pin, OUTPUT);
  digitalWrite(motorA1Pin, LOW);
  digitalWrite(motorA2Pin, LOW);
  digitalWrite(motorB1Pin, LOW);
  digitalWrite(motorB2Pin, LOW);

  Blinker.begin();

  Button1.attach(button1_callback);
  Button2.attach(button2_callback);
  Button3.attach(button3_callback);
  Button4.attach(button4_callback);
  Button5.attach(button5_callback);
  Button6.attach(button6_callback);
  Slider.attach(slider_callback);
}

void loop() {
  mpu6050.update();
  Blinker.run();
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.println(mpu6050.getAngleY());
}

void climbL(int L) {
  if (L > 0) {
    digitalWrite(motorA1Pin, HIGH);
    digitalWrite(motorA2Pin, LOW);
  } else if (L == 0) {
    digitalWrite(motorA1Pin, LOW);
    digitalWrite(motorA2Pin, LOW);
  } else {
    digitalWrite(motorA1Pin, LOW);
    digitalWrite(motorA2Pin, HIGH);
  }
}

void climbR(int R) {
  if (R < 0) {
    digitalWrite(motorB1Pin, HIGH);
    digitalWrite(motorB2Pin, LOW);
  } else if (R == 0) {
    digitalWrite(motorB1Pin, LOW);
    digitalWrite(motorB2Pin, LOW);
  } else {
    digitalWrite(motorB1Pin, LOW);
    digitalWrite(motorB2Pin, HIGH);
  }
}
