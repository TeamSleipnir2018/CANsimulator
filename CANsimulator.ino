#include <stdint.h>
#include <FlexCAN.h>

// Vehicle values
uint16_t rpm;
uint16_t oilTemp;
uint16_t waterTemp;
uint16_t brakeTemp;
uint16_t gear;
uint16_t speed;
uint16_t voltage;
bool fanOn;

uint16_t speedCount;
const uint16_t MAX_RPM = 14000;

CAN_message_t msg1;
CAN_message_t msg2;

void demo() {
	if (rpm != MAX_RPM) {
		rpm += 25;
	}
	else {
		oilTemp = random(473, 483);
		waterTemp = random(403, 423);
		brakeTemp = random(373, 423);
		voltage = random(11900, 12900);

		if (gear < 6) {
			gear++;
			rpm = 2000;
		}
		else {
			rpm = 13500;
		}
	}

	if (speed < 255 && gear != 0) {
		if (speedCount == 5) {
			speed++;
			speedCount = 0;
		}
		else {
			speedCount++;
		}
	}
}

void setup() {

	// Initialize the CAN bus
	Can0.begin(500000);
	Serial.begin(9600);

	msg1.ext = 0;
	msg1.id = 0x1;
	msg1.len = 8;

	msg2.ext = 0;
	msg2.id = 0x2;
	msg2.len = 8;
}

void loop() {

	demo();
	
	msg1.buf[0] = (uint8_t)rpm;
	msg1.buf[1] = rpm >> 8;
	msg1.buf[2] = (uint8_t)voltage;
	msg1.buf[3] = voltage >> 8;
	msg1.buf[4] = (uint8_t)waterTemp;
	msg1.buf[5] = waterTemp >> 8;
	msg1.buf[6] = (uint8_t)speed;
	msg1.buf[7] = speed >> 8;

	msg1.buf[0]++;
	Can0.write(msg1);
	msg1.buf[0]++;
	Can0.write(msg1);
	msg1.buf[0]++;
	Can0.write(msg1);
	msg1.buf[0]++;
	Can0.write(msg1);
	msg1.buf[0]++;
	Can0.write(msg1);
	delay(20);

	msg2.buf[0] = (uint8_t)oilTemp;
	msg2.buf[1] = oilTemp >> 8;
	msg2.buf[2] = (uint8_t)gear;
	msg2.buf[3] = gear >> 8;
	msg2.buf[4] = (uint8_t)waterTemp;
	msg2.buf[5] = waterTemp >> 8;
	msg2.buf[6] = (uint8_t)speed;
	msg2.buf[7] = speed >> 8;
	
	msg2.buf[0]++;
	Can0.write(msg2);
	msg2.buf[0]++;
	Can0.write(msg2);
	msg2.buf[0]++;
	Can0.write(msg2);
	msg2.buf[0]++;
	Can0.write(msg2);
	msg2.buf[0]++;
	Can0.write(msg2);
	delay(20);
}
