/*
 * File: xgzf4000_reg.h
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

/**
 * @brief chip information definition
 */
#define CHIP_NAME                           "CFSENSOR XGZF4000"   /**< chip name */
#define SUPPLY_VOLTAGE_MIN                  (4f)          /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX                  (5.5f)          /**< chip max supply voltage */
#define TEMPERATURE_MIN                     (0.0f)        /**< chip min working temperature */
#define TEMPERATURE_MAX                     (50.0f)        /**< chip max working temperature */
#define PRESSURE_MAX                        (0.2f)        /**< chip max working pressure */
