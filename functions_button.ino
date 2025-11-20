/**
 * @name initButtons
 * @brief 버튼 핀 3개를 INPUT_PULLUP 모드로 초기화합니다.
 */
void initButtons() {
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
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
  
  // X 전송
  BTSerial.print("X"); 
  if (digitalRead(BUTTON_PIN_1) == LOW) {
    BTSerial.println("1");
  } else {
    BTSerial.println("0");
  }

  // Y 전송
  BTSerial.print("Y");
  if (digitalRead(BUTTON_PIN_2) == LOW) {
    BTSerial.println("1");
    
  } else {
    BTSerial.println("0");
  }

  // B 전송
  BTSerial.print("B")
  if (digitalRead(BUTTON_PIN_3) == LOW) {
    BTSerial.println("1");
  } else {
    BTSerial.println("0");
  }

  // A 전송
  BTSerial.print("A");
  if (digitalRead(BUTTON_PIN_4) == LOW) {
    BTSerial.println("1");

  } else {
    BTSerial.println("0");
  }
}