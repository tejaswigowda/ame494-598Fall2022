String inData;

void setup() {
  // initialize serial:
  Serial.begin(115200);

  // reserve 200 bytes for the inputString:
}

void loop() {
    while (Serial.available() > 0)
    {
        char recieved = Serial.read();
        inData += recieved; 

        // Process message when new line character is recieved
        if (recieved == '\n')
        {
            Serial.print("Message Received: ");
            Serial.print(inData);



            inData = ""; // Clear recieved buffer
        }
    }
}
