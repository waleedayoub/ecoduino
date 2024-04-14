#include <Arduino.h>

void setup()
{
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);

    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
}

void loop()
{
    pumpOn();
    delay(1000);
    pumpOff();
    delay(1000);
}
// open pump
void pumpOn()
{
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
}
// close pump
void pumpOff()
{
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
}

/*
void test_pump_on(void) {
    // Call the pump_on function
    pump_on();

    // Check if the pump pins are HIGH
    TEST_ASSERT_EQUAL(digitalRead(PUMP_PIN1), HIGH);
    TEST_ASSERT_EQUAL(digitalRead(PUMP_PIN2), HIGH);
}

void test_pump_off(void) {
    // Call the pump_off function
    pump_off();

    // Check if the pump pins are LOW
    TEST_ASSERT_EQUAL(digitalRead(PUMP_PIN1), LOW);
    TEST_ASSERT_EQUAL(digitalRead(PUMP_PIN2), LOW);
}
*/