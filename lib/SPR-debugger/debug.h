#include <DHT.h>
#include <Arduino.h>

class Debug {
    private:
        const uint8_t DHT_TYPE = DHT11;
        uint8_t PIN_POT_MIN;
        uint8_t PIN_POT_MAX;
        uint8_t PIN_BUTTON;
        int MAX_COUNTER = 30;
        int DHT_PIN;

    public:
        const int DEBUG_LCD = 1;
        const int DEBUG_POTENSIO_MIN = 2;
        const int DEBUG_POTENSIO_MAX = 3;
        const int DEBUG_DHT11 = 4;
        const int DEBUG_BTN = 5;
        const int DEBUG_RELAY = 6;
        const int DEBUG_LED = 7;
        const int DEBUG_ALL = 8;
        int SERIAL_BITRATE = 9600;

        Debug();

        void initialize();
        void setup_pin(int PIN_POT_MIN, int PIN_POT_MAX, uint8_t PIN_BUTTON);
        void debug_dht(int temperature, int humidity);
        void debug_button();
        void debug_potensio(int debug_type);
        void debug_counter(int count);
        int is_button_pressed();
};