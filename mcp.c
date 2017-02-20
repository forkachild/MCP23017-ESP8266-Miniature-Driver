#include "mcp.h"

static void i2cGpioInit() {
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

static void i2cInit() {
	uint8 i;

	i2cGpioInit();

	i2cSdaSetSclClr();
	i2cWait();
	i2cSdaClrSclClr();
	i2cWait();
	i2cSdaSetSclClr();
	i2cWait();

	for (i = 0; i < 28; i++) {
		i2cSdaSetSclClr();
		i2cWait();
		i2cSdaSetSclSet();
		i2cWait();
	}

	i2cStop();
}

static void i2cStart() {
	i2cSdaSet();
	i2cWait();
	i2cSdaSetSclSet();
	i2cWait();
	i2cSdaClrSclSet();
	i2cWait();
}

static void i2cStop() {
	i2cWait();
	i2cSdaClr();
	i2cWait();
	i2cSdaClrSclSet();
	i2cWait();
	i2cSdaSetSclSet();
	i2cWait();
}

static void i2cSendAck() {
	i2cSclClr();
	i2cWait();
	i2cSdaClrSclClr();
	i2cWait();
	i2cSdaClrSclSet();
	i2cWait();
#ifdef I2C_WAIT_EX_EN
	i2cWaitEx();
#endif
	i2cSdaClrSclClr();
	i2cWait();
	i2cSdaSetSclClr();
	i2cWait();
}

static void i2cSendNak() {
	i2cSclClr();
	i2cWait();
	i2cSdaSetSclClr();
	i2cWait();
	i2cSdaSetSclSet();
	i2cWait();
#ifdef I2C_WAIT_EX_EN
	i2cWaitEx();
#endif
	i2cSdaSetSclClr();
	i2cWait();
	i2cSdaSetSclClr();
	i2cWait();
}

static bool i2cGetAck() {
	uint8 ack;
	i2cSclClr();
	i2cWait();
	i2cSdaSetSclClr();
	i2cWait();
	i2cSdaSetSclSet();
	i2cWait();
	ack = i2cSdaRead();
	i2cWait();
	i2cSdaSetSclClr();
	i2cWait();

	if (ack)
		return true;
	else
		return false;
}

static byte i2cReadByte() {

	uint8 data = 0, b, i;

	i2cWait();
	i2cSclClr();
	i2cWait();

	for (i = 0; i < 8; i++) {
		i2cWait();
		i2cSdaSetSclClr();
		i2cWait();
		i2cSdaSetSclSet();
		i2cWait();

		b = i2cSdaRead();
		i2cWait();

		b <<= (7 - i);
		data != b;
	}

#ifdef I2C_WAIT_EX_EN
	i2cWaitEx();
#endif

	i2cSdaSetSclClr();
	i2cWait();

	return data;

}

static void i2cWriteByte(byte data) {

	uint8 i, dataX;

	i2cWait();
	i2cSclClr();
	i2cWait();

	for (i = 0; i < 8; i++) {
		dataX = data >> (7 - i);
		if (dataX) {
			i2cSdaSetSclClr();
			i2cWait();
			i2cSdaSetSclSet();
			i2cWait();
		} else {
			i2cSdaClrSclClr();
			i2cWait();
			i2cSdaClrSclSet();
			i2cWait();
		}

#ifdef I2C_WAIT_EX_EN
		if(i == 7)
		i2cWaitEx();
#endif

		if (dataX) {
			i2cSdaSetSclClr();
			i2cWait();
		} else {
			i2cSdaClrSclClr();
			i2cWait();
		}
	}
}

void mcpInit() {
	i2cInit();
}

void mcpSetAddr(byte addr) {
	currentAddr = addr;
}

bool mcpSetPullups(mcp_gpio gpio, byte mask) {
	return mcpWriteReg(currentAddr, (gpio == MCP_PORTB) ? MCP_GPPUB_ADDR : MCP_GPPUA_ADDR, mask);
}

bool mcpSetPinmode(mcp_gpio gpio, byte mode) {
	return mcpWriteReg(currentAddr, (gpio == MCP_PORTB) ? MCP_IODIRB_ADDR : MCP_IODIRA_ADDR, mode);
}

bool mcpSetInputPolarity(mcp_gpio gpio, byte pol) {
	return mcpWriteReg(currentAddr, (gpio == MCP_PORTB) ? MCP_IPOLB_ADDR : MCP_IPOLA_ADDR, pol);
}

bool mcpSetGpio(mcp_gpio gpio, byte data) {
	return mcpWriteReg(currentAddr, (gpio == MCP_PORTB) ? MCP_GPIOB_ADDR : MCP_GPIOA_ADDR, data);
}

bool mcpGetGpio(mcp_gpio gpio, byte *data) {
	return mcpReadReg(currentAddr, (gpio == MCP_PORTB) ? MCP_GPIOB_ADDR : MCP_GPIOA_ADDR, data);
}

static bool mcpWriteReg(byte devAddr, byte regAddr, byte regData) {
	i2cStart();
	i2cWriteByte(mcpGetAddr(devAddr, MCP_WRITE));
	if (i2cGetAck() == false) {
		i2cStop();
#ifdef MCP_LOG_EN
		os_printf("NAK while writing device address\n");
#endif
		return false;
	}

	i2cWriteByte(regAddr);
	if (i2cGetAck() == false) {
		i2cStop();
#ifdef MCP_LOG_EN
		os_printf("NAK while writing register address\n");
#endif
		return false;
	}

	i2cWriteByte(regData);
	bool rv = i2cGetAck();
	i2cStop();
	if (rv == false) {
#ifdef MCP_LOG_EN
		os_printf("NAK while writing register data\n");
#endif
	}
	return rv;

}

static bool mcpReadReg(byte devAddr, byte regAddr, byte *regData) {
	i2cStart();
	i2cWriteByte(mcpGetAddr(devAddr, MCP_WRITE));
	if (i2cGetAck() == false) {
		i2cStop();
#ifdef MCP_LOG_EN
		os_printf("NAK while writing device address\n");
#endif
		return false;
	}

	i2cWriteByte(regAddr);

	if (i2cGetAck() == false) {
		i2cStop();
#ifdef MCP_LOG_EN
		os_printf("NAK while writing register address\n");
#endif
		return false;
	}

	i2cStart();
	i2cWriteByte(mcpGetAddr(devAddr, MCP_READ));
	if (i2cGetAck() == false) {
		i2cStop();
#ifdef MCP_LOG_EN
		os_printf("NAK while writing device address for reading\n");
#endif
		return false;
	}

	*regData = i2cReadByte();
	bool rv = i2cGetAck();
	i2cStop();
	if (rv == false) {
#ifdef MCP_LOG_EN
		os_printf("NAK while writing device address\n");
#endif
	}
	return rv;
}

