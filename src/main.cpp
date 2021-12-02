#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

const int PIN_RELAY_L = 3;
const int PIN_RELAY_R = 4;
const int PIN_LED_GRN = 5;
const int PIN_LED_RED = 6;
const int PIN_DHT11 = 8;
const int PIN_BTN = 7;

const int LCD_ROW = 2;
const int LCD_COL = 16;

const int DEBUG_LCD = 1;
const int DEBUG_POTENSIO = 2;
const int DEBUG_DHT11 = 3;
const int DEBUG_BTN = 4;
const int DEBUG_RELAY = 5;
const int DEBUG_LED = 6;
const int DEBUG_ALL = 7;

const uint8_t PIN_POT_MIN = A0;
const uint8_t PIN_POT_MAX = A1;
const uint8_t DHT_TYPE = DHT11;

int POTENSIO_MIN = 0;
int POTENSIO_MAX = 0;

int button_counter = 0;
int max_buton_counter = 30;

DHT dht_sensor(PIN_DHT11, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, LCD_COL, LCD_ROW);

int button_is_pressed()
{
    int isPressed = digitalRead(PIN_BTN);
    return isPressed;
}

int read_potensio(uint8_t PIN_POT)
{
    int current_value = analogRead(PIN_POT);
    int value = map(current_value, 0, 1024, 0, 40);
    return value;
}

int start_counter()
{
    if (button_counter > max_buton_counter)
    {
        button_counter = 0;
        return 1;
    }
    else
    {
        button_counter++;
        return 0;
    }
}

void debug_lcd(int debug_type)
{
    if (debug_type == DEBUG_LCD)
    {
        Serial.print("Potensio: ");
        Serial.print(read_potensio(PIN_POT_MIN));
        Serial.print("/");
        Serial.print(read_potensio(PIN_POT_MAX));
        Serial.print("%");
        Serial.println();
        Serial.print("DHT11: ");
        Serial.print(dht_sensor.readTemperature());
        Serial.print("/");
        Serial.print(dht_sensor.readHumidity());
        Serial.print("%");
    }
}

void display_boot()
{
    lcd.init();
    lcd.clear();
    lcd.backlight();
    
    // Set liquid crystal display cursor to row 0 and column 0
    for (int column = 0; column < (LCD_COL + 1); column++)
    {
        // Set liquid crystal display cursor to row 1 and column x
        lcd.clear();
        lcd.setCursor(3, 0);
        // Print to lcd
        lcd.print("( Booting )");
        lcd.setCursor(column, 1);
        lcd.print("(c)Billal Fauzan");
        delay(250);
    }

    delay(2000);
}

void setup()
{
    display_boot();

    Serial.begin(9600);
    // Setup pin output
    pinMode(PIN_RELAY_L, OUTPUT);
    pinMode(PIN_RELAY_R, OUTPUT);
    pinMode(PIN_LED_GRN, OUTPUT);
    pinMode(PIN_LED_RED, OUTPUT);

    // Setup pin input
    pinMode(PIN_BTN, INPUT);
    pinMode(PIN_POT_MIN, INPUT);
    pinMode(PIN_POT_MAX, INPUT);

    // Clear lcd
    lcd.clear();
}

void setting_mode()
{
    lcd.clear();
    button_counter = 0;
    while (1)
    {
        debug_lcd(DEBUG_LCD);

        start_counter(); // Add counter

        int button_state = button_is_pressed();
        if (button_state == 1 && button_counter > max_buton_counter)
        {
            POTENSIO_MIN = read_potensio(PIN_POT_MIN);
            POTENSIO_MAX = read_potensio(PIN_POT_MAX);
            button_counter = 0;
            break;
        }

        // Read potensio
        int pot_min = read_potensio(PIN_POT_MIN);
        int pot_max = read_potensio(PIN_POT_MAX);

        // Display potensio
        lcd.setCursor(0, 0);
        lcd.print("Min: ");
        lcd.print(pot_min);
        lcd.setCursor(0, 1);
        lcd.print("Max: ");
        lcd.print(pot_max);
    }
    
}

void loop()
{
    start_counter();

    int button_state = button_is_pressed();
    if (button_state == 1 && button_counter > max_buton_counter)
    {
        setting_mode();
    }
}