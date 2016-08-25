#pragma once

#include "stddef.h"

uint8	_inb(uint16 port);
uint16	_inw(uint16 port);
uint32 _ind(uint16 port);

void _outb(uint16 port, uint8 value);
void _outw(uint16 port, uint16 value);
void _outd(uint16 port, uint32 value);



void _inb(uint16 port, void* byteStruct);
void _inw(uint16 port, void* byteStruct);
void _ind(uint16 port, void* byteStruct);

void _outb(uint16 port, void* byteStruct);
void _outw(uint16 port, void* byteStruct);
void _outd(uint16 port, void* byteStruct);



void _sleep(uint32 seconds);

