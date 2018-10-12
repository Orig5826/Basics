
#ifndef _DEMO_H_
#define _DEMO_H_
#include <stdio.h>
#include <string.h>

#include "usbdrv.h"
#include "apdu.h"
#include "encrypt.h"

#define USB_VID         0x4853 //0x2309
#define USB_PID         0x4555 //0x0606

void hs_demo(void);

#endif