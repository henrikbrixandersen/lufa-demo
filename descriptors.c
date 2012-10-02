#include <LUFA/Drivers/USB/USB.h>

#include "descriptors.h"

#define DEMO_MANUFACTURER_STR     L"Henrik Brix Andersen"
#define DEMO_MANUFACTURER_STR_LEN 20
#define DEMO_PRODUCT_STR          L"Demo Controller"
#define DEMO_PRODUCT_STR_LEN      17

#define DEMO_VID       0x03EB /* Atmel VID */
#define DEMO_PID       0x2044 /* Derived from the LUFA CDC Demo Application, use same PID */

#define DEMO_VERSION   00.10  /* BCD */
#define DEMO_MAX_POWER 100    /* mA */

#define LANGUAGE_STR_INDEX          0x00
#define DEMO_MANUFACTURER_STR_INDEX 0x01
#define DEMO_PRODUCT_STR_INDEX      0x02

const USB_Descriptor_Device_t PROGMEM device_descriptor = {
	.Header                 = {
		.Size = sizeof(USB_Descriptor_Device_t),
		.Type = DTYPE_Device,
	},
	.USBSpecification       = VERSION_BCD(01.10),
	.Class                  = CDC_CSCP_CDCClass,
	.SubClass               = CDC_CSCP_NoSpecificSubclass,
	.Protocol               = CDC_CSCP_NoSpecificProtocol,
	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,
	.VendorID               = DEMO_VID,
	.ProductID              = DEMO_PID,
	.ReleaseNumber          = VERSION_BCD(DEMO_VERSION),
	.ManufacturerStrIndex   = DEMO_MANUFACTURER_STR_INDEX,
	.ProductStrIndex        = DEMO_PRODUCT_STR_INDEX,
	.SerialNumStrIndex      = USE_INTERNAL_SERIAL,
	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS,
};

const USB_Descriptor_Configuration_t PROGMEM configuration_descriptor = {
	.Config = {
		.Header = {
			.Size = sizeof(USB_Descriptor_Configuration_Header_t),
			.Type = DTYPE_Configuration,
		},
		.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
		.TotalInterfaces        = 2,
		.ConfigurationNumber    = 1,
		.ConfigurationStrIndex  = NO_DESCRIPTOR,
		.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),
		.MaxPowerConsumption    = USB_CONFIG_POWER_MA(DEMO_MAX_POWER),
	},
	.CDC_CCI_Interface = {
		.Header = {
			.Size = sizeof(USB_Descriptor_Interface_t),
			.Type = DTYPE_Interface,
		},
		.InterfaceNumber   = 0,
		.AlternateSetting  = 0,
		.TotalEndpoints    = 1,
		.Class             = CDC_CSCP_CDCClass,
		.SubClass          = CDC_CSCP_ACMSubclass,
		.Protocol          = CDC_CSCP_ATCommandProtocol,
		.InterfaceStrIndex = NO_DESCRIPTOR,
	},
	.CDC_Functional_Header = {
		.Header = {
			.Size = sizeof(USB_CDC_Descriptor_FunctionalHeader_t),
			.Type = DTYPE_CSInterface,
		},
		.Subtype          = CDC_DSUBTYPE_CSInterface_Header,
		.CDCSpecification = VERSION_BCD(01.10),
	},
	.CDC_Functional_ACM = {
		.Header = {
			.Size = sizeof(USB_CDC_Descriptor_FunctionalACM_t),
			.Type = DTYPE_CSInterface,
		},
		.Subtype      = CDC_DSUBTYPE_CSInterface_ACM,
		.Capabilities = 0x06,
	},
	.CDC_Functional_Union = {
		.Header = {
			.Size = sizeof(USB_CDC_Descriptor_FunctionalUnion_t),
			.Type = DTYPE_CSInterface,
		},
		.Subtype               = CDC_DSUBTYPE_CSInterface_Union,
		.MasterInterfaceNumber = 0,
		.SlaveInterfaceNumber  = 1,
	},
	.CDC_NotificationEndpoint = {
		.Header = {
			.Size = sizeof(USB_Descriptor_Endpoint_t),
			.Type = DTYPE_Endpoint,
		},
		.EndpointAddress   = DEMO_CDC_NOTIFICATION_EPADDR,
		.Attributes        = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize      = DEMO_CDC_NOTIFICATION_EPSIZE,
		.PollingIntervalMS = 0xFF,
	},
	.CDC_DCI_Interface = {
		.Header = {
			.Size = sizeof(USB_Descriptor_Interface_t),
			.Type = DTYPE_Interface,
		},
		.InterfaceNumber   = 1,
		.AlternateSetting  = 0,
		.TotalEndpoints    = 2,
		.Class             = CDC_CSCP_CDCDataClass,
		.SubClass          = CDC_CSCP_NoDataSubclass,
		.Protocol          = CDC_CSCP_NoDataProtocol,
		.InterfaceStrIndex = NO_DESCRIPTOR,
	},
	.CDC_DataOutEndpoint = {
		.Header = {
			.Size = sizeof(USB_Descriptor_Endpoint_t),
			.Type = DTYPE_Endpoint,
		},
		.EndpointAddress   = DEMO_CDC_RX_EPADDR,
		.Attributes        = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize      = DEMO_CDC_TXRX_EPSIZE,
		.PollingIntervalMS = 0x05,
	},
	.CDC_DataInEndpoint = {
		.Header = {
			.Size = sizeof(USB_Descriptor_Endpoint_t),
			.Type = DTYPE_Endpoint,
		},
		.EndpointAddress   = DEMO_CDC_TX_EPADDR,
		.Attributes        = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize      = DEMO_CDC_TXRX_EPSIZE,
		.PollingIntervalMS = 0x05,
	}
};

