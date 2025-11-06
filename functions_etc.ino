/**
 * @name initSerial
 * @brief PC 시리얼 모니터와 블루투스(SoftwareSerial)의 통신 속도를 초기화합니다.
 */
void initSerial() {
  Serial.begin(9600);   // PC 디버깅용 (9600)
  BTSerial.begin(9600); // 블루투스 전송용 (SoftwareSerial은 9600이 안정적)
  Serial.println("Arduino Ready! RAW Data Sender. BT=9600");
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