// xl9555.c
#include "bsp_xl9555.h"

esp_io_expander_handle_t xl9555_dev_handle = NULL;          

void xl9555_init(void)
{
    ESP_ERROR_CHECK(esp_io_expander_new_i2c_xl9555(bus_handle, 0x20, &xl9555_dev_handle));
}


void xl9555_set_beep_mode(uint8_t status)
{
    ESP_ERROR_CHECK(esp_io_expander_set_dir(xl9555_dev_handle, XL9555_BEEP_IO_NUM, IO_EXPANDER_OUTPUT));
    ESP_ERROR_CHECK(esp_io_expander_set_level(xl9555_dev_handle, XL9555_BEEP_IO_NUM, status));
}
