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
  PIN_LED_ONBOARD,
  PIN_BUTTON,
  PIN_SERIAL_PLUG_RX,
  PIN_SERIAL_PLUG_TX,
  PIN_SERIAL_PLUG_TX_ENABLE,
  PIN_SERIAL_SOCKET_RX,
  PIN_SERIAL_SOCKET_TX,
  PIN_SERIAL_SOCKET_TX_ENABLE,
  PIN_LED_WS2812,
  PIN_LED_WS2812_EXT,
  PIN_CODEC_ENABLE,
  PIN_CODEC_MUTE,
  PIN_I2S_MCK,
  PIN_I2S_SCK,
  PIN_I2S_FS,
  PIN_I2S_SDO,
  PIN_I2C_SCL,
  PIN_I2C_SDA,
  PIN_VOLTAGE_SENSE,
  PIN_MAX,
};

#define LED_BUILTIN PIN_LED_ONBOARD

#define digitalPinToBitMask(P) (1 << g_APinDescription[P].ulPin)

#define WIRE_INTERFACES_COUNT 1
#define PIN_WIRE_SDA (PIN_I2C_SDA)
#define PIN_WIRE_SCL (PIN_I2C_SCL)
#define PERIPH_WIRE sercom1
#define WIRE_IT_HANDLER SERCOM1_Handler
#define WIRE_IT_HANDLER_0 SERCOM1_0_Handler
#define WIRE_IT_HANDLER_1 SERCOM1_1_Handler
#define WIRE_IT_HANDLER_2 SERCOM1_2_Handler
#define WIRE_IT_HANDLER_3 SERCOM1_3_Handler
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

// Dummy definitions to satisfy compilation of core and libraries
#define PIN_A0 (0ul)
#define PIN_A1 (PIN_A0)
#define PIN_A2 (PIN_A0)
#define PIN_A3 (PIN_A0)
static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;

#define PIN_DAC0 (0ul)
#define PIN_DAC1 (0ul)

#define PIN_USB_HOST_ENABLE (0ul)
#define PIN_USB_DM (0ul)
#define PIN_USB_DP (0ul)

static const uint8_t MOSI = (0ul);
static const uint8_t MISO = (0ul);
static const uint8_t SCK  = (0ul);

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
extern Uart SerialPlug;
extern Uart SerialSocket;
void setSerialPriority(Uart *uart, uint8_t level);
#endif
