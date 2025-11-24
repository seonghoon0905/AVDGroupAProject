/**
 * @name sendJoystickData
 * @brief 조이스틱 값을 "J x,y,sw" 양식으로 블루투스 전송
 */
void sendJoystickData() {
  // 1. 아날로그 값 2개 읽기 (0 ~ 1023)
  int joyX = analogRead(joyX_Pin);
  int joyY = analogRead(joyY_Pin);

  // 2. 디지털 값 1개 읽기 (INPUT_PULLUP: 안 누르면 1, 누르면 0)
  int joySW = digitalRead(joySW_Pin);

  // 3. J:x,y,button 형식으로 블루투스 전송
  Serial.print("J "); // 키: "J"
  Serial.print(joyX);
  Serial.print(",");
  Serial.print(joyY);
  Serial.print(",");
  Serial.println(joySW); 
}