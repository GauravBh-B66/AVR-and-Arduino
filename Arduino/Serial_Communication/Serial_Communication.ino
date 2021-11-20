int incomingByte = 0; // for incoming serial data

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    Serial.print("Before reading ");
    Serial.println(Serial.available());
    incomingByte = Serial.read();
    Serial.print("After reading ");
    Serial.println(Serial.available());

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);
    switch (incomingByte)
    {
      case ('a'):
      {
        Serial.println("Garuav");
        break;
      }
      case ('b'):
      {
        Serial.println("Junge");
        break;
      }
      default:
      {
        Serial.println("Noone");
      }
    }
  }
}
