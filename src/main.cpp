#include <Arduino.h>
#include "OpenKNX.h"
#include "TouchDisplayDoorControlModule.h"

void setup()
{
    TouchDisplayModule* touchDisplayModule = new TouchDisplayModule();

    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    openknx.addModule(1, touchDisplayModule);
    openknx.addModule(2, new TouchDisplayDoorControlModule(touchDisplayModule));
    openknx.setup();

    // call direct for testing without KNX connected
    //openknx.modules.list[0]->setup();
    //openknx.modules.list[1]->setup();
}

void loop()
{
	openknx.loop();

    // call direct for testing without KNX connected
    //openknx.modules.list[0]->loop();
    //openknx.modules.list[1]->loop();
}