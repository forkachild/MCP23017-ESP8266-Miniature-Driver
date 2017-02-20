#include "mcp.h"

static void ICACHE_FLASH_ATTR i2cGpioInit() {
	ETS_GPIO_INTR_DISABLE();

	PIN_FUNC_SELECT(MCP_SDA_GPIO_MUX, MCP_SDA_GPIO_FUNC);
	PIN_FUNC_SELECT(MCP_SCL_GPIO_MUX, MCP_SCL_GPIO_FUNC);

	GPIO_REG_WRITE(GPIO_PIN_ADDR(GPIO_ID_PIN(MCP_SDA_GPIO)),
			GPIO_REG_READ(GPIO_PIN_ADDR(GPIO_ID_PIN(MCP_SDA_GPIO))) | GPIO_PIN_PAD_DRIVER_SET(GPIO_PAD_DRIVER_ENABLE)); //open drain;
	GPIO_REG_WRITE(GPIO_ENABLE_ADDRESS,
			GPIO_REG_READ(GPIO_ENABLE_ADDRESS) | (1 << MCP_SDA_GPIO));
	GPIO_REG_WRITE(GPIO_PIN_ADDR(GPIO_ID_PIN(MCP_SCL_GPIO)),
			GPIO_REG_READ(GPIO_PIN_ADDR(GPIO_ID_PIN(MCP_SCL_GPIO))) | GPIO_PIN_PAD_DRIVER_SET(GPIO_PAD_DRIVER_ENABLE)); //open drain;
	GPIO_REG_WRITE(GPIO_ENABLE_ADDRESS,
			GPIO_REG_READ(GPIO_ENABLE_ADDRESS) | (1 << MCP_SCL_GPIO));

	i2cSdaSetSclSet();

	ETS_GPIO_INTR_ENABLE();
}

static void ICACHE_FLASH_ATTR i2cSetSdaScl(byte sda, byte scl) {

	sda &= 0x01;
	scl &= 0x01;

	lastSda = sda;
	lastScl = scl;

	if (sda == 0 && scl == 0)
		i2cSdaClrSclClr();
	else if (sda == 0 && scl == 1)
		i2cSdaClrSclSet();
	else if (sda == 1 && scl == 0)
		i2cSdaSetSclClr();
	else
		i2cSdaSetSclSet();
}

static void ICACHE_FLASH_ATTR i2cInit() {
	uint8 i;

	i2cGpioInit();

	i2cSetSdaScl(1, 0);
	i2cWait();

	i2cSetSdaScl(0, 0);
	i2cWait();
	i2cSetSdaScl(1, 0);
	i2cWait();

	for (i = 0; i < 28; i++) {
		i2cSetSdaScl(1, 0);
		i2cWait();
		i2cSetSdaScl(1, 1);
		i2cWait();
	}

	i2cStop();
}

static void ICACHE_FLASH_ATTR i2cStart() {
	i2cSetSdaScl(1, lastScl);
	i2cWait();
	i2cSetSdaScl(1, 1);
	i2cWait();
	i2cSetSdaScl(0, 1);
	i2cWait();
}

static void ICACHE_FLASH_ATTR i2cStop() {
	i2cWait();

	i2cSetSdaScl(0, lastScl);
	i2cWait();
	i2cSetSdaScl(0, 1);
	i2cWait();
	i2cSetSdaScl(1, 1);
	i2cWait();
}

static void ICACHE_FLASH_ATTR i2cSendAck() {
	i2cSetSdaScl(lastSda, 0);
	i2cWait();
	i2cSetSdaScl(0, 0);
	i2cWait();
	i2cSetSdaScl(0, 1);
	i2cWait();
	i2cWaitEx();
	i2cSetSdaScl(0, 0);
	i2cWait();
	i2cSetSdaScl(1, 0);
	i2cWait();
}

static void ICACHE_FLASH_ATTR i2cSendNak() {
	i2cSetSdaScl(lastSda, 0);
	i2cWait();
	i2cSetSdaScl(1, 0);
	i2cWait();
	i2cSetSdaScl(1, 1);
	i2cWait();
	i2cWaitEx();
	i2cSetSdaScl(1, 0);
	i2cWait();
	i2cSetSdaScl(1, 0);
	i2cWait();
}

static bool ICACHE_FLASH_ATTR i2cGetAck() {
	uint8 ack;

	i2cSetSdaScl(lastSda, 0);
	i2cWait();
	i2cSetSdaScl(1, 0);
	i2cWait();
	i2cSetSdaScl(1, 1);
	i2cWait();

	ack = i2cSdaRead();
	i2cWait();
	i2cSetSdaScl(1, 0);
	i2cWait();

	if (ack)
		return false;
	else
		return true;
}

