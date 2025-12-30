S_meter_8digit_7segmet.ino

This project displays an S‑meter along with frequency on an **8‑digit 7‑segment display** using the **LedControl** library. Compatible with ATmega/LGT8FX microcontrollers and MAX7219-based modules.

---

## Features

- **Frequency**: 5 visible digits (digits 3–7)  
- **S‑meter** displayed on the last two digits:
  - **Second-to-last digit (1):** S‑meter tens (only if S ≥ 10)  
  - **Last digit (0):** S‑meter units  
- **Antepenultimate digit (2):** always OFF by default, provides visual separation from the frequency.  
- Supports S levels from 1 to 20 (adjustable via ADC).  
- Serial monitor outputs ADC reading and corresponding S level.  
- Easy integration with buttons or external inputs (A3, A6).

---

## Display Layout (ASCII)

```

┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐
| 7 | | 6 | | 5 | | 4 | | 3 | | 2 | | 1 | | 0 |
└───┘ └───┘ └───┘ └───┘ └───┘ └───┘ └───┘ └───┘

```

**Digit assignment:**

| Digit | Content |
|-------|---------|
| 7     | Frequency: millions |
| 6     | Frequency: hundred-thousands |
| 5     | Frequency: ten-thousands |
| 4     | Frequency: thousands |
| 3     | Frequency: hundreds |
| 2     | **Antepenultimate S‑meter:** OFF by default; lights up only for external test signal |
| 1     | **Second-to-last S‑meter:** tens of S‑meter (only if S ≥ 10) |
| 0     | **Last S‑meter:** units of S‑meter |

---

## S‑meter examples

```

Frequency 71230, S = 7
7 1 2 3 0   _  _  7
Digit 2 OFF, Digit 1 OFF, Digit 0 = 7

Frequency 71230, S = 15
7 1 2 3 0   _  1  5
Digit 2 OFF, Digit 1 = tens 1, Digit 0 = units 5

Frequency 71230, S = 20
7 1 2 3 0   _  2  0
Digit 2 OFF, Digit 1 = tens 2, Digit 0 = units 0

````

- `_` = OFF digit  
- Maintains clear **visual separation between frequency and S‑meter**.  

---

## Hardware Connections

| Pin          | Connection                     |
|--------------|--------------------------------|
| DIN          | MCU Pin 11                     |
| CLK          | MCU Pin 13                     |
| CS           | MCU Pin 12                     |
| S_METER_PIN  | A6 (ADC input)                 |
| BUTTON_PIN   | A3 (optional)                  |

---

## S‑meter Calibration

1. Connect your test signal to **A6** (0–5V range).  
2. Adjust the `smeterLevel()` thresholds in the code to map ADC values to S levels:

```cpp
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
````

3. Test by touching A6 or applying voltages; the display should show:

   * Last digit = units
   * Second-to-last = tens (if S ≥ 10)
   * Antepenultimate digit stays OFF.
4. Adjust thresholds until readings match real signals.

---

## Dependencies

* [LedControl library](https://github.com/wayoda/LedControl) version 1.0.6 or higher.

---

## Usage

1. Connect your 8‑digit display (MAX7219) to the MCU.
2. Set the test frequency in `rx_freq`.
3. Apply a signal to A6 and observe the S‑meter digits.
4. Modify `smeterLevel()` for calibration as needed.

```

---

Si quieres, puedo también **prepararte un pequeño “GIF” o diagrama animado en README con ejemplos de S = 1–20**, para que los seguidores vean cómo cambia el display visualmente.  

¿Quieres que haga eso?
```


