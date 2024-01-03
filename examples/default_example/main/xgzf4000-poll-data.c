#include "esp_log.h"
#include "xgzf4000.h"

static const char *TAG_XGZF = "XGZF4000_APP";

#define I2C_XGZF4000_ADDR 0x50 // default I2C address of the XGZF4000 sensor
#define I2C_MASTER_SCL_IO    19    // Assign the SCL pin number
#define I2C_MASTER_SDA_IO    18    // Assign the SDA pin number
#define I2C_MASTER_NUM       I2C_NUM_0
#define I2C_MASTER_FREQ_HZ   100000 // I2C master frequency

static xgzf4000_dev_handle_t xgzf4000;

static void poll_air_flow_data(void) {
    uint32_t flow_rate_raw;
    float flow_rate;

    if (xgzf4000_read_air_flow(xgzf4000, &flow_rate_raw, &flow_rate) == ESP_OK) {
        // Convert raw flow rate based on the selected unit
        #ifdef CONFIG_FLOW_RATE_UNIT_LMIN
        flow_rate *= LITERS_PER_MINUTE_FACTOR;
        #elif CONFIG_FLOW_RATE_UNIT_CMH
        flow_rate *= CUBIC_METERS_PER_HOUR_FACTOR;
        #endif

        // Log the flow rate in the selected unit
        #ifdef CONFIG_FLOW_RATE_UNIT_LMIN
        ESP_LOGI(TAG_XGZF, "Raw Flow Rate: %u, Flow Rate: %.2f L/min", flow_rate_raw, flow_rate);
        #elif CONFIG_FLOW_RATE_UNIT_CMH
        ESP_LOGI(TAG_XGZF, "Raw Flow Rate: %u, Flow Rate: %.2f m³/h", flow_rate_raw, flow_rate);
        #endif
    } else {
        ESP_LOGE(TAG_XGZF, "Failed to read air flow data");
    }
}

void app_main(void) {
    int ret = ESP_OK;

    xgzf4000_i2c_config_t i2c_config = {
        .i2c_port = I2C_MASTER_NUM,
        .i2c_addr = I2C_XGZF4000_ADDR,
    };

    ESP_ERROR_CHECK(xgzf4000_new_sensor(I2C_MASTER_NUM, I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO));


    if (init_xgzf4000_sensor() != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize XGZF4000 sensor");
        return;
    }

    while (1) {
        poll_air_flow_data();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    // Clean up
    xgzf4000_del_sensor(xgzf4000);
}
