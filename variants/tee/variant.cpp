#include "variant.h"

const PinDescription g_APinDescription[PIN_MAX] = {
  [PIN_LED_ONBOARD]                  = {PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_LED_WS2812]                   = {PORTA, 12, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_PLUG_RX]               = {PORTA, 16, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_PLUG_TX]               = {PORTA, 17, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_PLUG_TX_ENABLE]        = {PORTA, 15, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_RX]             = {PORTB, 12, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_TX]             = {PORTB, 13, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_TX_ENABLE]      = {PORTB, 11, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_NODE_RX]        = {PORTA, 8, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_NODE_TX]        = {PORTA, 9, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_NODE_TX_ENABLE] = {PORTA, 7, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
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

Uart SerialPlug(&sercom1, PIN_SERIAL_PLUG_RX, PIN_SERIAL_PLUG_TX, SERCOM_RX_PAD_1, UART_TX_PAD_0);
void SERCOM1_0_Handler() {
  SerialPlug.IrqHandler();
}
void SERCOM1_1_Handler() {
  SerialPlug.IrqHandler();
}
void SERCOM1_2_Handler() {
  SerialPlug.IrqHandler();
}
void SERCOM1_3_Handler() {
  SerialPlug.IrqHandler();
}

Uart SerialSocket(&sercom4, PIN_SERIAL_MIDI_RX, PIN_SERIAL_MIDI_TX, SERCOM_RX_PAD_1, UART_TX_PAD_0);
void SERCOM4_0_Handler() {
  SerialSocket.IrqHandler();
}
void SERCOM4_1_Handler() {
  SerialSocket.IrqHandler();
}
void SERCOM4_2_Handler() {
  SerialSocket.IrqHandler();
}
void SERCOM4_3_Handler() {
  SerialSocket.IrqHandler();
}

Uart SerialSocketNode(&sercom0, PIN_SERIAL_MIDI_RX, PIN_SERIAL_MIDI_TX, SERCOM_RX_PAD_1, UART_TX_PAD_0);
void SERCOM0_0_Handler() {
  SerialSocketNode.IrqHandler();
}
void SERCOM0_1_Handler() {
  SerialSocketNode.IrqHandler();
}
void SERCOM0_2_Handler() {
  SerialSocketNode.IrqHandler();
}
void SERCOM0_3_Handler() {
  SerialSocketNode.IrqHandler();
}

// The V2 connections require a stable ~300 kHz interrupt frequency.
void setSerialPriority(Uart *uart, uint8_t level) {
  if (uart == &SerialPlug) {
    NVIC_SetPriority(SERCOM1_0_IRQn, level);
    NVIC_SetPriority(SERCOM1_1_IRQn, level);
    NVIC_SetPriority(SERCOM1_2_IRQn, level);
    NVIC_SetPriority(SERCOM1_3_IRQn, level);
  } else if (uart = &SerialSocket) {
    NVIC_SetPriority(SERCOM4_0_IRQn, level);
    NVIC_SetPriority(SERCOM4_1_IRQn, level);
    NVIC_SetPriority(SERCOM4_2_IRQn, level);
    NVIC_SetPriority(SERCOM4_3_IRQn, level);
  } else if (uart = &SerialSocketNode) {
    NVIC_SetPriority(SERCOM0_0_IRQn, level);
    NVIC_SetPriority(SERCOM0_1_IRQn, level);
    NVIC_SetPriority(SERCOM0_2_IRQn, level);
    NVIC_SetPriority(SERCOM0_3_IRQn, level);
  } else
    abort();
}
