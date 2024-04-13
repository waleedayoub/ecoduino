#include <Arduino.h>
#include <unity.h>
#include "../src/main.cpp"  // Adjust this path to include your main.cpp file

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