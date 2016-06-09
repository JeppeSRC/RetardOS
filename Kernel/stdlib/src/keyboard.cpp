#include <keyboard.h>
#include <sys.h>

unsigned char keyboard_ctrl_read_status() {
	return _inb(KEYBOARD_IO_CONTROLLER);
}

unsigned char keyboard_enc_read_buffer() {
	while ((keyboard_ctrl_read_status() & KEYBOARD_CTRL_STATUS_MASK_OUT_BUFFER) != 1);

	return _inb(KEYBOARD_IO_ENCODER);
}

void keyboard_ctrl_send_cmd(unsigned char cmd) {
	while ((keyboard_ctrl_read_status() & KEYBOARD_CTRL_STATUS_MASK_IN_BUFFER) != 0);

	_outb(KEYBOARD_IO_CONTROLLER, cmd);
}

void keyboard_enc_send_cmd(unsigned char cmd) {
	while ((keyboard_ctrl_read_status() & KEYBOARD_CTRL_STATUS_MASK_IN_BUFFER) != 0);

	_outb(KEYBOARD_IO_ENCODER, cmd);
}

void keyboard_set_leds(bool scroll_lock, bool num_lock, bool caps_lock) {

	unsigned char data = (scroll_lock ? 1 : 0) | (num_lock ? 2 : 0) | (caps_lock ? 4 : 0);

	keyboard_enc_send_cmd(KEYBOARD_ENC_CMD_SET_LEDS);
	keyboard_enc_send_cmd(data);
}