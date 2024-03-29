#include "variant.h"

const PinDescription g_APinDescription[PIN_MAX] = {
  [PIN_LED_ONBOARD]      = {PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_MIDI_RX]   = {PORTA, 5, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_SERIAL_MIDI_TX]   = {PORTA, 4, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_BUTTON]           = {PORTA, 7, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7},
  [PIN_LED_WS2812]       = {PORTA, 16, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_POWER_ENABLE]     = {PORTA, 14, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_POWER_FAULT]      = {PORTA, 15, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15},
  [PIN_RESISTANCE_SENSE] = {PORTB, 2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel14, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  [PIN_PWM_CHANNEL + 0]  = {PORTA, 11, PIO_TIMER_ALT, PIN_ATTR_TIMER, No_ADC_Channel, NOT_ON_PWM, TCC0_CH3, EXTERNAL_INT_NONE},
  [PIN_PWM_CHANNEL + 1]  = {PORTA, 10, PIO_TIMER_ALT, PIN_ATTR_TIMER, No_ADC_Channel, NOT_ON_PWM, TCC0_CH2, EXTERNAL_INT_NONE},
  [PIN_PWM_CHANNEL + 2]  = {PORTA, 9, PIO_TIMER_ALT, PIN_ATTR_TIMER, No_ADC_Channel, NOT_ON_PWM, TCC0_CH1, EXTERNAL_INT_NONE},
  [PIN_PWM_CHANNEL + 3]  = {PORTA, 8, PIO_TIMER_ALT, PIN_ATTR_TIMER, No_ADC_Channel, NOT_ON_PWM, TCC0_CH0, EXTERNAL_INT_NONE},
};

const void *g_apTCInstances[TCC_INST_NUM + TC_INST_NUM]     = {TCC0, TCC1, TCC2, TC0, TC1, TC2, TC3};
const uint32_t GCLK_CLKCTRL_IDs[TCC_INST_NUM + TC_INST_NUM] = {TCC0_GCLK_ID, TCC1_GCLK_ID, TCC2_GCLK_ID, TC0_GCLK_ID, TC1_GCLK_ID, TC2_GCLK_ID, TC3_GCLK_ID};

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
