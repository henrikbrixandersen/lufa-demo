TARGET = lufa-demo

MCU   = atmega32u4
ARCH  = AVR8
BOARD = ADAFRUITU4

F_CPU = 16000000
F_USB = $(F_CPU)

OPTIMIZATION = s
LUFA_PATH    = ../lufa/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER

AVRDUDE_PORT       = /dev/tty.usbmodem641
AVRDUDE_PROGRAMMER = avr109

SRC = 	descriptors.c \
	main.c \
	usb.c \
	$(LUFA_SRC_USB) \
	$(LUFA_SRC_USBCLASS)

all:

include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
