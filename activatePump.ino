// Define how to activate the pump on and off routine

// open pump
void pumpOn() {
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
}

// close pump
void pumpOff() {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

