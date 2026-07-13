#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

// ---------------- Pins ----------------
const int buttonPin = 8;
const int motorPin  = 9;
const int buzzerPin = 7;

const int ringPin   = 10;
const int pixelCount = 12;

// LCD: RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Adafruit_NeoPixel ring(
  pixelCount,
  ringPin,
  NEO_GRB + NEO_KHZ800
);

bool lastButtonState = HIGH;

// ---------------- Setup ----------------
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(motorPin, LOW);
  noTone(buzzerPin);

  lcd.begin(16, 2);
  showReadyScreen();

  ring.begin();
  ring.clear();
  ring.show();
  ring.setBrightness(100);
}

// ---------------- Main loop ----------------
void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  // يبدأ الاحتفال عند الضغطة الجديدة فقط
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    goalCelebration();
  }

  lastButtonState = currentButtonState;

  delay(30);
}

// ---------------- Goal celebration ----------------
void goalCelebration() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("GOAL!!!");

  lcd.setCursor(1, 1);
  lcd.print("Celebration!");

  // تشغيل الموتور
  digitalWrite(motorPin, HIGH);

  // نغمة بداية الهدف
  tone(buzzerPin, 900, 180);
  delay(200);

  tone(buzzerPin, 1200, 180);
  delay(200);

  tone(buzzerPin, 1500, 350);
  delay(400);

  // ضوء أخضر يدور حول الرينج
  greenRunningEffect();

  // إضاءة الرينج كاملة بالأخضر
  fillRing(0, 255, 0);
  delay(700);

  // تأثير ألوان احتفالي
  rainbowEffect();

  // وميض أخضر وأبيض
  for (int i = 0; i < 4; i++) {
    fillRing(0, 255, 0);
    tone(buzzerPin, 1100, 100);
    delay(180);

    fillRing(255, 255, 255);
    delay(180);
  }

  delay(500);

  // إيقاف كل شيء
  digitalWrite(motorPin, LOW);
  noTone(buzzerPin);

  ring.clear();
  ring.show();

  showReadyScreen();
}

// ---------------- LCD ready screen ----------------
void showReadyScreen() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Ready...");

  lcd.setCursor(0, 1);
  lcd.print("Press Button");
}

// ---------------- Green moving light ----------------
void greenRunningEffect() {
  for (int roundNumber = 0; roundNumber < 3; roundNumber++) {
    for (int pixel = 0; pixel < pixelCount; pixel++) {
      ring.clear();

      ring.setPixelColor(
        pixel,
        ring.Color(0, 255, 0)
      );

      ring.show();
      delay(80);
    }
  }
}

// ---------------- Fill ring with one color ----------------
void fillRing(int red, int green, int blue) {
  for (int pixel = 0; pixel < pixelCount; pixel++) {
    ring.setPixelColor(
      pixel,
      ring.Color(red, green, blue)
    );
  }

  ring.show();
}

// ---------------- Rainbow effect ----------------
void rainbowEffect() {
  for (int colorStep = 0; colorStep < 256; colorStep += 4) {
    for (int pixel = 0; pixel < pixelCount; pixel++) {
      int colorPosition =
        (pixel * 256 / pixelCount + colorStep) & 255;

      ring.setPixelColor(
        pixel,
        colorWheel(colorPosition)
      );
    }

    ring.show();
    delay(25);
  }
}

// ---------------- Rainbow color wheel ----------------
uint32_t colorWheel(byte position) {
  position = 255 - position;

  if (position < 85) {
    return ring.Color(
      255 - position * 3,
      0,
      position * 3
    );
  }

  if (position < 170) {
    position -= 85;

    return ring.Color(
      0,
      position * 3,
      255 - position * 3
    );
  }

  position -= 170;

  return ring.Color(
    position * 3,
    255 - position * 3,
    0
  );
}