/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);

  // Set the name for the Bluetooth (AT commands to HC-05)
//  Serial.begin(38400);
//  Serial.write("AT+NAME=Letters\r\n");
//  Serial.end();
//  delay(200);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  bool isWriteInProgress = digitalRead(4);
  static bool wasWriteInProgress = isWriteInProgress;
  byte letter = 0;
  char decodedLetter;


  if (wasWriteInProgress && !isWriteInProgress) {
    // Receive the letter
    for (int i=0; i<5; ++i) {
      letter *= 2;
      letter += digitalRead(5+i);
    }
    // Decode the letter
    if (letter == 0b11111) {
      // We need to look in the additional table
      // TODO
      goto done;
    } else if (letter == 0) {
      decodedLetter = ' ';
    } else {
      // FIXME we need to process special characters as well
      decodedLetter = 'A' + letter - 1;
    }
    // Send it through Serial
    Serial.write(decodedLetter);
//    Serial.write("-");
    // Say that we've received it
    digitalWrite(2, HIGH);
  } else if (!wasWriteInProgress && isWriteInProgress) {
    // Prepare for receiving a new character
    letter = 0;
    digitalWrite(2, LOW);
  }

  done:
  
  wasWriteInProgress = isWriteInProgress;
  delay(10);                       // wait
}
