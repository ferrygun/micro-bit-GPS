#include "MicroBit.h"
MicroBit uBit;

#define EVENT_ID    8888
#define DC_BUTTON_LEFT   76
#define DC_BUTTON_RIGHT  82
#define DC_BUTTON_STOP   82


void onConnected(MicroBitEvent) {
   uBit.display.print("C");
}

void onDisconnected(MicroBitEvent){
   uBit.display.print("D");
}

void onButton(MicroBitEvent e) {
	if (e.source == MICROBIT_ID_BUTTON_A) {
		//uBit.display.scroll("BTN A UP");
		MicroBitEvent evt(EVENT_ID, 1);
    }

	if (e.source == MICROBIT_ID_BUTTON_B) {
		//uBit.display.scroll("BTN B UP");
		MicroBitEvent evt(EVENT_ID, 2);
    }
}

void onControllerEvent(MicroBitEvent e) {
	if (e.value == DC_BUTTON_LEFT)  {
		uBit.io.P0.setServoValue(90);
	}

	if (e.value == DC_BUTTON_RIGHT)  {
		uBit.io.P0.setServoValue(180);
	}

}

int main() {
    uBit.init();
	uBit.display.scroll("DC");

    new MicroBitTemperatureService(*uBit.ble, uBit.thermometer);

	uBit.messageBus.listen(EVENT_ID, 0, onControllerEvent);
	uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
	uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButton);
	uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButton);

	//uBit.messageBus.listen(EVENT_ID, 0, onControllerEvent);

    release_fiber();
}