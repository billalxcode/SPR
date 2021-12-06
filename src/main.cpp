// ==========================================================
// = Copyright (c) 2021 Billal Fauzan. All rights reserved. =
// ==========================================================

#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

const int PIN_RELAY_L = 3;
const int PIN_RELAY_R = 4;
const int PIN_LED_GRN = 5;
const int PIN_LED_RED = 6;
const int PIN_DHT11 = 9;
const int PIN_BTN = 7;

const int LCD_ROW = 2;
const int LCD_COL = 16;

const int SERIAL_BAUDRATE = 9600;

const int MODE_NORMAL = 1;
const int MODE_SETTING = 2;
const uint8_t PIN_POT_MIN = A0;
const uint8_t PIN_POT_MAX = A1;

byte face_error0[] = {
  B11111,
  B10000,
  B10100,
  B10100,
  B10000,
  B10011,
  B10100,
  B10000
};

byte face_error1[] = {
  B11110,
  B00101,
  B00101,
  B00111,
  B00001,
  B11001,
  B00101,
  B00001
};

byte face_error2[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B11111,
  B00000,
  B00000,
  B00000
};

byte fae_error3[] = {
  B00001,
  B00001,
  B00001,
  B00001,
  B11111,
  B00000,
  B00000,
  B00000
};

int POTENSIO_MIN = 0;
int POTENSIO_MAX = 0;

int mode = MODE_NORMAL;

DHT dht(9, DHT11);
LiquidCrystal_I2C lcd(0x27, LCD_COL, LCD_ROW);

int read_potensiometer(uint8_t PIN_POT)
{
    int current_value = analogRead(PIN_POT);
    int value = map(current_value, 0, 1024, 0, 40);
    return value;
}

int button_is_pressed()
{
    int isPressed = digitalRead(PIN_BTN);
    return isPressed;
}

void display_boot()
{
    lcd.setCursor(3, 0); // Set cursor to column 3 and row 0
    lcd.print("( Booting )"); // Print string to LCD
    // Set liquid crystal display cursor to row 0 and column 0
    for (int column = 0; column < LCD_COL; column++)
    {
        // Set liquid crystal display cursor to row 1 and column x
        lcd.setCursor(column, 1);
        lcd.print("-");
        delay(250);
    }
    // Clear lcd
    delay(2000);
}

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);
    lcd.init();
    lcd.clear();
    lcd.backlight();
    lcd.createChar(0, face_error0);
    lcd.createChar(1, face_error1);
    lcd.createChar(2, face_error2);
    lcd.createChar(3, fae_error3);

    display_boot();

    // Setup pin output
    pinMode(PIN_RELAY_L, OUTPUT);
    pinMode(PIN_RELAY_R, OUTPUT);
    pinMode(PIN_LED_GRN, OUTPUT);
    pinMode(PIN_LED_RED, OUTPUT);

    // Setup pin input
    pinMode(PIN_BTN, INPUT);
    pinMode(PIN_POT_MIN, INPUT);
    pinMode(PIN_POT_MAX, INPUT);

    // Enable DHT11
    dht.begin(); 
    
    lcd.clear();
}

void setting_mode()
{
    lcd.clear();
    while (1)
    {
        int button_state = button_is_pressed();
        if (button_state == 1 && mode == MODE_SETTING)
        {
            POTENSIO_MIN = read_potensiometer(PIN_POT_MIN);
            POTENSIO_MAX = read_potensiometer(PIN_POT_MAX);
            mode = MODE_NORMAL;
            delay(500);
            break;
        }

        // Read potensio
        int pot_min = read_potensiometer(PIN_POT_MIN);
        int pot_max = read_potensiometer(PIN_POT_MAX);

        // Display potensio
        lcd.setCursor(0, 0);
        lcd.print("Min: ");
        lcd.print(pot_min);
        lcd.setCursor(0, 1);
        lcd.print("Max: ");
        lcd.print(pot_max);
    }
    
}

void logic_relay(float temperature, float humidity)
{
    if (temperature < POTENSIO_MIN)
    {
        digitalWrite(PIN_LED_GRN, HIGH);
        digitalWrite(PIN_LED_RED, LOW);
        digitalWrite(PIN_RELAY_L, LOW);
        digitalWrite(PIN_RELAY_R, LOW);
    } else if (temperature > POTENSIO_MAX)
    {
        digitalWrite(PIN_LED_GRN, LOW);
        digitalWrite(PIN_LED_RED, HIGH);
        digitalWrite(PIN_RELAY_L, HIGH);
        digitalWrite(PIN_RELAY_R, HIGH);
    } else {
        digitalWrite(PIN_LED_GRN, HIGH);
        digitalWrite(PIN_LED_RED, HIGH);
        digitalWrite(PIN_RELAY_L, LOW);
        digitalWrite(PIN_RELAY_R, LOW);
    }
}

void loop()
{
    int button_state = button_is_pressed();
    if (button_state == 1 && mode == MODE_NORMAL)
    {
        mode = MODE_SETTING;
        delay(500);
        setting_mode();
    }
    // Read temperature and humidity from DHT11
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    lcd.setCursor(0, 0);
    lcd.print("T: ");
    lcd.print(temperature);
    lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print("H: ");
    lcd.print(humidity);
    lcd.print("  ");

    logic_relay(temperature, humidity);
    delay(150);
}