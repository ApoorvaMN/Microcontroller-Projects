int buttonPin1 = 17;
int buttonPin2 = 14;
int ledPin1 = 13;
int pressCount1 = 0;
int pressCount2 = 0;

int ledState1 = HIGH;         // the current state of the output pin
int buttonState1;             // the current reading from the input pin
int buttonState2;
int lastButtonState1 = LOW;   // the previous reading from the input pin
int lastButtonState2 = LOW;
int Buttton_2_Value = (1 << 3); // Button 2 is in 3rd bit position (0-7)

char ledOn = 0;

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime1 = 0;  // the last time the output pin was toggled
long lastDebounceTime2 = 0;
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPin1, INPUT);  
  digitalWrite(ledPin1, LOW);
  DDRB= DDRB & (0b1110110);
  DDRD |= (1 << DDD5);   //Initial state of green LED on port configuration
  //pinMode (buttonPin2, INPUT_PULLUP);  
}

void loop() {
  // put your main code here, to run repeatedly for yellow LED
 int reading1 = digitalRead(buttonPin1);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading1 != lastButtonState1) {
    // reset the debouncing timer
    lastDebounceTime1 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      // only toggle the LED if the new button state is HIGH
      if (buttonState1 != HIGH) {
        pressCount1++;
        if(pressCount1>2)
        {pressCount1 = pressCount1 % 3;}
      }
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState1 = reading1;
  
  
  if(pressCount1 == 1) {
    digitalWrite(ledPin1, HIGH);
  }
  if(pressCount1 == 2) {
    digitalWrite(ledPin1, HIGH);
    delay(1250);
    digitalWrite(ledPin1, LOW);
    delay(1250);
  }
  if(pressCount1 == 0) {
    digitalWrite(ledPin1, LOW);
  }

//------------------------------------------------------------------------------------------------------
  // for green LED
 int reading2 = (PINB & (1<<3));
 
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading2 != lastButtonState2) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();
 
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:



    // if the button state has changed:
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      // only toggle the LED if the new button state is HIGH
      if (buttonState2 != (1<<3)) {
        pressCount2++;
        
        if(pressCount2>2)
        {pressCount2 = pressCount2 % 3;}
      }
    }
  }




  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState2 = reading2;
    
  if(pressCount2 == 1) {
    PORTD |= (1<<DDD5);
  }
  if(pressCount2 == 2) {
    PORTD &= ~(1<<DDD5);
    delay(250);
    PORTD |= (1<<DDD5);
    delay(250);
  }
  if(pressCount2 == 0) {
 
    PORTD &=~ (1<<DDD5);
  }

}
