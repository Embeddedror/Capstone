#include <LiquidCrystal.h>
#include <Servo.h>
#include <Stepper.h>

#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
#define STEPS 256

Servo servo2;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // LCD 패널에 사용되는 핀 설정
int lcd_key = 0;
int adc_key_in = 0;
Stepper lowerstepper(STEPS, 3, 2, 1, 0); // 스텝모터에 연결된 핀

int num = 40;  // 초기 값 설정

int read_LCD_buttons() {
  adc_key_in = analogRead(0);  // 키패드 값을 받음
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50) return btnRIGHT;
  if (adc_key_in < 195) return btnUP;
  if (adc_key_in < 380) return btnDOWN;
  if (adc_key_in < 555) return btnLEFT;
  if (adc_key_in < 790) return btnSELECT;
  return btnNONE;
}

void setup() {
  lcd.begin(16, 2);            // 라이브러리 시작
  lcd.setCursor(0, 0);         // 첫 번째 줄 LCD 커서 위치 설정
  lcd.print("Cut: 8");         // 첫 번째 줄에 출력
  lcd.setCursor(0, 1);         // 두 번째 줄 LCD 커서 위치 설정
  lcd.print("number: ");        // 두 번째 줄에 출력
  servo2.attach(11); // 서보모터에 연결된 핀
  servo2.write(0); // 서보모터 각도 초기화
}

void loop() {
  lcd.setCursor(9, 1);         // 두 번째 줄 LCD 커서 위치 설정
  lcd.print(num);              // num 값 출력
  lcd_key = read_LCD_buttons(); // 키패드 값을 읽음
  switch (lcd_key) {            // 키패트 이름 출력
    case btnRIGHT: {
      num = 60;  // RIGHT 버튼을 누르면 num을 60으로 설정
      break;
    }
    case btnLEFT: {
      num = 40;  // LEFT 버튼을 누르면 num을 40으로 설정
      break;
    }
    case btnUP: {
      num++;  // UP 버튼을 누르면 num이 1 증가
      delay(500);
      break;
    }
    case btnDOWN: {
      num--;  // DOWN 버튼을 누르면 num이 1 감소
      delay(500);
      break;
    }
    case btnSELECT: {
       for (; num > 0; num--) {
       servo2.write(180);   // 서보모터 180도 회전
       delay(500);
       servo2.write(0);     // 서보모터 0도로 돌아옴
       lcd.print(" ");
       lcd.setCursor(9, 1); // 두 번째 줄 LCD 커서 위치 설정
       lcd.print(num);      // 숫자 출력
       delay(500);
       lowerstepper.setSpeed(50);  // 스텝모터의 속도 설정
       lowerstepper.step(STEPS);    // 스텝모터를 지정한 각도만큼 회전
       delay(500);
  }
  break;  // for문이 끝난 후 빠져나가기
}
    case btnNONE: {
      // 아무 버튼도 눌리지 않았을 때 추가 동작을 수행할 수 있음
      break;
    }
  }
}