/**
 * @name initMPU6050
 * @brief MPU6050 센서를 찾고, 범위를 설정하여 초기화합니다.
 */
void initMPU6050() {
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) { delay(10); }
  }
  Serial.println("MPU6050 Found!");
  
  // 센서 범위 설정
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

/**
 * @name sendSensorData
 * @brief MPU6050에서 RAW 6축 값을 읽어, 정해진 양식("G ...")으로 블루투스 전송
 */
void sendSensorData() {
  // 1. 센서 값 읽기 (RAW 데이터)
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // 2. 블루투스로 데이터 전송 (새로운 양식: "G [값6개]")
  BTSerial.print("G "); // 데이터 종류 'G' (Gyro+Accel)
  
  // 자이로 3축 (rad/s)
  BTSerial.print(g.gyro.x); BTSerial.print(",");
  BTSerial.print(g.gyro.y); BTSerial.print(",");
  BTSerial.print(g.gyro.z); BTSerial.print(",");
  
  // 가속도 3축 (m/s^2)
  BTSerial.print(a.acceleration.x); BTSerial.print(",");
  BTSerial.print(a.acceleration.y); BTSerial.print(",");
  BTSerial.println(a.acceleration.z); // println으로 한 줄 마무리
}
