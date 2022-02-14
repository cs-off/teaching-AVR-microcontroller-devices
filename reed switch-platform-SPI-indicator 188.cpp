int digitalGerkon = 7;
int val = 0;
unsigned long prev_time = 0;
unsigned long curr_time = 0;
int latchPin = 9;
int clockPin = 8;
int dataPin = 11;
int Time = 10;
boolean gerk = false;
boolean previous = false;
int g_registerArray[2] = {12, 13};
byte g_digits[12] = {
  B11000000, B11111001, // 0 1
  B10100100, B10110000, // 2 3
  B10011001, B10010010, // 4 5
  B10000010, B11111000, // 6 7
  B10000000, B10010000, // 8 9
};
byte g_digits_dp[12] = {
  B01000000, B01111001, // 0 1
  B00100100, B00110000, // 2 3
  B00011001, B00010010, // 4 5
  B00000010, B01111000, // 6 7
  B00000000, B00010000, // 8 9
};
void setup() {
  pinMode(digitalGerkon, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i <= 1; i++) {
    pinMode (g_registerArray[i], OUTPUT);
    digitalWrite(g_registerArray[i], 1);
  }
}
void loop() {
  prev_time = millis();
  do {
    boolean current = digitalRead(digitalGerkon);
    if (current && !previous) {
      gerk = !gerk;
      if (val > 199) val = 0; else val++;
      curr_time = millis();
    }
    previous = current;
  }
  while (curr_time - prev_time == Time);
  if (val < 10) {
    Indication(B11111111, 0);
    Indication(g_digits[val], 1);
  } else if (val < 100) {
    Indication(g_digits[(val % 100) / 10], 0);
    Indication(g_digits[val % 10], 1);
  } else if (val < 200)
  {
    Indication(g_digits_dp[(val % 100) / 10], 0);
    Indication(g_digits[val % 10], 1);
  }
}

void Indication(byte Mask, int Anode) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, Mask);
  digitalWrite(latchPin, HIGH);
  digitalWrite (g_registerArray[Anode], 0);
  delay(1);
  digitalWrite (g_registerArray[Anode], 1);
}
