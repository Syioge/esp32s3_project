#include "bsp_at24c02.h"

i2c_master_dev_handle_t at24c02_dev_handle = NULL;

static const char *TAG = "AT24C02";

esp_err_t at24c02_init(void)
{
    if (at24c02_dev_handle != NULL) {
        ESP_LOGW(TAG, "AT24C02 init ok");
        return ESP_OK;
    }

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,  // 7位地址模式[reference:19]
        .device_address  = AT24C02_I2C_ADDR,    // 设置器件地址[reference:20]
        .scl_speed_hz    = 400000,              // 时钟速度: 400 kHz
        .scl_wait_us  = 0,                   // 使用默认超时
    };

    esp_err_t ret = i2c_master_bus_add_device(bus_handle, &dev_config, &at24c02_dev_handle);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "add AT24C02 error: %s", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "AT24C02 init ok");
    }
    return ret;
}

esp_err_t at24c02_byte_write(i2c_master_dev_handle_t dev_handle, uint8_t mem_addr, uint8_t data)
{
    // AT24C02 字节写入时序: START + 器件地址(W) + 内存地址 + 数据 + STOP[reference:21]
    uint8_t write_buf[2] = {mem_addr, data};
    return i2c_master_transmit(dev_handle, write_buf, sizeof(write_buf), 50);
}

esp_err_t at24c02_page_write(i2c_master_dev_handle_t dev_handle, uint8_t start_mem_addr, const uint8_t *data, size_t len)
{
    if (len > AT24C02_PAGE_SIZE) {
        ESP_LOGE(TAG, "page size %d    %d", len, AT24C02_PAGE_SIZE);
        return ESP_ERR_INVALID_SIZE;
    }

    // AT24C02 页写入时序: START + 器件地址(W) + 起始地址 + 数据1 + 数据2... + 数据N + STOP[reference:22]
    uint8_t write_buf[AT24C02_PAGE_SIZE + 1]; // +1 用于起始地址
    write_buf[0] = start_mem_addr;
    memcpy(&write_buf[1], data, len);
    return i2c_master_transmit(dev_handle, write_buf, len + 1, 50);
}
esp_err_t at24c02_current_address_read(i2c_master_dev_handle_t dev_handle, uint8_t *data)
{
    // AT24C02 当前地址读取时序: START + 器件地址(R) + ... + 数据 + NACK + STOP[reference:23]
    return i2c_master_receive(dev_handle, data, 1, 50);
}

esp_err_t at24c02_random_read(i2c_master_dev_handle_t dev_handle, uint8_t mem_addr, uint8_t *data)
{
    // AT24C02 随机读取时序:
    // START + 器件地址(W) + 内存地址 + START + 器件地址(R) + 数据 + NACK + STOP[reference:24]
    return i2c_master_transmit_receive(dev_handle, &mem_addr, 1, data, 1, 50);
}

esp_err_t at24c02_sequential_read(i2c_master_dev_handle_t dev_handle, uint8_t start_mem_addr, uint8_t *buffer, size_t len)
{
    // AT24C02 顺序读取时序:
    // START + 器件地址(W) + 起始地址 + START + 器件地址(R) + 数据1 + ACK + 数据2 + ACK... + 数据N + NACK + STOP[reference:25]
    return i2c_master_transmit_receive(dev_handle, &start_mem_addr, 1, buffer, len, 50);
}
