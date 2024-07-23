#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Stepper.h>

#define nbPCAServo 8
#define STEPS 256 

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);
Stepper stepper1(STEPS, 9, 7, 8, 6); // 스텝모터에 연결된 핀

int switchPin = 11; // 11번 핀에 연결된 스위치

void setup() {
  Serial.begin(9600);
  Serial.println(F("Initialize System"));
  pca.begin();
  pca.setPWMFreq(50); // Analog servos run at ~50 Hz updates
  pinMode(switchPin, INPUT);
}

void loop() {
  if (digitalRead(switchPin) == HIGH) {
    for (int i = 0; i < nbPCAServo; i++) {
      servoScenario(i);
      stepperScenario();
    }

    // 원래대로 반시계 방향으로 90도 회전
    for (int i = 0; i < nbPCAServo; i++) {
      pca.setPWM(i, 0, 0); // 최소 각도
    }
    delay(1000); // 적절한 딜레이 추가
  }
}

void servoScenario(int servoIndex) {
  int initialAngle = 0; // 최소 각도
  int finalAngle = initialAngle + 90;

  pca.setPWM(servoIndex, 0, initialAngle);
  delay(1000); // 적절한 딜레이 추가
  pca.setPWM(servoIndex, 0, finalAngle);
  delay(1000); // 적절한 딜레이 추가
}

void stepperScenario() {

  stepper1.setSpeed(50);  // 스텝모터의 속도 설정
  stepper1.step(STEPS); // 스텝모터를 지정한 각도만큼 회전

  delay(1000); // 적절한 딜레이 추가
}