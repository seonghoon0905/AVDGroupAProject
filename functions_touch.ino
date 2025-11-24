// ---------------------------------
// 터치 센서 관리 함수들
// ---------------------------------

/**
 * @name initTouch
 * @brief 터치 센서 핀을 입력 모드로 설정합니다.
 */

void initTouch() {
  pinMode(TOUCH_PIN, INPUT);
}

/**
 * @name sendTouchData
 * @brief 터치 센서 상태를 "T 1" 또는 "T 0"으로 블루투스 전송
 */
void sendTouchData() {
  // 터치 센서 읽기 (터치하면 HIGH(1), 안 하면 LOW(0))
  int touchState = digitalRead(TOUCH_PIN);

  // 1. 블루투스로 전송
  Serial.print("T "); // 키: "T"
  Serial.println(touchState); // 값: 1 or 0 (줄바꿈 포함)
}