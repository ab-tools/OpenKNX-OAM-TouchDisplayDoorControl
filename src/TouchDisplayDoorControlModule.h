#include "OpenKNX.h"
#include <lvgl.h>
#include "TouchDisplayModule.h"

#define DISPLAY_SLEEP_DELAY 10000

class TouchDisplayDoorControlModule : public OpenKNX::Module
{
	public:
		TouchDisplayDoorControlModule(TouchDisplayModule* touchDisplayModule);

		void loop() override;
		void setup() override;
		void processAfterStartupDelay() override;
		void processInputKo(GroupObject &ko) override;

		const std::string name() override;
		const std::string version() override;
		// void writeFlash() override;
		// void readFlash(const uint8_t* data, const uint16_t size) override;
		// uint16_t flashSize() override;
	
	private:
		enum DoorState {
			UNDEFINED,
			OPEN,
			CLOSED,
			AUTO
		};

		static void ui_ImgButtonClosed_event(lv_event_t * event);
		static void ui_ImgButtonOpen_event(lv_event_t * event);
		static void ui_ImgButtonAuto_event(lv_event_t * event);
		static void ui_Main_event(lv_event_t * event);
		static void update_button_states(DoorState newDoorState);

		inline static TouchDisplayModule* _touchDisplayModule;
		inline static DoorState doorState;
};