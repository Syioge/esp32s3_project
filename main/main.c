#include "freertos/FreeRTOS.h" 
#include "freertos/task.h" 
#include "nvs_flash.h" 
#include "esp_system.h" 
#include "esp_chip_info.h" 
#include "esp_psram.h" 
#include "esp_flash.h" 
#include "string.h"
#include "bsp_iic.h"
#include "esp_log.h"
#include "bsp_at24c02.h"

static const char *TAG = "MAIN";
void app_main(void)
{
    esp_err_t ret; 
    uint32_t flash_size; 
    esp_chip_info_t chip_info;            /* 定义芯片信息结构体变量 */ 
    ret = nvs_flash_init();              /* 初始化NVS */ 
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES  
        || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) 
    { 
        ESP_ERROR_CHECK(nvs_flash_erase()); 
        ret = nvs_flash_init(); 
    } 
    esp_flash_get_size(NULL, &flash_size);     /* 获取FLASH大小 */ 
    esp_chip_info(&chip_info); 
    printf("内核：cup数量%d\n",chip_info.cores); /* 获取CPU内核数并显示 */ 
/* 获取FLASH大小并显示 */ 
    printf("FLASH size:%ld MB flash\n",flash_size / (1024 * 1024));  
/* 获取PARAM大小并显示 */ 
    printf("PSRAM size: %d bytes\n", esp_psram_get_size());          
    
    bsp_iic_init();
    at24c02_init();
    
    uint8_t test_addr = 0x00;
    uint8_t write_data = 0xA5;
    uint8_t read_data = 0x00;

    // 字节写入
    if (at24c02_byte_write(at24c02_dev_handle, test_addr, write_data) == ESP_OK) {
        ESP_LOGI(TAG, "on addr 0x%02X write 0x%02X ok", test_addr, write_data);
        vTaskDelay(pdMS_TO_TICKS(10)); // 必须等待内部写周期完成 (≥5ms)
    }

    // 随机读取验证
    if (at24c02_random_read(at24c02_dev_handle, test_addr, &read_data) == ESP_OK) {
        ESP_LOGI(TAG, "slave_addr 0x%02X read: 0x%02X", test_addr, read_data);
        if (read_data == write_data) {
            ESP_LOGI(TAG, "data ok!");
        } else {
            ESP_LOGE(TAG, "data error!");
        }
    }

    // 页写入示例
    uint8_t page_data[AT24C02_PAGE_SIZE] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    if (at24c02_page_write(at24c02_dev_handle, 0x10, page_data, sizeof(page_data)) == ESP_OK) {
        ESP_LOGI(TAG, "page (addr : 0x10) ok");
        vTaskDelay(pdMS_TO_TICKS(10)); // 等待内部写周期完成
    }

    // 顺序读取验证 (从刚才写入的页地址0x10开始)
    uint8_t read_buffer[AT24C02_PAGE_SIZE] = {0};
    if (at24c02_sequential_read(at24c02_dev_handle, 0x10, read_buffer, sizeof(read_buffer)) == ESP_OK) {
        ESP_LOGI(TAG, "read (addr 0x10, len %d) ok", sizeof(read_buffer));
        ESP_LOG_BUFFER_HEX(TAG, read_buffer, sizeof(read_buffer));
    }

    while(1) 
    { 
        printf("Hello-ESP32\r\n"); 
        vTaskDelay(1000); 
    } 
}
