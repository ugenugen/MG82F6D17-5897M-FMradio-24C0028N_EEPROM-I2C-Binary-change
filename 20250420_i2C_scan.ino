#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial); // シリアルモニタ接続待ち（必要なら）
  Serial.println("I2Cスキャナ開始...");
}

void loop() {
  static int scanCount = 0;

  if (scanCount < 5) {
    Serial.print("スキャン回数: ");
    Serial.println(scanCount + 1);

    byte error, address;
    int count = 0;

    for (address = 1; address < 127; address++) {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0) {
        Serial.print("I2Cデバイス発見: アドレス 0x");
        if (address < 16)
          Serial.print("0");
        Serial.print(address, HEX);
        Serial.println();
        count++;
      }
      else if (error == 4) {
        Serial.print("未知のエラー at address 0x");
        if (address < 16)
          Serial.print("0");
        Serial.println(address, HEX);
      }
    }

    if (count == 0)
      Serial.println("I2Cデバイスが見つかりませんでした");

    scanCount++;
    delay(5000); // 5秒待って再スキャン
  } else {
    // スキャン5回終了後、何もしない
    while (true); // 無限ループで停止（スリープも可能）
  }
}
