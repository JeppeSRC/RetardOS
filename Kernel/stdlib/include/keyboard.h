#pragma once

enum KEYBOARD_CTRL_STATUS_MASK {
	KEYBOARD_CTRL_STATUS_MASK_OUT_BUFFER = 0x01,
	KEYBOARD_CTRL_STATUS_MASK_IN_BUFFER = 0x02,
	KEYBOARD_CTRL_STATUS_MASK_SYSTEM = 0x04,
	KEYBOARD_CTRL_STATUS_MASK_CMD_DATA = 0x08,
	KEYBOARD_CTRL_STATUS_MASK_LOCKED = 0x10,
	KEYBOARD_CTRL_STATUS_MASK_AUX_BUFFER = 0x20,
	KEYBOARD_CTRL_STATUS_MASK_TIMEOUT = 0x40,
	KEYBOARD_CTRL_STATUS_MASK_PARITY = 0x80
};

enum KEYBOARD_IO {
	KEYBOARD_IO_ENCODER = 0x60,
	KEYBOARD_IO_CONTROLLER = 0x64
};

enum KEYBOARD_ENC_CMD {
	KEYBOARD_ENC_CMD_SET_LEDS = 0xED,
	KEYBOARD_ENC_CMD_ECHO = 0xEE,
	KEYBOARD_ENC_CMD_SET_ALT_SCANCODES = 0xF0,
	KEYBOARD_ENC_CMD_ENABLE_KEYBOARD = 0xF4,
	KEYBOARD_ENC_CMD_RESEND_LAST = 0xFE,
	KEYBOARD_ENC_CMD_RST_AND_POST = 0xFF
};

extern uint8 keyboard_ctrl_read_status();
extern uint8 keyboard_enc_read_buffer();

extern void keyboard_ctrl_send_cmd(uint8 cmd);
extern void keyboard_enc_send_cmd(uint8 cmd);


extern void keyboard_set_leds(bool scroll_lock, bool num_lock, bool caps_lock);