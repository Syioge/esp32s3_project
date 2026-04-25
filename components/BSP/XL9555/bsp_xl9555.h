#ifndef _BSP_XL9555_H
#define _BSP_XL9555_H

#include "driver/i2c_master.h"
#include "bsp_iic.h"
#include "esp_log.h"
#include <string.h>
#include "esp_io_expander.h"
#include "esp_io_expander_xl9555.h"

#ifdef __cplusplus
extern "C" {
#endif

#define XL9555_BEEP_IO_NUM      IO_EXPANDER_PIN_NUM_3    

void xl9555_init(void);
void xl9555_set_beep_mode(uint8_t status);
#ifdef __cplusplus
}
#endif

#endif
