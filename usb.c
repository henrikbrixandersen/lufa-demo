#include <stdio.h>

#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/USB/USB.h>

#include "descriptors.h"

USB_ClassInfo_CDC_Device_t demo_controller_cdc_interface = {
	.Config = {
		.ControlInterfaceNumber   = 0,
		.DataINEndpoint           = {
			.Address          = DEMO_CDC_TX_EPADDR,
			.Size             = DEMO_CDC_TXRX_EPSIZE,
			.Banks            = 1,
		},
		.DataOUTEndpoint = {
			.Address          = DEMO_CDC_RX_EPADDR,
			.Size             = DEMO_CDC_TXRX_EPSIZE,
			.Banks            = 1,
		},
		.NotificationEndpoint = {
			.Address          = DEMO_CDC_NOTIFICATION_EPADDR,
			.Size             = DEMO_CDC_NOTIFICATION_EPSIZE,
			.Banks            = 1,
		},
	},
};

void
usb_init(void) {
	USB_Init();
	CDC_Device_CreateBlockingStream(&demo_controller_cdc_interface, stdout);
}

void
EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t *const CDCInterfaceInfo)
{
	if (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR) {
		LEDs_TurnOnLEDs(LEDS_LED1);
	} else {
		LEDs_TurnOffLEDs(LEDS_LED1);
	}
}

void
EVENT_USB_Device_ConfigurationChanged(void)
{
	if (!CDC_Device_ConfigureEndpoints(&demo_controller_cdc_interface))
		USB_ResetInterface();
}

void
EVENT_USB_Device_ControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&demo_controller_cdc_interface);
}
