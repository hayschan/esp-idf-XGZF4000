/*
 * File: xgzf4000.chip.c
 * Author: Hays Chan
 * Year: 2023
 *
 * This file is part of the XGZF4000 Air Flow Sensor Driver project.
 *
 * SPDX-FileCopyrightText: 2023 Hays Chan
 *
 * SPDX-License-Identifier: MIT
 */

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

const int XGZF4000_I2C_ADDRESS = 0x50; // Default I2C address for the sensor

typedef struct {
  uint16_t flow_data; // Holds the 16-bit gas flow data
  uint8_t high_byte;  // High byte of flow data
  uint8_t low_byte;   // Low byte of flow data
  uint8_t read_state; // Keeps track of the read state (0 for high byte, 1 for low byte)
  uint32_t gas_flow_rate_attr; // Threshold attribute for gas flow rate slider
} chip_state_t;

static bool on_i2c_connect(void *user_data, uint32_t address, bool connect);
static uint8_t on_i2c_read(void *user_data);
static void on_i2c_disconnect(void *user_data);
// no need to implement on_i2c_write(), it's not used by the gas air flow sensor

void chip_init() {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  chip->flow_data = 0; // Initialize flow data to 0
  chip->read_state = 0; // Initialize read state to 0

  const i2c_config_t i2c_config = {
    .user_data = chip,
    .address = XGZF4000_I2C_ADDRESS,
    .scl = pin_init("SCL", INPUT),
    .sda = pin_init("SDA", INPUT),
    .connect = on_i2c_connect,
    .read = on_i2c_read,
    .disconnect = on_i2c_disconnect,
  };
  i2c_init(&i2c_config);

  // This attribute can be edited by the user through on-screen slider. It's defined in wokwi-custom-part.json:
  chip->gas_flow_rate_attr = attr_init("airFlowRate", 25);

  printf("XGZF4000 Air Flow Sensor Simulation Initialized.\n");
}

static void gas_flow_rate_updated(chip_state_t *chip)
{
    const uint32_t threshold = attr_read(chip->gas_flow_rate_attr);
}

bool on_i2c_connect(void *user_data, uint32_t address, bool connect) {
  return true; /* Ack */
}

uint8_t on_i2c_read(void *user_data) {
    chip_state_t *chip = (chip_state_t *)user_data;

    chip->flow_data = attr_read(chip->gas_flow_rate_attr); // Update flow data edited by user through slider

    // Split the 16-bit flow data into high and low bytes
    chip->high_byte = (chip->flow_data >> 8) & 0xFF; // Extract high byte
    chip->low_byte = chip->flow_data & 0xFF;        // Extract low byte

    // Alternate between sending high byte and low byte
    if (chip->read_state == 0) {
        chip->read_state = 1; // Next read will be the low byte
        return chip->high_byte;
    } else {
        chip->read_state = 0; // Reset for next cycle, next read will be the high byte
        return chip->low_byte;
    }
}

void on_i2c_disconnect(void *user_data) {
    // Do nothing
}