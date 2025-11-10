// 공동작업 테스트

// ---------------------------------
// 라이브러리 선언
// ---------------------------------
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SoftwareSerial.h> // 블루투스 라이브러리

// ---------------------------------
// 전역 변수 및 객체 선언
// ---------------------------------
SoftwareSerial BTSerial(3, 2); // RX, TX 핀 교차 연결 (3번핀->TX, 2번핀->RX)
Adafruit_MPU6050 mpu;

const int BUTTON_PIN_1 = 5;  
const int BUTTON_PIN_2 = 6; 
const int BUTTON_PIN_3 = 7; 

// ---------------------------------
// 1. 초기화 (Setup)
// ---------------------------------
void setup() {
  initButtons();
  initSerial();   // 시리얼 및 블루투스 초기화
  initMPU6050();  // MPU6050 센서 초기화
}

// --- 주기 설정 ---
unsigned long previousMillis = 0;
const long interval = 100;

// ---------------------------------
// 2. 메인 루프 (Loop)
// ---------------------------------
void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      sendSensorData(); // 6축 센서 데이터를 전송하는 함수 호출
      sendButtonData(); // 2. 버튼 3개 데이터 전송
    }
}