const USB_Descriptor_String_t PROGMEM language_string = {
	.Header = {
		.Size = USB_STRING_LEN(1),
		.Type = DTYPE_String,
	},
	.UnicodeString = {
		LANGUAGE_ID_ENG,
	},
};

const USB_Descriptor_String_t PROGMEM manufacturer_string = {
	.Header = {
		.Size = USB_STRING_LEN(DEMO_MANUFACTURER_STR_LEN),
		.Type = DTYPE_String,
	},
	.UnicodeString = DEMO_MANUFACTURER_STR,
};

const USB_Descriptor_String_t PROGMEM product_string = {
	.Header = {
		.Size = USB_STRING_LEN(DEMO_PRODUCT_STR_LEN),
		.Type = DTYPE_String,
	},
	.UnicodeString = DEMO_PRODUCT_STR,
};

uint16_t
CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, const void** const DescriptorAddress)
{
	const uint8_t desc_type = (wValue >> 8);
	const uint8_t desc_index = (wValue & 0xFF);
	const void* addr = NULL;
	uint16_t size = NO_DESCRIPTOR;

	switch (desc_type) {
	case DTYPE_Device:
		addr = &device_descriptor;
		size = sizeof(USB_Descriptor_Device_t);
		break;

	case DTYPE_Configuration:
		addr = &configuration_descriptor;
		size = sizeof(USB_Descriptor_Configuration_t);
		break;

	case DTYPE_String:
		switch (desc_index) {
		case LANGUAGE_STR_INDEX:
			addr = &language_string;
			size = pgm_read_byte(&language_string.Header.Size);
			break;

		case DEMO_MANUFACTURER_STR_INDEX:
			addr = &manufacturer_string;
			size = pgm_read_byte(&manufacturer_string.Header.Size);
			break;

		case DEMO_PRODUCT_STR_INDEX:
			addr = &product_string;
			size = pgm_read_byte(&product_string.Header.Size);
			break;
		}

		break;
	}

	*DescriptorAddress = addr;
	return size;
}

