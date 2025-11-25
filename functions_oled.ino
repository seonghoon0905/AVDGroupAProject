/**
 * @name initOLED
 * @brief OLED를 초기화하고 로고를 띄웁니다.
 */
void initOLED() {
  // 주소 0x3C로 시작 (대부분의 0.96인치 모듈)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    return;
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // 부팅 메시지
  display.setCursor(10, 10);
  display.println(F("Arduino Controller"));
  display.setCursor(10, 30);
  display.println(F("Initializing..."));
  display.display();
  
  delay(1000); // 로고 잠시 보여줌
}

/**
 * @name updateScreen
 * @brief 현재 컨트롤러의 상태 정보를 화면에 그립니다.
 */
void updateScreen() {
  display.clearDisplay(); // 화면 지우기 (필수)

  // 1. 타이틀 바 (상단)
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(F("CONTROLLER"));

  // 2. 연결 상태 표시 (우측 상단)
  display.setCursor(80, 0);
  if (isBtConnected) {
    display.print(F("[CONN]")); // 연결됨
  } else {
    display.print(F("[DISC]")); // 끊김
  }
  
  // 구분선
  display.drawLine(0, 10, 128, 10, WHITE);

  // 3. 센서/버튼 상태 표시 (본문)
  display.setCursor(0, 15);
  
  // 터치 센서 상태
  display.print(F("Touch: "));
  if (digitalRead(TOUCH_PIN) == HIGH) display.println(F("ON"));
  else display.println(F("OFF"));

  // 조이스틱 값 (간략히)
  display.print(F("Joy X:")); display.print(analogRead(A0));
  display.print(F(" Y:")); display.println(analogRead(A1));

  // 4. 하단 상태바 (배터리 등 나중에 활용)
  display.setCursor(0, 50);
  if (isBtConnected) {
    display.print(F("Ready to Play!"));
  } else {
    display.print(F("Waiting Unity..."));
  }

  display.display(); // ★ 그리기 명령 전송 (이게 있어야 보임)
}