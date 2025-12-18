// ===== 매크로는 무조건 맨 위 =====
#define TX_HIGH() (PORTD |=  (1 << 1))  // D1 HIGH
#define TX_LOW()  (PORTD &= ~(1 << 1))  // D1 LOW

const int BIT_US = 104; // 9600 bps

void setup() {
  DDRD |= (1 << 1);   // D1 출력 설정
  TX_HIGH();          // idle 상태
}

void loop() {
  uint8_t c = 'a';    // 0x61

  noInterrupts();     // 타이밍 안정화

  // Start bit
  TX_LOW();
  delayMicroseconds(BIT_US);

  // Data bits (LSB first)
  for (int i = 0; i < 8; i++) {
    if (c & 0x01) TX_HIGH();
    else          TX_LOW();
    c >>= 1;
    delayMicroseconds(BIT_US);
  }

  // Stop bit
  TX_HIGH();
  delayMicroseconds(BIT_US);

  interrupts();

  delay(500);
}
