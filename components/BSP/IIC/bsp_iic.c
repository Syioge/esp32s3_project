#include "bsp_iic.h"

i2c_master_bus_handle_t bus_handle;


void bsp_iic_init(void)
{
    i2c_master_bus_config_t i2c_master_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = GPIO_NUM_41,
        .scl_io_num = GPIO_NUM_42,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority = 2,
        .flags.enable_internal_pullup = true,
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_master_config, &bus_handle));
}

