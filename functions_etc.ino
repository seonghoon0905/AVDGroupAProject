/**
 * @name initSerial
 */
void initSerial() {
  Serial.begin(9600);   
}


// ==========================================
// 큐 관리 함수들 
// ==========================================

/**
 * @name receiveToQueue
 * @brief 시리얼 데이터를 읽어서 완성된 명령어를 큐에 '저장'만 합니다. (매우 빠름)
 * loop() 곳곳에서 최대한 자주 호출해주세요.
 */
void receiveToQueue() {
  while (Serial.available() > 0) {
    char c = (char)Serial.read();

    // 종료 문자('\n')가 오면 큐에 넣음
    if (c == '\n') {
      inputBuffer.trim(); 
      if (inputBuffer.length() > 0) {
        pushToQueue(inputBuffer); // 큐에 넣기
      }
      inputBuffer = ""; // 버퍼 비우기
    } 
    else {
      inputBuffer += c; // 글자 모으기
    }
  }
}

/**
 * @name pushToQueue
 * @brief 큐에 데이터를 넣는 내부 함수
 */
void pushToQueue(String cmd) {
  int nextHead = (queueHead + 1) % QUEUE_SIZE;
  
  // 큐가 꽉 차지 않았으면 저장
  if (nextHead != queueTail) {
    cmdQueue[queueHead] = cmd;
    queueHead = nextHead;
    // Serial.println("Queue Saved: " + cmd); // 디버깅용
  } else {
    // Serial.println("Queue Full! Command Dropped."); // 큐가 꽉 참
  }
}

/**
 * @name processQueue
 * @brief 큐에 쌓인 명령을 하나씩 꺼내서 '실행'합니다.
 * loop() 마지막에 한 번 호출하면 됩니다.
 */
void processQueue() {
  // 큐에 데이터가 있다면 (Head와 Tail이 다르면)
  while (queueHead != queueTail) {
    
    // 1. 큐에서 명령어 꺼내기
    String cmd = cmdQueue[queueTail];
    queueTail = (queueTail + 1) % QUEUE_SIZE; // Tail 이동
    
    // 2. 명령어 해석 및 실행 (기존 로직)
    executeCommand(cmd);
  }
}

/**
 * @name executeCommand
 * @brief 실제 기능을 수행하는 함수 (소리, 연결확인 등)
 */
void executeCommand(String cmd) {
  // --- 하트비트 (P) ---
  if (cmd == "P") {
    lastPingTime = millis();
    if (!isBtConnected) {
      isBtConnected = true;
    }
    return;
  }
  // --- 소리 재생 (S 1, S 2 ...) ---
  if (cmd.startsWith("S")) {
    int soundType = cmd.substring(2).toInt();
    playSoundEffect(soundType); 
  }
}

/**
 * @name checkConnectionStatus
 * @brief 유니티로부터 신호(P)가 끊겼는지 주기적으로 검사하는 함수
 */
void checkConnectionStatus() {
  // 1. 현재 연결되어 있다고 알고 있는 상태에서 (isBtConnected == true)
  // 2. 마지막 신호(P)를 받은 지 2초(connectionTimeout)가 지났다면?
  if (isBtConnected && (millis() - lastPingTime > connectionTimeout)) {
    
    // --- 연결 끊김 처리 시작 ---
    isBtConnected = false; // 상태 변수를 '끊김'으로 변경
    
    // (옵션) OLED가 있다면 화면 갱신
    // updateOLED("Waiting...", "Disconnected");
    
    // (옵션) 연결 끊김 알림음 (낮은 톤)
    // playTone(500, 500); 
  }
}