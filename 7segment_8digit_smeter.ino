#include <LedControl.h>

// ---------------- HARDWARE ----------------
#define DIN_PIN     11
#define CLK_PIN     13
#define CS_PIN      12
#define S_METER_PIN A6
#define BUTTON_PIN  A3

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

// ------------- VARIABLES ------------------
uint32_t rx_freq = 7123000;   // frecuencia de prueba para 40m

// =========================================
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  lc.shutdown(0, false);      
  lc.setIntensity(0, 2);      
  lc.setScanLimit(0, 7);      
  lc.clearDisplay(0);
}

// =========================================
void loop() {
  show_freq(rx_freq);  

  static unsigned long t = 0;
  if (millis() - t > 50) {        
    t = millis();
    uint16_t adc = analogRead(S_METER_PIN); 
    updateSMeter(adc);
  }
}

// =========================================
void show_freq(uint32_t f) {
  lc.setDigit(0, 7, (f / 1000000) % 10, true);  
  lc.setDigit(0, 6, (f / 100000)  % 10, false);
  lc.setDigit(0, 5, (f / 10000)   % 10, false);
  lc.setDigit(0, 4, (f / 1000)    % 10, true);
  lc.setDigit(0, 3, (f / 100)     % 10, false);
  // Dígito 2 = antepenúltimo (apagado por defecto)
  // Dígito 1 = penúltimo S‑meter decena si s ≥ 10
  // Dígito 0 = último S‑meter unidad
}

// =========================================
byte smeterLevel(uint16_t adc) {
  if      (adc < 50)   return 1;
  else if (adc < 70)   return 2;
  else if (adc < 90)   return 3;
  else if (adc < 120)  return 4;
  else if (adc < 160)  return 5;
  else if (adc < 200)  return 6;
  else if (adc < 250)  return 7;
  else if (adc < 320)  return 8;
  else if (adc < 400)  return 9;
  else if (adc < 500)  return 10;   
  else if (adc < 600)  return 15;   
  else                  return 20;   
}

// =========================================
void updateSMeter(uint16_t adc) {
  byte s = smeterLevel(adc);

  Serial.print("A6=");
  Serial.print(adc);
  Serial.print("  S=");
  Serial.println(s);

  // Antepenúltimo dígito (2) → apagado por defecto
  lc.setChar(0, 2, ' ', false);  

  // Penúltimo dígito (1) → decena solo si s ≥ 10
  if(s >= 10){
      lc.setDigit(0, 1, s / 10, false); 
  } else {
      lc.setChar(0, 1, ' ', false); // apagado si s ≤ 9
  }

  // Último dígito (0) → unidad siempre
  lc.setDigit(0, 0, s % 10, false);
}
