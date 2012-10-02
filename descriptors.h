#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

#include <LUFA/Drivers/USB/USB.h>

#define DEMO_CDC_NOTIFICATION_EPADDR        (ENDPOINT_DIR_IN  | 2)
#define DEMO_CDC_TX_EPADDR                  (ENDPOINT_DIR_IN  | 3)
#define DEMO_CDC_RX_EPADDR                  (ENDPOINT_DIR_OUT | 4)

#define DEMO_CDC_NOTIFICATION_EPSIZE        8
#define DEMO_CDC_TXRX_EPSIZE                16

typedef struct {
	USB_Descriptor_Configuration_Header_t    Config;

	// CDC Control Interface
	USB_Descriptor_Interface_t               CDC_CCI_Interface;
	USB_CDC_Descriptor_FunctionalHeader_t    CDC_Functional_Header;
	USB_CDC_Descriptor_FunctionalACM_t       CDC_Functional_ACM;
	USB_CDC_Descriptor_FunctionalUnion_t     CDC_Functional_Union;
	USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;

	// CDC Data Interface
	USB_Descriptor_Interface_t               CDC_DCI_Interface;
	USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
	USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
} USB_Descriptor_Configuration_t;

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, const void** const DescriptorAddress)
	ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif /* _DESCRIPTORS_H */

