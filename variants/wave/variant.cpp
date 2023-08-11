#include "variant.h"

const PinDescription g_APinDescription[PIN_MAX] = {
  [PIN_LED_ONBOARD]             = {PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_BUTTON]                  = {PORTB, 22, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6},
  [PIN_SERIAL_PLUG_RX]          = {PORTA, 23, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_PLUG_TX]          = {PORTA, 22, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_PLUG_TX_ENABLE]   = {PORTA, 21, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_RX]        = {PORTA, 5, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_TX]        = {PORTA, 4, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_SOCKET_TX_ENABLE] = {PORTB, 8, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_LED_WS2812]              = {PORTB, 23, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_LED_WS2812_EXT]          = {PORTB, 12, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_CODEC_ENABLE]            = {PORTA, 6, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_CODEC_MUTE]              = {PORTA, 7, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_I2S_MCK]                 = {PORTA, 8, PIO_I2S, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_I2S_SCK]                 = {PORTA, 10, PIO_I2S, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_I2S_FS]                  = {PORTA, 9, PIO_I2S, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_I2S_SDO]                 = {PORTA, 11, PIO_I2S, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_I2C_SCL]                 = {PORTA, 17, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_I2C_SDA]                 = {PORTA, 16, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_VOLTAGE_SENSE]           = {PORTB, 4, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel6, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
};

const void *g_apTCInstances[TCC_INST_NUM + TC_INST_NUM] = {TCC0, TCC1, TCC2, TCC3, TCC4, TC0, TC1, TC2, TC3, TC4, TC5};
const uint32_t GCLK_CLKCTRL_IDs[TCC_INST_NUM + TC_INST_NUM] =
  {TCC0_GCLK_ID, TCC1_GCLK_ID, TCC2_GCLK_ID, TCC3_GCLK_ID, TCC4_GCLK_ID, TC0_GCLK_ID, TC1_GCLK_ID, TC2_GCLK_ID, TC3_GCLK_ID, TC4_GCLK_ID, TC5_GCLK_ID};

SERCOM sercom0(SERCOM0); // Socket
SERCOM sercom1(SERCOM1); // I2C
SERCOM sercom2(SERCOM2); //
SERCOM sercom3(SERCOM3); // Plug
SERCOM sercom4(SERCOM4); // LEDExt
SERCOM sercom5(SERCOM5); // LED

Uart SerialPlug(&sercom3, PIN_SERIAL_SOCKET_RX, PIN_SERIAL_SOCKET_TX, SERCOM_RX_PAD_1, UART_TX_PAD_0);
void SERCOM3_0_Handler() {
  SerialPlug.IrqHandler();
}
void SERCOM3_1_Handler() {
  SerialPlug.IrqHandler();
}
void SERCOM3_2_Handler() {
  SerialPlug.IrqHandler();
}
void SERCOM3_3_Handler() {
  SerialPlug.IrqHandler();
}

Uart SerialSocket(&sercom0, PIN_SERIAL_PLUG_RX, PIN_SERIAL_PLUG_TX, SERCOM_RX_PAD_1, UART_TX_PAD_0);
void SERCOM0_0_Handler() {
  SerialSocket.IrqHandler();
}
void SERCOM0_1_Handler() {
  SerialSocket.IrqHandler();
}
void SERCOM0_2_Handler() {
  SerialSocket.IrqHandler();
}
void SERCOM0_3_Handler() {
  SerialSocket.IrqHandler();
}

// The V2 connections require a stable ~300 kHz interrupt frequency.
void setSerialPriority(Uart *uart, uint8_t level) {
  if (uart == &SerialPlug) {
    NVIC_SetPriority(SERCOM3_0_IRQn, level);
    NVIC_SetPriority(SERCOM3_1_IRQn, level);
    NVIC_SetPriority(SERCOM3_2_IRQn, level);
    NVIC_SetPriority(SERCOM3_3_IRQn, level);

  } else if (uart == &SerialSocket) {
    NVIC_SetPriority(SERCOM0_0_IRQn, level);
    NVIC_SetPriority(SERCOM0_1_IRQn, level);
    NVIC_SetPriority(SERCOM0_2_IRQn, level);
    NVIC_SetPriority(SERCOM0_3_IRQn, level);
  }
}
