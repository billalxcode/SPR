#include <Arduino.h>
#include "debug.h"

int Debug::is_button_pressed()
{
    int current_value = digitalRead(PIN_BUTTON);
    return current_value;
}

Debug::Debug()
{

}

void Debug::initialize()
{
    pinMode(PIN_POT_MIN, INPUT);
    pinMode(PIN_POT_MAX, INPUT);
    
}

void Debug::setup_pin(int PIN_POT_MIN, int PIN_POT_MAX, uint8_t PIN_BUTTON)
{
    this->PIN_POT_MIN = PIN_POT_MIN;
    this->PIN_POT_MAX = PIN_POT_MAX;
    this->PIN_BUTTON = PIN_BUTTON;
}

void Debug::debug_potensio(int debug_type)
{
    if (debug_type == DEBUG_POTENSIO_MIN)
    {
        int current_value = analogRead(PIN_POT_MIN);
        int value = map(current_value, 0, 1024, 0, 40);
        Serial.print("Potensio min: ");
        Serial.println(value);
    }
    else if (debug_type == DEBUG_POTENSIO_MAX)
    {
        int current_value = analogRead(PIN_POT_MAX);
        int value = map(current_value, 0, 1024, 0, 40);
        Serial.print("Potensio max: ");
        Serial.println(value);
    }
}

void Debug::debug_dht(int temperature, int humidity)
{
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" Humidity: ");
    Serial.println(humidity);
}

void Debug::debug_button()
{
    int is_pressed = is_button_pressed();
    if (is_pressed == 1)
    {
        Serial.println("Button pressed");
    } else {
        Serial.println("Button not pressed");
    }
}

void Debug::debug_counter(int count)
{
    bool is_max_count = count == this->MAX_COUNTER;
    Serial.print("Counter: ");
    Serial.print(count);
    Serial.print(" Is max count: ");
    Serial.println(is_max_count);
}