// ---------------------------------
// 라이브러리 선언
// ---------------------------------
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// ==========================================
// 큐 설정
// ==========================================
#define QUEUE_SIZE 10          // 최대 10개 명령어 저장 가능
String cmdQueue[QUEUE_SIZE];   // 명령어 저장소 (문자열 배열)
int queueHead = 0;             // 데이터를 넣을 위치
int queueTail = 0;             // 데이터를 꺼낼 위치
// 수신 중인 문자열 임시 저장소
String inputBuffer = "";

// ---------------------------------
// 전역 변수 및 객체 선언
// ---------------------------------
Adafruit_MPU6050 mpu;

bool isBtConnected = false;          // 현재 연결 상태 (true: 연결됨, false: 끊김)
unsigned long lastPingTime = 0;      // 마지막으로 'P' 신호를 받은 시간
const long connectionTimeout = 2000; // 2초(2000ms) 동안 신호 없으면 끊김 처리

// 버튼 핀 추가
const int BUTTON_PIN_X = 5;  
const int BUTTON_PIN_Y = 6; 
const int BUTTON_PIN_B = 7; 
const int BUTTON_PIN_A = 8;

// ◀️ 조이스틱 핀 추가
const int joyX_Pin = A0; // X축
const int joyY_Pin = A1; // Y축
const int joySW_Pin = 9; // 버튼 (D8)

// 스피커 핀 추가
const int SPEAKER_PIN = 12; // 스피커 핀 (D8)

// 터치 센서 핀 추가
const int TOUCH_PIN = 13; // 터치 센서 핀 (D13)

// ---------------------------------
// 1. 초기화 (Setup)
// ---------------------------------
void setup() {
  initButtons();
  initSerial();   // 시리얼 및 블루투스 초기화
  initMPU6050();  // MPU6050 센서 초기화
  initSpeaker(); 
  initTouch();
}

// --- 주기 설정 ---
unsigned long previousMillis = 0;
const long interval = 100;

// ---------------------------------
// 2. 메인 루프 (Loop)
// ---------------------------------
void loop() {
    receiveToQueue();

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      sendSensorData(); // 6축 센서 데이터를 전송하는 함수 호출
      sendButtonData(); // 2. 버튼 3개 데이터 전송
      sendJoystickData();
      sendTouchData();
    }

    // 큐에 쌓인 명령 일괄 처리 (소리 재생 등)
    processQueue();
    checkConnectionStatus();
}
