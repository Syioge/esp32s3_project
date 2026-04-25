#ifndef _BSP_AT24C02_H
#define _BSP_AT24C02_H

#include "bsp_iic.h"
#include "esp_log.h"
#define AT24C02_I2C_ADDR          0x50        // 7位器件地址 (A2,A1,A0 均接GND)[reference:16]
#define AT24C02_MEMORY_ADDR_BITS  8           // 内存地址宽度 (bit)，可寻址0x00-0xFF[reference:17]
#define AT24C02_PAGE_SIZE         8           // 页写入大小 (字节)[reference:18]
extern i2c_master_dev_handle_t at24c02_dev_handle;

esp_err_t at24c02_init(void);
esp_err_t at24c02_byte_write(i2c_master_dev_handle_t dev_handle, uint8_t mem_addr, uint8_t data);
esp_err_t at24c02_page_write(i2c_master_dev_handle_t dev_handle, uint8_t start_mem_addr, const uint8_t *data, size_t len);
esp_err_t at24c02_current_address_read(i2c_master_dev_handle_t dev_handle, uint8_t *data);
esp_err_t at24c02_random_read(i2c_master_dev_handle_t dev_handle, uint8_t mem_addr, uint8_t *data);
esp_err_t at24c02_sequential_read(i2c_master_dev_handle_t dev_handle, uint8_t start_mem_addr, uint8_t *buffer, size_t len);


#endif
