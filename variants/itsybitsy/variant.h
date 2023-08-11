#pragma once

#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC (32768ul)

/** Master clock frequency */
#define VARIANT_MCK (F_CPU)

#define VARIANT_GCLK0_FREQ (F_CPU)
#define VARIANT_GCLK1_FREQ (48000000UL)
#define VARIANT_GCLK2_FREQ (100000000UL)

#include "WVariant.h"

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum {
  PIN_SERIAL1_RX,
  PIN_SERIAL1_TX,
  PIN_DIGITAL2,
  PIN_DIGITAL3,
  PIN_DIGITAL4,
  PIN_DIGITAL5,
  PIN_DIGITAL6,
  PIN_DIGITAL7,
  PIN_DIGITAL8,
  PIN_DIGITAL9,
  PIN_DIGITAL10,
  PIN_DIGITAL11,
  PIN_DIGITAL12,
  PIN_LED,
  PIN_ANALOG0,
  PIN_ANALOG1,
  PIN_ANALOG2,
  PIN_ANALOG3,
  PIN_ANALOG4,
  PIN_ANALOG5,
  PIN_I2C_SDA,
  PIN_I2C_SCL,
  PIN_SPI_MISO,
  PIN_SPI_SCK,
  PIN_SPI_MOSI,
  PIN_MAX,
};

#define PINS_COUNT (38u)
#define NUM_DIGITAL_PINS (26u)
#define NUM_ANALOG_INPUTS (7u)
#define NUM_ANALOG_OUTPUTS (2u)
#define analogInputToDigitalPin(p) ((p < NUM_ANALOG_INPUTS) ? (p) + PIN_A0 : -1)

#define digitalPinToPort(P) (&(PORT->Group[g_APinDescription[P].ulPort]))
#define digitalPinToBitMask(P) (1 << g_APinDescription[P].ulPin)
#define portOutputRegister(port) (&(port->OUT.reg))
#define portInputRegister(port) (&(port->IN.reg))
#define portModeRegister(port) (&(port->DIR.reg))
#define digitalPinHasPWM(P) (g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER)

#define PIN_LED_ONBOARD PIN_LED
#define LED_BUILTIN PIN_LED

#define PIN_A0 (14ul)
#define PIN_A1 (PIN_A0 + 1)
#define PIN_A2 (PIN_A0 + 2)
#define PIN_A3 (PIN_A0 + 3)
#define PIN_A4 (PIN_A0 + 4)
#define PIN_A5 (PIN_A0 + 5)
#define PIN_A6 (PIN_A0 + 6)
#define PIN_DAC0 PIN_A0
#define PIN_DAC1 PIN_A1

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;

static const uint8_t DAC0 = PIN_DAC0;
static const uint8_t DAC1 = PIN_DAC1;

#define ADC_RESOLUTION 12

#define PAD_SERIAL1_RX (SERCOM_RX_PAD_1)
#define PAD_SERIAL1_TX (UART_TX_PAD_0)

#define SPI_INTERFACES_COUNT 1

#define PERIPH_SPI sercom1
#define PAD_SPI_TX SPI_PAD_0_SCK_1
#define PAD_SPI_RX SERCOM_RX_PAD_3

static const uint8_t SS   = PIN_A2;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA (PIN_I2C_SDA)
#define PIN_WIRE_SCL (PIN_I2C_SCL)
#define PERIPH_WIRE sercom2
#define WIRE_IT_HANDLER SERCOM2_Handler
#define WIRE_IT_HANDLER_0 SERCOM2_0_Handler
#define WIRE_IT_HANDLER_1 SERCOM2_1_Handler
#define WIRE_IT_HANDLER_2 SERCOM2_2_Handler
#define WIRE_IT_HANDLER_3 SERCOM2_3_Handler

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;
extern SERCOM sercom3;
extern SERCOM sercom4;
extern SERCOM sercom5;
extern Uart Serial1;
#endif
