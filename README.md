# MCP23017 ESP8266 Miniature Driver

This is a simple MCP23017 driver for ESP8266. MCP23017 is an I/O Expander, which means it provides 16 fully customizable Input/Output pins for any microcontroller supporting I2C protocol. ESP8266 is a powerful chip, except that it lacks the I2C hardware. This library is a fully functional controller for the same. Kudos to developing in C.

Usage is pretty straightforward. No I2C library required. Easy to understand API.

## Schematic

![Schematic](https://github.com/forkachild/MCP23017-ESP8266-Driver/raw/master/schematic.png)

## Customize SDA & SCL GPIO, Logging and addressing

	// user_config.h
    
    // Choose GPIO
    
    #define MCP_SDA_GPIO		14
    #define MCP_SCL_GPIO		12
    
    // Debugging mode
    
    #define MCP_LOG_EN
    
    // Custom MCP23017 address
    
    #define MCP_A0				0
    #define MCP_A1				0
    #define MCP_A3				0



## Configuration uses a few function calls

	#include "mcp.h"
    
    mcpInit();
    
    // Set pin mode to input or output, individual bits can be ORed
    
    mcpSetPinmode(MCP_PORTA, MCP_OUTPUT);
    mcpSetPinmode(MCP_PORTB, 0x0E);
    
    // Configure internal pullups (for input modes only), individual bits can be ORed
    
    mcpSetPullups(MCP_PORTB, MCP_PULL_HIGH);
    
    // Input polarity can be changed, and yet again individual bits can be ORed
    
    mcpSetInputPolarity(MCP_PORTA, MCP_IPOL_INVERTED);
    


## Switch GPIO and read from a port by single calls

	uint8 input;
    
	mcpSetGpio(MCP_PORTA, 0xF0);
    mcpGetGpio(MCP_PORTB, &input);
    


### Enjoy... :-)