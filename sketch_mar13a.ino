const int TX_PIN = 8;
const int BIT_US = 104; // 9600bps

void setup() {
  pinMode(TX_PIN, OUTPUT);
  digitalWrite(TX_PIN, HIGH); // idle
}

void loop() {
  uint8_t c = 'a';  // ASCII 0x61

  noInterrupts();

  // Start bit
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(BIT_US);

  // Data bits (LSB first)
  for (int i = 0; i < 8; i++) {
    digitalWrite(TX_PIN, (c & 0x01) ? HIGH : LOW);
    c >>= 1;
    delayMicroseconds(BIT_US);
  }

  // Stop bit
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(BIT_US);

  interrupts();

  delay(500);
}
