#include "Arduino.h"

const uint8_t controlDiode = 13; //LED on pin 13
const uint8_t fakeEnergyMetterDiode = 8; //LED blink - emit fake metter diode.
const uint8_t photoDiodeInput = 2; //Interrupt for Photodiode
volatile auto interruptFlag = 0;

void FakeBlink(unsigned int m_delay);

void setup() {
	Serial.begin(9600); //Set serial
	pinMode(fakeEnergyMetterDiode, OUTPUT); //Set direction output for fake LED
	pinMode(controlDiode, OUTPUT); //Set direction output for control diode - on board
	//Setup Interrupt
	pinMode(photoDiodeInput, INPUT); //Set Interrupt Pin number
	attachInterrupt(digitalPinToInterrupt(photoDiodeInput), setEdge, RISING); //call function on Rising edge
}

void loop() {
	FakeBlink(1000);

	if (interruptFlag == true) {
		digitalWrite(controlDiode, HIGH);
		delay(100);
		digitalWrite(controlDiode, LOW);
		interruptFlag = false;
	}
}

//Interrupt function
void setEdge() {
	interruptFlag = true;
}


void FakeBlink(unsigned int m_delay){
	static bool flaga = true;
	static unsigned int flashFakeDiodeCounter = 0;
	static unsigned long previousMillis = 0;

	unsigned int delay = m_delay / 40;
	unsigned long currentMillis = millis();

	if(flaga)digitalWrite(fakeEnergyMetterDiode, HIGH);

	if (currentMillis - previousMillis >= 40) {
		previousMillis = currentMillis;
		flaga = false;
		flashFakeDiodeCounter++;
		if (flashFakeDiodeCounter > delay) {
			flashFakeDiodeCounter = 0;
			flaga = true;
		} else {
			digitalWrite(fakeEnergyMetterDiode, LOW);
		}
	}

}
