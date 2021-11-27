#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

int PIN_LED_GRN = 5;
int PIN_LED_RED = 6;
int PIN_DHT11 = 8;
int PIN_BUTTON = 7;
int PIN_POTENSIO_MIN = A0;
int PIN_POTENSIO_MAX = A1;
int PIN_RELAY_L = 2;
int PIN_RELAY_R = 3;

int MIN_VALUE = 0;
int MAX_VALUE = 0;

int LCD_ROW = 2;
int LCD_COLUMN = 16;

int max_counter = 10;
int current_counter = 0;

DHT dht(PIN_DHT11, DHT11);
LiquidCrystal_I2C lcd(0x27, LCD_ROW, LCD_COLUMN);

int read_potensio(uint8_t pin)
{
    int potensio_value = analogRead(pin);
    int value_output = map(potensio_value, 0, 1024, 0, 40);
    return value_output;
}

int button_is_pressed()
{
    int btn_status = digitalRead(PIN_BUTTON);
    Serial.println(btn_status);
    return btn_status;
}

void display_boot(int delay_time)
{
    lcd.setCursor(0, 0);
    lcd.print("Booting...");
    lcd.setCursor(0, 1);
    lcd.print("(c)Billal Fauzan");

    Serial.begin(9600);
    Serial.println("(c) Copyright 2021 Billal Fauzan (billal.xcode@gmail.com)");
    dht.begin();

    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_GRN, OUTPUT);
    pinMode(PIN_RELAY_L, OUTPUT);
    pinMode(PIN_RELAY_R, OUTPUT);
    delay(delay_time);
    lcd.clear();
}

void start_counter()
{
    if (current_counter <= (max_counter + 1))
    {
        current_counter += 1;
    }
}

void disable_all()
{
    digitalWrite(PIN_RELAY_L, LOW);
    digitalWrite(PIN_RELAY_R, LOW);
    digitalWrite(PIN_LED_GRN, LOW);
    digitalWrite(PIN_LED_RED, LOW);
}

void display_settings()
{
    current_counter = 0;
    Serial.println("Settings Mode");
    lcd.clear();
    disable_all();
    while (1)
    {

        int potensio_min = read_potensio(PIN_POTENSIO_MIN);
        int potensio_max = read_potensio(PIN_POTENSIO_MAX);

        lcd.setCursor(0, 0);
        lcd.print("MIN: ");
        lcd.print(potensio_min);
        lcd.print("   ");
        lcd.setCursor(0, 1);
        lcd.print("MAX: ");
        lcd.print(potensio_max);
        lcd.print("   ");

        int is_pressed = button_is_pressed();
        if (is_pressed == 1 && current_counter >= max_counter)
        {
            MIN_VALUE = potensio_min;
            MAX_VALUE = potensio_max;
            lcd.clear();
            break;
        }
        start_counter();
        delay(150);
    }

}

void led_automate()
{
    Serial.print("MIN: ");
    Serial.print(MIN_VALUE);
    Serial.print(" | MAX: ");
    Serial.println(MAX_VALUE);
    int current_temperature = dht.readTemperature();
    // int current_humidity = dht.readHumidity();
    Serial.println(current_temperature);
    if (current_temperature <= MIN_VALUE)
    {
        digitalWrite(PIN_LED_GRN, HIGH);
        digitalWrite(PIN_LED_RED, LOW);
        digitalWrite(PIN_RELAY_L, LOW);
        digitalWrite(PIN_RELAY_R, LOW);
    } else if (current_temperature >= MAX_VALUE)
    {
        digitalWrite(PIN_LED_GRN, LOW);
        digitalWrite(PIN_LED_RED, HIGH);
        digitalWrite(PIN_RELAY_L, HIGH);
        digitalWrite(PIN_RELAY_R, HIGH);
    } else
    {
        digitalWrite(PIN_LED_GRN, HIGH);
        digitalWrite(PIN_LED_RED, HIGH);
        digitalWrite(PIN_RELAY_L, LOW);
        digitalWrite(PIN_RELAY_R, LOW);
    }
}

void setup()
{
    lcd.init();
    lcd.clear();
    lcd.backlight();

    display_boot(3000);
}

void loop()
{
    int is_pressed = button_is_pressed();
    if (is_pressed == 1 && current_counter >= max_counter)
    {
        display_settings();
    }

    int temperature = dht.readTemperature();
    int humidity = dht.readHumidity();

    lcd.setCursor(0, 0);
    lcd.print("C: ");
    lcd.print(temperature);
    lcd.print("   ");
    lcd.setCursor(0, 1);
    lcd.print("H: ");
    lcd.print(humidity);
    lcd.print("   ");

    led_automate();
    start_counter();
    delay(150);
}