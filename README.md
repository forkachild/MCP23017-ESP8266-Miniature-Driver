# MCP23017 ESP8266 Miniature Driver

This is a simple MCP23017 driver for ESP8266. MCP23017 is an I/O Expander, which means it provides 16 fully customizable Input/Output pins for any microcontroller supporting I2C protocol. ESP8266 is a powerful chip, except that it lacks the I2C hardware. This library is a fully functional controller for the same. Kudos to developing in C.

The work is heavily based on [this](https://github.com/eadf/esp8266_mcp23017) library. The I2C driver is a modified port of the `i2c_master` library from the `esp-open-sdk`.

Usage is pretty straightforward. No I2C library required. Easy to understand API.

## Schematic
![Schematic](https://github.com/forkachild/MCP23017-ESP8266-Driver/raw/master/schematic.png)

## Customize SDA & SCL GPIO, Logging and addressing

```c
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
```


## Configuration uses a few function calls

```c
#include "mcp.h"

mcpInit();

// Set pin mode to input or output, individual bits can be ORed

mcpSetPinmode(MCP_PORTA, MCP_OUTPUT);
mcpSetPinmode(MCP_PORTB, 0x0E);

// Configure internal pullups (for input modes only), individual bits can be ORed

mcpSetPullups(MCP_PORTB, MCP_PULL_HIGH);

// Input polarity can be changed, and yet again individual bits can be ORed

mcpSetInputPolarity(MCP_PORTA, MCP_IPOL_INVERTED);
```


## Effortlessly control GPIO

```c
uint8 input;

mcpSetGpio(MCP_PORTA, 0xF0);
mcpGetGpio(MCP_PORTB, &input);
``` 

## Examples

### Blinky

We all know this one

```c
// user_main.c

#include "os_type.h"
#include "mcp.h"

#define LED_PIN         (1 << 0)

os_timer_t timer;
bool toggle = false;

LOCAL void ICACHE_FLASH_ATTR timerPoll(void *arg) {
    if(toggle) {
        mcpSetGpio(MCP_PORTA, LED_PIN);     // Switch on LED
        toggle = false;
    } else {
        mcpSetGpio(MCP_PORTA, 0);           // Switch off LED
        toggle = true;
    }
}

LOCAL void ICACHE_FLASH_ATTR initDoneCb() {
    os_timer_disarm(&timer);
    os_timer_setfn(&timer, (os_timer_func_t *) timerPoll);
    os_timer_arm(&timer, 1000, true);       // Create timer
}

void user_init() {
    mcpInit();                              // Init the library
    mcpSetPinmode(MCP_PORTA, MCP_OUTPUT);   // Set full Port A as output
    system_init_done_cb(initDoneCb);
}
```

### Read switch to control an LED

The switch is push-to-close and connects PORTB pin 0 to ground.

```c
// user_main.c

#include "os_type.h"
#include "mcp.h"

#define LED_PIN         (1 << 0)
#define SWITCH_PIN      (1 << 0)

os_timer_t timer;
uint8 data;

LOCAL void ICACHE_FLASH_ATTR timerPoll(void *arg) {
    mcpGetGpio(PORTB, &data);                       // Read Port B where switch is connected
    if(data & SWITCH_PIN) {                         // Check whether switch is on
        mcpSetGpio(MCP_PORTA, LED_PIN);             // Switch on LED
    } else {
        mcpSetGpio(MCP_PORTA, 0);                   // Switch off LED
    }
}

LOCAL void ICACHE_FLASH_ATTR initDoneCb() {
    os_timer_disarm(&timer);
    os_timer_setfn(&timer, (os_timer_func_t *) timerPoll);
    os_timer_arm(&timer, 100, true);                // Create timer to poll switch
}

void user_init() {
    mcpInit();                                      // Init the library
    mcpSetPinmode(MCP_PORTA, MCP_OUTPUT);           // Set full Port A as output
    mcpSetPinmode(MCP_PORTB, MCP_INPUT);            // Set full Port B as input
    mcpSetPullups(MCP_PORTB, MCP_PULL_HIGH);        // Pullup Port B pins for switch to pull it down on press
    mcpSetInputPolarity(MCP_PORTB, MCP_INVERTED);   // Polrity has to be reversed since pullup has to mean 1
    system_init_done_cb(initDoneCb);
}
```

## Enjoy
