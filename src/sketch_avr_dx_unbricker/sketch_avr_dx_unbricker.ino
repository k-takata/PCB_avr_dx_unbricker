//
// AVR Dx Unbricker
//
// Unbricks AVR Dx/Ex series
//

#define PIN_RESET PIN_PA3
#define PIN_INPUT PIN_PA2
#define PIN_LED   PIN_PA7

#if defined(DXCORE) && _AVR_PINCOUNT == 28
# define PIN_UPDI  PIN_PA0
#elif defined(MEGATINYCORE) && _AVR_PINCOUNT == 8
# define PIN_UPDI  PIN_PA6
#else
# error Unsupported device
#endif

// Use UART0 for UPDI
// Use only TX0 pin
auto& serial_updi = Serial;

// Use UART1 for debugging (for AVR Dx/Ex)
//auto& serial_debug = Serial1;

void setup()
{
  pinModeFast(PIN_INPUT, INPUT_PULLUP);
  pinModeFast(PIN_LED, OUTPUT);

  pinModeFast(PIN_RESET, OUTPUT);
  digitalWriteFast(PIN_RESET, LOW);

  // For debugging
  //serial_debug.begin(115200);

  // UPDI - 8 bit, even parity, 2 stop bit; one-wire
  serial_updi.begin(115200, SERIAL_8E2 | SERIAL_HALF_DUPLEX);

  attachInterrupt(digitalPinToInterrupt(PIN_INPUT), buttonPushed, FALLING);
}

unsigned long pushed_time = 0;
bool button_pushed = false;

void buttonPushed()
{
  if (!button_pushed) {
    pushed_time = millis();
    button_pushed = true;
    digitalWriteFast(PIN_LED, HIGH);
  }
}

constexpr int debounceDelay = 50; // [ms]

bool checkButtonStatus()
{
  bool ret = false;

  if (button_pushed) {
    if (millis() - pushed_time >= debounceDelay) {
      if (digitalReadFast(PIN_INPUT) == LOW) {
        ret = true;
      }
      digitalWriteFast(PIN_LED, LOW);
      button_pushed = false;
    }
  }
  return ret;
}

const uint8_t UPDI_SYNCH = 0x55;
const uint8_t UPDI_KEY_64 = 0xe0;
const uint8_t nvmprog_key[] = {0x20, 0x67, 0x6f, 0x72, 0x50, 0x4d, 0x56, 0x4e};

void send_hv_pulse()
{
  //pinMode(PIN_RESET, OUTPUT);
  digitalWriteFast(PIN_RESET, HIGH);
  // Wait t_HV (> 10 us)
  delayMicroseconds(50);
  digitalWriteFast(PIN_RESET, LOW);
  delayMicroseconds(10);  // needed?
}

void enable_updi()
{
  openDrainFast(PIN_UPDI, LOW);
  // Wait t_Deb0 (0.2 - 1 us)
  __builtin_avr_delay_cycles(F_CPU * 5 / 10'000'000);  // 0.5 us (e.g. 12 cycles @ 24 MHz)
  openDrainFast(PIN_UPDI, FLOATING);

  digitalWriteFast(PIN_LED, HIGH);
  // Wait t_UPDI (10 - 200 us)
  for (int i = 0; i < 21; ++i) {
    delayMicroseconds(10);
    if (digitalReadFast(PIN_UPDI) == HIGH)
      break;
  }
  digitalWriteFast(PIN_LED, LOW);

  // Wait t_DebZ (200 us - 14 ms)
  delay(1);

#if 0
  // long break
  openDrainFast(PIN_UPDI, LOW);
  delay(25);
  openDrainFast(PIN_UPDI, FLOATING);
#endif

  digitalWriteFast(PIN_LED, HIGH);
  // Send NVMPROG key
  serial_updi.begin(115200, SERIAL_8E2 | SERIAL_HALF_DUPLEX);
  serial_updi.write(UPDI_SYNCH);
  serial_updi.read();
  serial_updi.write(UPDI_KEY_64);
  serial_updi.read();
  for (const auto& e : nvmprog_key) {
    serial_updi.write(e);
    serial_updi.read();
  }
  digitalWriteFast(PIN_LED, LOW);
}

void loop()
{
  if (checkButtonStatus()) {
    send_hv_pulse();
    enable_updi();
  }
  delay(10);
}