static byte ICACHE_FLASH_ATTR i2cReadByte() {

	uint8 data = 0, b, i;

	i2cWait();
	i2cSetSdaScl(lastSda, 0);
	i2cWait();

	for (i = 0; i < 8; i++) {
		i2cWait();
		i2cSetSdaScl(1, 0);
		i2cWait();
		i2cSetSdaScl(1, 1);
		i2cWait();

		b = i2cSdaRead();
		i2cWait();

		if (i == 7)
			i2cWaitEx();

		b <<= (7 - i);
		data |= b;
	}

	//i2cWaitEx();

	i2cSetSdaScl(1, 0);
	i2cWait();

	return data;

}

static void ICACHE_FLASH_ATTR i2cWriteByte(byte data) {

	uint8 dat;
	sint8 i;

	i2cWait();
	i2cSetSdaScl(lastSda, 0);
	i2cWait();

	for (i = 7; i >= 0; i--) {
		dat = data >> i;

		i2cSetSdaScl(dat, 0);
		i2cWait();
		i2cSetSdaScl(dat, 1);
		i2cWait();

		if (i == 0) {
			i2cWaitEx();
		}

		i2cSetSdaScl(dat, 0);
		i2cWait();
	}
}

static bool ICACHE_FLASH_ATTR mcpWriteReg(byte regAddr, byte regData) {
	i2cStart();
	i2cWriteByte(MCP_WRITE_CMD);
	if (!i2cGetAck()) {
		i2cStop();
#ifdef MCP_LOG_EN
		os_printf("NAK while writing device address\n");
#endif
		return false;
	}
#ifdef MCP_LOG_EN
	os_printf("ACK while writing device address\n");
#endif

	i2cWriteByte(regAddr);
	if (!i2cGetAck()) {
		i2cStop();
#ifdef MCP_LOG_EN
		os_printf("NAK while writing register address\n");
#endif
		return false;
	}

#ifdef MCP_LOG_EN
	os_printf("ACK while writing register address\n");
#endif

	i2cWriteByte(regData);
	bool rv = i2cGetAck();
	i2cStop();
#ifdef MCP_LOG_EN
	if (!rv) {
		os_printf("NAK while writing register data\n");
	} else {
		os_printf("ACK while writing register data\n");
	}
#endif

	return rv;

}

static bool ICACHE_FLASH_ATTR mcpReadReg(byte regAddr, byte *regData) {
	i2cStart();
	i2cWriteByte(MCP_WRITE_CMD);
	if (i2cGetAck() == false) {
		i2cStop();
#ifdef MCP_LOG_EN
		os_printf("NAK while writing device address\n");
#endif
		return false;
	}

#ifdef MCP_LOG_EN
	os_printf("ACK while writing device address\n");
#endif

	i2cWriteByte(regAddr);

	if (i2cGetAck() == false) {
		i2cStop();
#ifdef MCP_LOG_EN
		os_printf("NAK while writing register address\n");
#endif
		return false;
	}

#ifdef MCP_LOG_EN
	os_printf("ACK while writing register address\n");
#endif

	i2cStart();
	i2cWriteByte(MCP_READ_CMD);
	if (i2cGetAck() == false) {
		i2cStop();
#ifdef MCP_LOG_EN
		os_printf("NAK while writing device address for reading\n");
#endif
		return false;
	}

#ifdef MCP_LOG_EN
	os_printf("ACK while writing device address for reading\n");
#endif

	*regData = i2cReadByte();
	i2cGetAck();
	i2cStop();

	return true;
}

void ICACHE_FLASH_ATTR mcpInit() {
	i2cInit();
}

bool ICACHE_FLASH_ATTR mcpSetPullups(mcp_gpio gpio, mcp_pullup_mode mode) {
	return mcpWriteReg((gpio == MCP_PORTA) ? MCP_GPPUA_ADDR : MCP_GPPUB_ADDR,
			(mode == MCP_PULL_LOW) ? 0x00 : 0xFF);
}

bool ICACHE_FLASH_ATTR mcpSetPinmode(mcp_gpio gpio, mcp_pin_mode mode) {
	return mcpWriteReg((gpio == MCP_PORTA) ? MCP_IODIRA_ADDR : MCP_IODIRB_ADDR,
			(mode == MCP_OUTPUT) ? 0x00 : 0xFF);
}

bool ICACHE_FLASH_ATTR mcpSetInputPolarity(mcp_gpio gpio, mcp_ipol_mode mode) {
	return mcpWriteReg((gpio == MCP_PORTA) ? MCP_IPOLA_ADDR : MCP_IPOLB_ADDR,
			(mode == MCP_IPOL_NORMAL) ? 0x00 : 0xFF);
}

bool ICACHE_FLASH_ATTR mcpSetGpio(mcp_gpio gpio, byte data) {
	return mcpWriteReg((gpio == MCP_PORTA) ? MCP_GPIOA_ADDR : MCP_GPIOB_ADDR,
			data);
}

bool ICACHE_FLASH_ATTR mcpGetGpio(mcp_gpio gpio, byte *data) {
	return mcpReadReg((gpio == MCP_PORTA) ? MCP_GPIOA_ADDR : MCP_GPIOB_ADDR,
			data);
}
