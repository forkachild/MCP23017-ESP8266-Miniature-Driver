#ifndef MCP_H
#define MCP_H

#include "c_types.h"
#include "eagle_soc.h"
#include "gpio.h"
#include "osapi.h"
#include "user_interface.h"
#include "ets_sys.h"

// Define the below 4 lines in your user_config.h file
#define MCP_SDA_GPIO			14
#define MCP_SCL_GPIO			12
#define MCP_LOG_EN
//#define I2C_WAIT_EX_EN

#ifndef MCP_SDA_GPIO
#define MCP_SDA_GPIO			14
#endif

#ifndef MCP_SCL_GPIO
#define MCP_SCL_GPIO			12
#endif

#if MCP_SDA_GPIO == 0
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_GPIO0_U
#elif MCP_SDA_GPIO == 1
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_U0TXD_U
#elif MCP_SDA_GPIO == 2
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_GPIO2_U
#elif MCP_SDA_GPIO == 3
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_U0RXD_U
#elif MCP_SDA_GPIO == 4
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_GPIO4_U
#elif MCP_SDA_GPIO == 5
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_GPIO5_U
#elif MCP_SDA_GPIO == 6
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_SD_CLK_U
#elif MCP_SDA_GPIO == 7
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA0_U
#elif MCP_SDA_GPIO == 8
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA1_U
#elif MCP_SDA_GPIO == 9
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA2_U
#elif MCP_SDA_GPIO == 10
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA3_U
#elif MCP_SDA_GPIO == 11
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_SD_CMD_U
#elif MCP_SDA_GPIO == 12
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_MTDI_U
#elif MCP_SDA_GPIO == 13
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_MTCK_U
#elif MCP_SDA_GPIO == 14
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_MTMS_U
#elif MCP_SDA_GPIO == 15
#define MCP_SDA_GPIO_MUX		PERIPHS_IO_MUX_MTDO_U
#else
#define MCP_SDA_GPIO_MUX		0
#error "Invalid SDA"
#endif

#if MCP_SCL_GPIO == 0
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_GPIO0_U
#elif MCP_SCL_GPIO == 1
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_U0TXD_U
#elif MCP_SCL_GPIO == 2
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_GPIO2_U
#elif MCP_SCL_GPIO == 3
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_U0RXD_U
#elif MCP_SCL_GPIO == 4
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_GPIO4_U
#elif MCP_SCL_GPIO == 5
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_GPIO5_U
#elif MCP_SCL_GPIO == 6
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_SD_CLK_U
#elif MCP_SCL_GPIO == 7
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA0_U
#elif MCP_SCL_GPIO == 8
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA1_U
#elif MCP_SCL_GPIO == 9
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA2_U
#elif MCP_SCL_GPIO == 10
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_SD_DATA3_U
#elif MCP_SCL_GPIO == 11
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_SD_CMD_U
#elif MCP_SCL_GPIO == 12
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_MTDI_U
#elif MCP_SCL_GPIO == 13
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_MTCK_U
#elif MCP_SCL_GPIO == 14
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_MTMS_U
#elif MCP_SCL_GPIO == 15
#define MCP_SCL_GPIO_MUX		PERIPHS_IO_MUX_MTDO_U
#else
#define MCP_SCL_GPIO_MUX		0
#error "Invalid SDA"
#endif

#if MCP_SDA_GPIO == 0
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO0
#elif MCP_SDA_GPIO == 1
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO1
#elif MCP_SDA_GPIO == 2
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO2
#elif MCP_SDA_GPIO == 3
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO3
#elif MCP_SDA_GPIO == 4
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO4
#elif MCP_SDA_GPIO == 5
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO5
#elif MCP_SDA_GPIO == 6
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO6
#elif MCP_SDA_GPIO == 7
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO7
#elif MCP_SDA_GPIO == 8
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO8
#elif MCP_SDA_GPIO == 9
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO9
#elif MCP_SDA_GPIO == 10
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO10
#elif MCP_SDA_GPIO == 11
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO11
#elif MCP_SDA_GPIO == 12
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO12
#elif MCP_SDA_GPIO == 13
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO13
#elif MCP_SDA_GPIO == 14
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO14
#elif MCP_SDA_GPIO == 15
#define MCP_SDA_GPIO_FUNC		FUNC_GPIO15
#else
#define MCP_SDA_GPIO_FUNC		0
#error "Invalid SDA"
#endif

