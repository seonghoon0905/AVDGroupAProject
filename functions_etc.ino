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
 * @brief Unity로부터 수신된 데이터를 처리합니다.
 * (명령어 예시: "S 1" -> 1번 효과음 재생)
 */
void checkIncomingData() {
  // 데이터가 들어왔는지 확인
  if (BTSerial.available()) {
    
    // 1. 줄바꿈 문자('\n')가 나올 때까지 문자열 전체를 읽음
    String inputString = BTSerial.readStringUntil('\n'); 
    inputString.trim(); // 앞뒤 공백 제거 (혹시 모를 오류 방지)

    // 2. 데이터 해석 (Parsing)
    // 만약 문자열이 'S'로 시작한다면? (Sound 명령)
    if (inputString.startsWith("S")) {
      
      // "S " 다음 부분(인덱스 2부터 끝까지)을 잘라내서 숫자로 변환
      // 예: "S 1" -> "1" -> 1
      int soundType = inputString.substring(2).toInt();
      
      // 3. 우리가 만든 스피커 함수 호출!
      playSoundEffect(soundType);
      
      // (디버깅용: PC 모니터에 출력)
      Serial.print("Unity Command Recieved: Sound Type ");
      Serial.println(soundType);
    }
  }
}