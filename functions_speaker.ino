// ---------------------------------
// 스피커 관리 함수들
// ---------------------------------

/**
 * @name initSpeaker
 * @brief 스피커 초기화 및 시작음 재생
 */
void initSpeaker() {
  pinMode(SPEAKER_PIN, OUTPUT);
}

/**
 * @name playSoundEffect
 * @brief 검증된 주파수 대역(440~1000Hz)을 사용한 효과음 재생
 * @param type 효과음 번호 (1:시작, 2:클릭, 3:경고, 4:성공)
 */
void playSoundEffect(int type) {
  switch (type) {
    case 1: // [시작음] "띠-딩" (안정적인 도 -> 미)
      // 523Hz (높은 도)
      tone(SPEAKER_PIN, 523, 150); 
      delay(150); 
      noTone(SPEAKER_PIN);

      // 659Hz (높은 미)
      tone(SPEAKER_PIN, 659, 300); 
      delay(300); 
      noTone(SPEAKER_PIN);
      break;

    case 2: // [클릭/터치] "톡" 
      // 440Hz (라)
      tone(SPEAKER_PIN, 440, 50); 
      delay(50); 
      noTone(SPEAKER_PIN);
      break;

    case 3: // [경고/충돌]
      // 392Hz (솔)
      tone(SPEAKER_PIN, 392, 150); 
      delay(150); 
      noTone(SPEAKER_PIN);
      
      delay(100); // 소리 사이 간격

      tone(SPEAKER_PIN, 392, 150); 
      delay(150); 
      noTone(SPEAKER_PIN);
      break;

    case 4: // [성공/아이템] "띠로리~" (도-미-솔)
      // 523Hz (도)
      tone(SPEAKER_PIN, 523, 100); delay(100); noTone(SPEAKER_PIN);
      // 659Hz (미)
      tone(SPEAKER_PIN, 659, 100); delay(100); noTone(SPEAKER_PIN);
      // 784Hz (솔)
      tone(SPEAKER_PIN, 784, 200); delay(200); noTone(SPEAKER_PIN);
      break;
      
    default:
      noTone(SPEAKER_PIN);
      break;
  }
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