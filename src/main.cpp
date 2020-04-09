#include <Ctrl.h>
#include <avr/delay.h>
#include <avr/io.h>
#include <stdint.h>

#define ENC_STABLE_STATE 0x03

uint8_t read_encoder();
void handle_rotate(ctrl::Encoder_Event const *);

ctrl::Encoder enc(ENC_STABLE_STATE, read_encoder);

void setup() {
  DDRA = 0x00;
  DDRD = 0x03;
  PORTA = 0x03;
  PORTD = 0x00;

  enc.on("rotate", handle_rotate);
}

void loop() { enc.listen(); }

int main() {
  setup();

  while (true) {
    loop();
  }

  return 0;
}

uint8_t read_encoder() { return PINA &= 0x03; }

void handle_rotate(ctrl::Encoder_Event const *event) {
  if (event->positive_tick) {
    PORTD ^= 0x01;

    return;
  }

  if (event->negative_tick) {
    PORTD ^= 0x02;

    return;
  }
}
