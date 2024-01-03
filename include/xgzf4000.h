/*
 * File: xgzf4000.c
 * Author: Hays Chan
 * Year: 2023
 *
 * This file is part of the XGZF4000 Air Flow Sensor Driver project.
 *
 * SPDX-FileCopyrightText: 2023 Hays Chan
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_types.h"
#include "esp_err.h"

#include "driver/i2c.h"

const static char *TAG = "XGZF4000";

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


esp_err_t xgzf4000_new_sensor(i2c_port_t i2c_num, int sda_pin, int scl_pin);

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
esp_err_t xgzf4000_read_air_flow(xgzf4000_dev_handle_t handle, uint32_t *flow_rate_raw, float *flow_rate);

#ifdef __cplusplus
}
#endif