This is standard library for Sistem Pendingin Ruangan [Github](https://github.com/billalxcode/SPR/master/lib/SPR-debugger)

For example

```cpp
#include <debug.h>

uint8_t PIN_POT_MIN = 10;
uint8_t PIN_POT_MAX = 1;;
uint8_t PIN_BTN = A0;

int temperature = 10;
int humidity = 9;

int count = 0;

Debug debug;

int DEBUG_POTENSIO_MIN = debug.DEBUG_POTENSIO_MIN;
int DEBUG_POTENSIO_MAX = debug.DEBUG_POTENSIO_MAX;

void setup()
{
    debug.setup_pin(PIN_POT_MIN, PIN_POT_MAX, PIN_BTN);
    debug.initialize();
}

void loop()
{
    debug.debug_potensio(DEBUG_POTENSIO_MIN); // Debug and show value potensio min
    debug.debug_potensio(DEBUG_POTENSIO_MAX); // Debug and show value potensio max
    debug.debug_dht(temperature, humidity); // For DHT library
    debug.debug_button(); // Debug button is pressed or not pressed
    debug.debug_counter(count); // Debug and show value 'count'

    count++;
    delay(500);
}
```