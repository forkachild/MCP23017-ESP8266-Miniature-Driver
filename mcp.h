#ifndef MCP_H
#define MCP_H

#include "c_types.h"
#include "gpio.h"
#include "osapi.h"
#include "eagle_soc.h"
#include "ets_sys.h"
#include "user_config.h"

// Override in user_config.h
#ifndef MCP_SDA_GPIO
#define MCP_SDA_GPIO			14
#endif

// Override in user_config.h
#ifndef MCP_SCL_GPIO
#define MCP_SCL_GPIO			12
#endif

// Override in user_config.h
#ifndef	MCP_A0
#define MCP_A0					0
#endif

// Override in user_config.h
#ifndef	MCP_A1
#define MCP_A1					0
#endif

// Override in user_config.h
#ifndef	MCP_A2
#define MCP_A2					0
#endif

#define MCP_ADDR				(0x20 | ((MCP_A2 << 2) | (MCP_A1 << 1) | (MCP_A0)))
#define MCP_READ_CMD			((MCP_ADDR << 1) | 1)
#define MCP_WRITE_CMD			((MCP_ADDR << 1) | 0)

#if MCP_SDA_GPIO == MCP_SCL_GPIO
#error "SDA and SCL cannot be on the same pins"
#endif

#if MCP_SDA_GPIO == 0
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_GPIO0_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO0
#elif MCP_SDA_GPIO == 1
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_U0TXD_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO1
#elif MCP_SDA_GPIO == 2
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_GPIO2_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO2
#elif MCP_SDA_GPIO == 3
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_U0RXD_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO3
#elif MCP_SDA_GPIO == 4
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_GPIO4_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO4
#elif MCP_SDA_GPIO == 5
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_GPIO5_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO5
#elif MCP_SDA_GPIO == 9
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA2_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO9
#elif MCP_SDA_GPIO == 10
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA3_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO10
#elif MCP_SDA_GPIO == 12
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_MTDI_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO12
#elif MCP_SDA_GPIO == 13
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_MTCK_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO13
#elif MCP_SDA_GPIO == 14
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_MTMS_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO14
#elif MCP_SDA_GPIO == 15
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_MTDO_U
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO15
#else
#error "SDA illegal value"
#endif

#if MCP_SCL_GPIO == 0
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_GPIO0_U
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO0
#elif MCP_SCL_GPIO == 1
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_U0TXD_U
#define MCP_SCL_GPIO_FUNC 		FUNC_GPIO1
#elif MCP_SCL_GPIO == 2
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_GPIO2_U
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO2
#elif MCP_SCL_GPIO == 3
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_U0RXD_U
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO3
#elif MCP_SCL_GPIO == 4
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_GPIO4_U
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO4
#elif MCP_SCL_GPIO == 5
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_GPIO5_U
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO5
#elif MCP_SCL_GPIO == 9
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA2_U
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO9
#elif MCP_SCL_GPIO == 10
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA3_U
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO10
#elif MCP_SCL_GPIO == 12
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_MTDI_U
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO12
#elif MCP_SCL_GPIO == 13
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_MTCK_U
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO13
#elif MCP_SCL_GPIO == 14
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_MTMS_U
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO14
#elif MCP_SCL_GPIO == 15
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_MTDO_U
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO15
#else
#error "SCL illegal value"
#endif

#define MCP_IODIRA_ADDR				0x00
#define MCP_IPOLA_ADDR				0x02
#define MCP_GPINTENA_ADDR			0x04
#define MCP_DEFVALA_ADDR			0x06
#define MCP_INTCONA_ADDR			0x08
#define MCP_IOCON_ADDR				0x0A
#define MCP_GPPUA_ADDR				0x0C
#define MCP_INTFA_ADDR				0x0E
#define MCP_INTCAPA_ADDR			0x10
#define MCP_GPIOA_ADDR				0x12
#define MCP_OLATA_ADDR				0x14

#define MCP_IODIRB_ADDR				0x01
#define MCP_IPOLB_ADDR				0x03
#define MCP_GPINTENB_ADDR			0x05
#define MCP_DEFVALB_ADDR			0x07
#define MCP_INTCONB_ADDR			0x09
//#define MCP_IOCON_ADDR			0x0B
#define MCP_GPPUB_ADDR				0x0D
#define MCP_INTFB_ADDR				0x0F
#define MCP_INTCAPB_ADDR			0x11
#define MCP_GPIOB_ADDR				0x13
#define MCP_OLATB_ADDR				0x15

