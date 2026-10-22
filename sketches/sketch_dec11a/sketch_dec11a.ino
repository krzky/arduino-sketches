void setup() {
  TCB0.CCMP = 250;
  TCB0.CTRLA = (1 << TCB_ENABLE_bp) | (0x03 << TCB_CLKSEL_gp);
  TCB0.INTCTRL = (1 << TCB_CAPT_bp);

  sei();
}

void loop() {
}
