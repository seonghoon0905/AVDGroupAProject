// ---------------------------------
// 스피커 관리 함수들
// ---------------------------------

/**
 * @name initSpeaker
 * @brief 스피커를 초기화하고 시작 알림음을 울립니다.
 */
void initSpeaker() {
  pinMode(SPEAKER_PIN, OUTPUT);
  Serial.println("Speaker Initialized (D12)");
  
  // 시작 알림음 (띠리링!)
  playSoundEffect(1); 
}

/**
 * @name playTone
 * @brief 특정 주파수의 소리를 지정된 시간만큼 재생합니다.
 * @param frequency 주파수 (Hz)
 * @param duration 지속 시간 (ms)
 */
void playTone(int frequency, int duration) {
  tone(SPEAKER_PIN, frequency, duration);
}

/**
 * @name playSoundEffect
 * @brief 상황에 맞는 효과음을 재생합니다.
 * @param type 효과음 번호 (1:시작, 2:클릭, 3:경고/충돌, 4:성공)
 */
void playSoundEffect(int type) {
  switch (type) {
    case 1: // [시작음] 띠리링~ (상승음)
      tone(SPEAKER_PIN, 1319, 100); delay(100); // 미 (E6)
      tone(SPEAKER_PIN, 1568, 100); delay(100); // 솔 (G6)
      tone(SPEAKER_PIN, 2093, 200);             // 도 (C7)
      break;

    case 2: // [클릭음] 틱! (짧고 높은음)
      tone(SPEAKER_PIN, 1000, 50); 
      break;

    case 3: // [경고/충돌] 삐- 삐- (단속음)
      tone(SPEAKER_PIN, 500, 100); delay(150);
      tone(SPEAKER_PIN, 500, 100);
      break;

    case 4: // [성공/아이템] 띠-딩!
      tone(SPEAKER_PIN, 1568, 100); delay(100); // 솔
      tone(SPEAKER_PIN, 2093, 200);             // 도
      break;
      
    default:
      noTone(SPEAKER_PIN); // 소리 끄기
      break;
  }
}