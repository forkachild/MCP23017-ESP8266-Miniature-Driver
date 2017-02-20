# MCP23017 ESP8266 Miniature Driver

This is a simple MCP23017 driver for ESP8266. Kudos to developing in C.

Usage is pretty straightforward. No I2C library required. Easy to understand API.

Circuit diagram is as follows

![Schematic](https://github.com/forkachild/MCP23017-ESP8266-Driver/raw/master/schematic.png)

If you do not want to use the default SDA, SCL and MCP23017 address, and also switch on debugging logging, use following macros in `user_config.h`

	Choose GPIO
    
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