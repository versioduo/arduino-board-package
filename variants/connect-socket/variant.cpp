#include "variant.h"

const PinDescription g_APinDescription[PIN_MAX] = {
  [PIN_LED_ONBOARD]             = {PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_RX]        = {PORTA, 23, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_TX]        = {PORTA, 22, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_TX_ENABLE] = {PORTA, 21, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_BUTTON + 0]              = {PORTB, 0, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0},
  [PIN_BUTTON + 1]              = {PORTB, 1, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1},
  [PIN_BUTTON + 2]              = {PORTB, 2, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2},
  [PIN_BUTTON + 3]              = {PORTB, 3, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3},
  [PIN_LED_WS2812]              = {PORTA, 12, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_MIDI_RX]          = {PORTA, 5, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_MIDI_TX]          = {PORTA, 4, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
};

const void *g_apTCInstances[TCC_INST_NUM + TC_INST_NUM] = {
  TCC0,
  TCC1,
  TCC2,
  TCC3,
  TCC4,
  TC0,
  TC1,
  TC2,
  TC3,
  TC4,
  TC5,
};

const uint32_t GCLK_CLKCTRL_IDs[TCC_INST_NUM + TC_INST_NUM] = {
  TCC0_GCLK_ID,
  TCC1_GCLK_ID,
  TCC2_GCLK_ID,
  TCC3_GCLK_ID,
  TCC4_GCLK_ID,
  TC0_GCLK_ID,
  TC1_GCLK_ID,
  TC2_GCLK_ID,
  TC3_GCLK_ID,
  TC4_GCLK_ID,
  TC5_GCLK_ID,
};

SERCOM sercom0(SERCOM0);
SERCOM sercom1(SERCOM1);
SERCOM sercom2(SERCOM2);
SERCOM sercom3(SERCOM3);
SERCOM sercom4(SERCOM4);
SERCOM sercom5(SERCOM5);

Uart SerialMIDI(&sercom0, PIN_SERIAL_MIDI_RX, PIN_SERIAL_MIDI_TX, SERCOM_RX_PAD_1, UART_TX_PAD_0);
void SERCOM0_0_Handler() {
  SerialMIDI.IrqHandler();
}
void SERCOM0_1_Handler() {
  SerialMIDI.IrqHandler();
}
void SERCOM0_2_Handler() {
  SerialMIDI.IrqHandler();
}
void SERCOM0_3_Handler() {
  SerialMIDI.IrqHandler();
}

Uart SerialSocket(&sercom3, PIN_SERIAL_SOCKET_RX, PIN_SERIAL_SOCKET_TX, SERCOM_RX_PAD_1, UART_TX_PAD_0);
void SERCOM3_0_Handler() {
  SerialSocket.IrqHandler();
}
void SERCOM3_1_Handler() {
  SerialSocket.IrqHandler();
}
void SERCOM3_2_Handler() {
  SerialSocket.IrqHandler();
}
void SERCOM3_3_Handler() {
  SerialSocket.IrqHandler();
}

// The V2 connections require a stable ~300 kHz interrupt frequency.
void setSerialPriority(Uart *uart, uint8_t level) {
  if (uart == &SerialSocket) {
    NVIC_SetPriority(SERCOM3_0_IRQn, level);
    NVIC_SetPriority(SERCOM3_1_IRQn, level);
    NVIC_SetPriority(SERCOM3_2_IRQn, level);
    NVIC_SetPriority(SERCOM3_3_IRQn, level);
  }
}
