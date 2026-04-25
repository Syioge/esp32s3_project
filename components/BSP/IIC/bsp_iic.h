#ifndef _BSP_IIC_H_
#define _BSP_IIC_H_

#include "driver/i2c_master.h"
#include "esp_log.h"


extern i2c_master_bus_handle_t bus_handle;

void bsp_iic_init(void);
#endif 
