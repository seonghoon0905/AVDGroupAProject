// ---------------------------------
// 터치 센서 관리 함수들
// ---------------------------------

/**
 * @name initTouch
 * @brief 터치 센서 핀을 입력 모드로 설정합니다.
 */

void initTouch() {
  pinMode(TOUCH_PIN, INPUT);
  Serial.println("Touch Sensor Initialized (D10)");
}

/**
 * @name sendTouchData
 * @brief 터치 센서 상태를 "T 1" 또는 "T 0"으로 블루투스 전송
 */
void sendTouchData() {
  // 터치 센서 읽기 (터치하면 HIGH(1), 안 하면 LOW(0))
  int touchState = digitalRead(TOUCH_PIN);

  // 1. 블루투스로 전송
  BTSerial.print("T "); // 키: "T"
  BTSerial.println(touchState); // 값: 1 or 0 (줄바꿈 포함)
  
  // 2. PC 시리얼 모니터로 디버깅 (확인용)
  // (데이터가 너무 많아 시리얼 모니터가 지저분하면 주석 처리하세요)
  
  Serial.print("T ");
  Serial.println(touchState);
}