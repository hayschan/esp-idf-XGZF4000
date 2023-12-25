/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include "aht20.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_check.h"

#include "aht20_reg.h"

const static char *TAG = "AHT20";

typedef struct {
    i2c_port_t  i2c_port;
    uint8_t     i2c_addr;
} xgzf4000_dev_t;

static esp_err_t xgzf4000_read_flow_data(xgzf4000_dev_handle_t dev, uint8_t *data, size_t len)
{
    xgzf4000_dev_t *sens = (xgzf4000_dev_t *) dev;
    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    // Start I2C communication
    ret = i2c_master_start(cmd);
    assert(ESP_OK == ret);

    // Specify the sensor's I2C address and set read mode
    ret = i2c_master_write_byte(cmd, sens->i2c_addr << 1 | I2C_MASTER_READ, true);
    assert(ESP_OK == ret);

    // Read the specified number of bytes from the sensor
    if (len > 1) {
        ret = i2c_master_read(cmd, data, len - 1, I2C_MASTER_ACK);
        assert(ESP_OK == ret);
    }
    ret = i2c_master_read_byte(cmd, data + len - 1, I2C_MASTER_NACK);
    assert(ESP_OK == ret);

    // Send stop condition
    ret = i2c_master_stop(cmd);
    assert(ESP_OK == ret);

    // Execute the command
    ret = i2c_master_cmd_begin(sens->i2c_port, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t xgzf4000_read_air_flow(xgzf4000_dev_handle_t handle, uint32_t *flow_rate_raw, float *flow_rate)
{
    uint8_t buf[2]; // Buffer for reading the two bytes of flow data

    ESP_RETURN_ON_FALSE(handle, ESP_ERR_INVALID_ARG, TAG, "invalid device handle pointer");

    // Read the flow data from the sensor
    ESP_RETURN_ON_ERROR(xgzf4000_read_flow_data(handle, buf, 2), TAG, "I2C read/write error");

    // Combine the two bytes into a single integer
    *flow_rate_raw = ((uint32_t)buf[0] << 8) | buf[1];

    // Calculate the actual flow rate using the proportionality factor K
    *flow_rate = (float)(*flow_rate_raw) / K_FACTOR; // K_FACTOR needs to be defined based on sensor range

    return ESP_OK;
}


esp_err_t xgzf4000_new_sensor(const xgzf4000_i2c_config_t *i2c_conf, xgzf4000_dev_handle_t *handle_out)
{
    ESP_LOGI(TAG, "Initializing XGZF4000 Air Flow Sensor");

    ESP_RETURN_ON_FALSE(i2c_conf, ESP_ERR_INVALID_ARG, TAG, "invalid device config pointer");
    ESP_RETURN_ON_FALSE(handle_out, ESP_ERR_INVALID_ARG, TAG, "invalid device handle pointer");

    xgzf4000_dev_t *handle = calloc(1, sizeof(xgzf4000_dev_t));
    ESP_RETURN_ON_FALSE(handle, ESP_ERR_NO_MEM, TAG, "memory allocation for device handler failed");

    handle->i2c_port = i2c_conf->i2c_port;
    handle->i2c_addr = i2c_conf->i2c_addr; // Default I2C address for XGZF4000 is 0x50

    *handle_out = handle;
    return ESP_OK;
}


esp_err_t aht20_del_sensor(aht20_dev_handle_t handle)
{
    ESP_RETURN_ON_FALSE(handle, ESP_ERR_INVALID_ARG, TAG, "invalid device handle pointer");

    free(handle);

    return ESP_OK;
}