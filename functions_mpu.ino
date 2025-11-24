/*
 * @name initMPU6050
 * @brief MPU6050 센서를 찾고, 범위를 설정하여 초기화합니다.'
 */
void initMPU6050() {
  if (!mpu.begin()) {
    while (1) { delay(10); }
  }
  
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
  Serial.print("G "); // 데이터 종류 'G' (Gyro+Accel)
  
  // 자이로 3축 (rad/s)
  Serial.print(g.gyro.x); Serial.print(",");
  Serial.print(g.gyro.y); Serial.print(",");
  Serial.print(g.gyro.z); Serial.print(",");
  
  // 가속도 3축 (m/s^2)
  Serial.print(a.acceleration.x); Serial.print(",");
  Serial.print(a.acceleration.y); Serial.print(",");
  Serial.println(a.acceleration.z); // println으로 한 줄 마무리
}
