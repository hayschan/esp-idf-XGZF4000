/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_types.h"
#include "esp_err.h"

#include "driver/i2c.h"

/**
 * @brief Type of XGZF4000 device handle
 *
 */
typedef void *xgzf4000_dev_handle_t;

/**
 * @brief XGZF4000 I2C config struct
 *
 */
typedef struct {
    i2c_port_t  i2c_port;           /*!< I2C port used to connecte XGZF4000 device */
    uint8_t     i2c_addr;           /*!< I2C address of XGZF4000 device, can be 0x38 or 0x39 according to A0 pin */
} xgzf4000_i2c_config_t;

/**
 * @brief Create new XGZF4000 device handle.
 *
 * @param[in]  i2c_conf Config for I2C used by XGZF4000
 * @param[out] handle_out New XGZF4000 device handle
 * @return
 *          - ESP_OK                  Device handle creation success.
 *          - ESP_ERR_INVALID_ARG     Invalid device handle or argument.
 *          - ESP_ERR_NO_MEM          Memory allocation failed.
 *
 */
esp_err_t xgzf4000_new_sensor(const xgzf4000_i2c_config_t *i2c_conf, xgzf4000_dev_handle_t *handle_out);

/**
 * @brief Delete XGZF4000 device handle.
 *
 * @param[in] handle XGZF4000 device handle
 * @return
 *          - ESP_OK                  Device handle deletion success.
 *          - ESP_ERR_INVALID_ARG     Invalid device handle or argument.
 *
 */
esp_err_t xgzf4000_del_sensor(xgzf4000_dev_handle_t handle);

/**
 * @brief Read the air flow rate data from the XGZF4000 sensor
 *
 * @param[in]  *handle points to an XGZF4000 handle structure
 * @param[out] *flow_rate_raw points to a buffer where the raw flow rate data will be stored
 * @param[out] *flow_rate points to a buffer where the calculated flow rate (in litres/minute) will be stored
 *
 * @return
 *     - ESP_OK on successful reading of the flow rate data
 *     - ESP_FAIL on failure to read the flow rate data
 */
esp_err_t xgzf4000_read_air_flow(xgzf4000_dev_handle_t handle, uint32_t *flow_rate_raw, float *flow_rate)


#ifdef __cplusplus
}
#endif