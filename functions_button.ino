/**
 * @name initButtons
 * @brief 버튼 핀 4개를 INPUT_PULLUP 모드로 초기화합니다.
 */
void initButtons() {
  pinMode(BUTTON_PIN_X, INPUT_PULLUP);
  pinMode(BUTTON_PIN_Y, INPUT_PULLUP);
  pinMode(BUTTON_PIN_B, INPUT_PULLUP);
  pinMode(BUTTON_PIN_A, INPUT_PULLUP);
}

/**
 * @name sendButtonData
 * @brief 버튼 4개의 상태를 "B[번호] ON/OFF" 양식으로 블루투스 전송
 */
void sendButtonData() {
  // 1. 버튼 값 읽기 (INPUT_PULLUP)
  // - 안 누르면 HIGH(1)
  // - 누르면 LOW(0)
  
  // X 전송
  Serial.print("X "); 
  if (digitalRead(BUTTON_PIN_X) == LOW) {
    Serial.println("1");
  } else {
    Serial.println("0");
  }

  // Y 전송
  Serial.print("Y ");
  if (digitalRead(BUTTON_PIN_Y) == LOW) {
    Serial.println("1");
    
  } else {
    Serial.println("0");
  }

  // B 전송
  Serial.print("B ");
  if (digitalRead(BUTTON_PIN_B) == LOW) {
    Serial.println("1");
  } else {
    Serial.println("0");
  }

  // A 전송
  Serial.print("A ");
  if (digitalRead(BUTTON_PIN_A) == LOW) {
    Serial.println("1");

  } else {
    Serial.println("0");
  }
}
