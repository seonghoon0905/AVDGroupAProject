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

// ---------------------------------
// 3. 사용자 정의 함수 (기능 블록)
// ---------------------------------

/**
 * @name initSerial
 * @brief PC 시리얼 모니터와 블루투스(SoftwareSerial)의 통신 속도를 초기화합니다.
 */
void initSerial() {
  Serial.begin(9600);   // PC 디버깅용 (9600)
  BTSerial.begin(9600); // 블루투스 전송용 (SoftwareSerial은 9600이 안정적)
  Serial.println("Arduino Ready! RAW Data Sender. BT=9600");
}

// --- 전역 변수 (핀 번호) ---
// (BTSerial, mpu 등은 동일...)
const int BUTTON_PIN_1 = 5;  
const int BUTTON_PIN_2 = 6; 
const int BUTTON_PIN_3 = 7; 


// ---------------------------------
// 3. 사용자 정의 함수 (기능 블록)
// ---------------------------------

/**
 * @name initButtons
 * @brief 버튼 핀 3개를 INPUT_PULLUP 모드로 초기화합니다.
 */
void initButtons() {
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  Serial.println("Buttons Initialized");
}

/**
 * @name sendButtonData
 * @brief 버튼 3개의 상태를 "B[번호] ON/OFF" 양식으로 블루투스 전송
 */
void sendButtonData() {
  // 1. 버튼 값 읽기 (INPUT_PULLUP)
  // - 안 누르면 HIGH(1)
  // - 누르면 LOW(0)
  
  // 버튼 1 전송
  BTSerial.print("B1 "); // 키: "B1"
  if (digitalRead(BUTTON_PIN_1) == LOW) {
    BTSerial.println("1");

  } else {
    BTSerial.println("0");
  }

  // 버튼 2 전송
  BTSerial.print("B2 "); // 키: "B2"
  if (digitalRead(BUTTON_PIN_2) == LOW) {
    BTSerial.println("1");
  } else {
    BTSerial.println("0");
  }

  // 버튼 3 전송
  BTSerial.print("B3 "); // 키: "B3"
  if (digitalRead(BUTTON_PIN_3) == LOW) {
    BTSerial.println("1");
  } else {
    BTSerial.println("0");
  }
}

/**
 * @name initMPU6050
 * @brief MPU6050 센서를 찾고, 범위를 설정하여 초기화합니다.
 */
void initMPU6050() {
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) { delay(10); }
  }
  Serial.println("MPU6050 Found!");
  
  // 센서 범위 설정
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

/**
 * @name sendSensorData
 * @brief MPU6050에서 RAW 6축 값을 읽어, 정해진 양식("G ...")으로 블루투스 전송
 */
void sendSensorData() {
  // 1. 센서 값 읽기 (RAW 데이터)
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // 2. 블루투스로 데이터 전송 (새로운 양식: "G [값6개]")
  BTSerial.print("G "); // 데이터 종류 'G' (Gyro+Accel)
  
  // 자이로 3축 (rad/s)
  BTSerial.print(g.gyro.x); BTSerial.print(",");
  BTSerial.print(g.gyro.y); BTSerial.print(",");
  BTSerial.print(g.gyro.z); BTSerial.print(",");
  
  // 가속도 3축 (m/s^2)
  BTSerial.print(a.acceleration.x); BTSerial.print(",");
  BTSerial.print(a.acceleration.y); BTSerial.print(",");
  BTSerial.println(a.acceleration.z); // println으로 한 줄 마무리
}

/**
 * @name checkIncomingData
 * @brief Unity로부터 수신된 데이터가 있는지 확인하고 처리합니다. (예: 진동)
 */
void checkIncomingData() {
  if (BTSerial.available()) {
    char c = BTSerial.read();
    Serial.print("Received from Unity: "); // PC 모니터에 디버깅 출력
    Serial.println(c);

    // if (c == 'V') {
    //   // 진동 모터 켜는 코드
    // }
  }
}

// ---------------------------------
// 1. 초기화 (Setup)
// ---------------------------------
void setup() {
  initButtons();
  initSerial();   // 시리얼 및 블루투스 초기화
  initMPU6050();  // MPU6050 센서 초기화
}

// --- 주기 설정 (50Hz = 20ms) ---
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
