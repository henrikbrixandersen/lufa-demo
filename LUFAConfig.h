#ifndef _LUFA_CONFIG_H_
#define _LUFA_CONFIG_H_

/* General USB Driver Related Tokens */
#define USE_STATIC_OPTIONS (USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)
#define USB_DEVICE_ONLY
#define NO_SOF_EVENTS

/* USB Device Mode Driver Related Tokens */
#define USE_FLASH_DESCRIPTORS
#define FIXED_CONTROL_ENDPOINT_SIZE 8
#define FIXED_NUM_CONFIGURATIONS    1

#endif /* _LUFA_CONFIG_H_ */