#if MCP_SCL_GPIO == 0
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO0
#elif MCP_SCL_GPIO == 1
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO1
#elif MCP_SCL_GPIO == 2
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO2
#elif MCP_SCL_GPIO == 3
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO3
#elif MCP_SCL_GPIO == 4
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO4
#elif MCP_SCL_GPIO == 5
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO5
#elif MCP_SCL_GPIO == 6
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO6
#elif MCP_SCL_GPIO == 7
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO7
#elif MCP_SCL_GPIO == 8
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO8
#elif MCP_SCL_GPIO == 9
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO9
#elif MCP_SCL_GPIO == 10
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO10
#elif MCP_SCL_GPIO == 11
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO11
#elif MCP_SCL_GPIO == 12
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO12
#elif MCP_SCL_GPIO == 13
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO13
#elif MCP_SCL_GPIO == 14
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO14
#elif MCP_SCL_GPIO == 15
#define MCP_SCL_GPIO_FUNC		FUNC_GPIO15
#else
#define MCP_SCL_GPIO_FUNC		0
#error "Invalid SCL"
#endif

//Pre calculated values
#define IOCON_BANK				0
#define IOCON_MIRROR			0
#define IOCON_SEQOP				1
#define IOCON_DISSLW			1
#define IOCON_HAEN				1
#define IOCON_ODR				1
#define IOCON_INTPOL			0
#define IOCON_UNIMP				0

#define IOCON_VALUE				(IOCON_BANK << 7) | (IOCON_MIRROR << 6) | (IOCON_SEQOP << 5) | (IOCON_DISSLW << 4) | (IOCON_HAEN << 3) | (IOCON_ODR << 2) | (IOCON_INTPOL << 1) | (IOCON_UNIMP)

#if IOCON_BANK == 0

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

#else

#define MCP_IODIRA_ADDR				0x00
#define MCP_IPOLA_ADDR				0x01
#define MCP_GPINTENA_ADDR			0x02
#define MCP_DEFVALA_ADDR			0x03
#define MCP_INTCONA_ADDR			0x04
#define MCP_IOCON_ADDR				0x05
#define MCP_GPPUA_ADDR				0x06
#define MCP_INTFA_ADDR				0x07
#define MCP_INTCAPA_ADDR			0x08
#define MCP_GPIOA_ADDR				0x09
#define MCP_OLATA					0x0A

#define MCP_IODIRB_ADDR				0x10
#define MCP_IPOLB_ADDR				0x11
#define MCP_GPINTENB_ADDR			0x12
#define MCP_DEFVALB_ADDR			0x13
#define MCP_INTCONB_ADDR			0x14
//#define MCP_IOCON_ADDR			0x15
#define MCP_GPPUB_ADDR				0x16
#define MCP_INTFB_ADDR				0x17
#define MCP_INTCAPB_ADDR			0x18
#define MCP_GPIOB_ADDR				0x19
#define MCP_OLATB_ADDR				0x1A

#endif

#define MCP_READ				1
#define MCP_WRITE				0
#define mcpGetAddr(x, y)		(((0x20UL | (x)) << 1) | (y))

//I2C

#define I2C_WAIT_TIME			5
#define I2C_WAIT_TIME_EX		3

#define I2C_ACK					1
#define I2C_NAK					0

#define bit(x)					(1UL << (x))
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
#ifdef I2C_WAIT_EX_EN
#define i2cWaitEx()				os_delay_us(I2C_WAIT_TIME_EX)
#endif

#define true					(1)
#define false					(0)
#define TRUE					true
#define FALSE					false

typedef enum MCP_GPIO {
	MCP_PORTA = 0, MCP_PORTB = 1
} mcp_gpio;

typedef unsigned char bool;
typedef unsigned char byte;

static byte currentAddr = 0x00;

static void i2cGpioInit();
static void i2cInit();
static void i2cStart();
static void i2cStop();
static void i2cSendAck();
static void i2cSendNak();
static bool i2cGetAck();
void mcpInit();
void mcpSetAddr(byte);
bool mcpSetPullups(mcp_gpio, byte);
bool mcpSetPinmode(mcp_gpio, byte);
bool mcpSetInputPolarity(mcp_gpio, byte);
bool mcpSetGpio(mcp_gpio, byte);
bool mcpGetGpio(mcp_gpio, byte *);

#endif