//I2C

#define I2C_WAIT_TIME			5
#define I2C_WAIT_TIME_EX		I2C_WAIT_TIME - 2

#define bit(x)					(1 << (x))
#define bits(x, y)				(bit(x) | bit(y))
#define i2cSdaSet()				gpio_output_set(bit(MCP_SDA_GPIO), 0, bit(MCP_SDA_GPIO), 0)
#define i2cSdaClr()				gpio_output_set(0, bit(MCP_SDA_GPIO), bit(MCP_SDA_GPIO), 0)
#define i2cSclSet()				gpio_output_set(bit(MCP_SCL_GPIO), 0, bit(MCP_SCL_GPIO), 0)
#define i2cSclClr()				gpio_output_set(0, bit(MCP_SCL_GPIO), bit(MCP_SCL_GPIO), 0)
#define i2cSdaClrSclClr()		gpio_output_set(0, bits(MCP_SDA_GPIO, MCP_SCL_GPIO), bits(MCP_SDA_GPIO, MCP_SCL_GPIO), 0)
#define i2cSdaClrSclSet()		gpio_output_set(bit(MCP_SCL_GPIO), bit(MCP_SDA_GPIO), bits(MCP_SDA_GPIO, MCP_SCL_GPIO), 0)
#define i2cSdaSetSclClr()		gpio_output_set(bit(MCP_SDA_GPIO), bit(MCP_SCL_GPIO), bits(MCP_SDA_GPIO, MCP_SCL_GPIO), 0)
#define i2cSdaSetSclSet()		gpio_output_set(bits(MCP_SDA_GPIO, MCP_SCL_GPIO), 0, bits(MCP_SDA_GPIO, MCP_SCL_GPIO), 0)
#define i2cSdaRead()			(uint8) GPIO_INPUT_GET(GPIO_ID_PIN(MCP_SDA_GPIO))
#define i2cSclRead()			(uint8) GPIO_INPUT_GET(GPIO_ID_PIN(MCP_SCL_GPIO))

#define i2cWait()				os_delay_us(I2C_WAIT_TIME)
#define i2cWaitEx()				os_delay_us(I2C_WAIT_TIME_EX)

typedef enum MCP_GPIO {
	MCP_PORTA = 0, MCP_PORTB = 1
} mcp_gpio;

typedef enum MCP_PIN_MODE {
	MCP_INPUT = 0, MCP_OUTPUT = 1
} mcp_pin_mode;

typedef enum MCP_PULLUP_MODE {
	MCP_PULL_HIGH = 0, MCP_PULL_LOW = 1
} mcp_pullup_mode;

typedef enum MCP_IPOL_MODE {
	MCP_IPOL_NORMAL = 0, MCP_IPOL_INVERTED = 1
} mcp_ipol_mode;

typedef unsigned char byte;

static byte lastSda = 0;
static byte lastScl = 0;

static void ICACHE_FLASH_ATTR i2cGpioInit();
static void ICACHE_FLASH_ATTR i2cSetSdaScl(byte, byte);
static void ICACHE_FLASH_ATTR i2cInit();
static void ICACHE_FLASH_ATTR i2cStart();
static void ICACHE_FLASH_ATTR i2cStop();
static void ICACHE_FLASH_ATTR i2cSendAck();
static void ICACHE_FLASH_ATTR i2cSendNak();
static bool ICACHE_FLASH_ATTR i2cGetAck();
static byte ICACHE_FLASH_ATTR i2cReadByte();
static void ICACHE_FLASH_ATTR i2cWriteByte(byte);
static bool ICACHE_FLASH_ATTR mcpWriteReg(byte, byte);
static bool ICACHE_FLASH_ATTR mcpReadReg(byte, byte *);
void ICACHE_FLASH_ATTR mcpInit();
bool ICACHE_FLASH_ATTR mcpSetPullups(mcp_gpio, mcp_pullup_mode);
bool ICACHE_FLASH_ATTR mcpSetPinmode(mcp_gpio, mcp_pin_mode);
bool ICACHE_FLASH_ATTR mcpSetInputPolarity(mcp_gpio, mcp_ipol_mode);
bool ICACHE_FLASH_ATTR mcpSetGpio(mcp_gpio, byte);
bool ICACHE_FLASH_ATTR mcpGetGpio(mcp_gpio, byte *);

#endif
