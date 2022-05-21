/**  
 *                  Copyright 2022 Javinator9889
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at

 *            http://www.apache.org/licenses/LICENSE-2.0

 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#ifndef OBDII_H
#include <WString.h>
#include <driver/gpio.h>

// we read up-to 64 DTC codes - if a vehicle has more than this value, I mean,
// why are you using that car??
#define OBD2_MAX_ERR_CODES 64
#define DECLARE_OBD2_DTC(X) uint8_t(X[OBD2_MAX_ERR_CODES]) = { 0U }
#define OBD2_SIZE 4U
#define DECLARE_OBD2_DATA(X) uint8_t(X[OBD2_SIZE])
#define OBD2_DATA_ADDR(X) &(X)
#define OBD2_DATA_SIZE(X) sizeof((X))
#define A(X) X[0]
#define B(X) X[1]
#define C(X) X[2]
#define D(X) X[3]
#define OBD2_EXPAND(X) ((uint32_t)A((X)) << 24 | (uint32_t)B((X)) << 16 | (uint32_t)C((X)) << 8 | (uint32_t)D((X)))

/* Representation of 32-bit float or uint32_t value */
typedef union FU32_ {
  float value;
  uint32_t raw;
} FU32;

/* ESP32 pin attached to the CAN RX pin */
extern const gpio_num_t CAN_rx;

/* ESP32 pin connected to the CAN TX pin */
extern const gpio_num_t CAN_tx;

/**
 * @brief Initializes the OBD-II system attaching the given
 * CAN_rx and CAN_tx pins respectively.
 * 
 * @return int '1' if successful, '0' otherwise
 */
int OBD_init(void);

/**
 * @brief Finalizes the OBD-II system
 */
void OBD_end(void);

/**
 * @brief Gets current engine load as a percentage (over 100%).
 * 
 * @return float engine load percentage.
 */
float OBD_get_engine_load(void);

/**
 * @brief Gets current engine coolant temperature.
 * 
 * @return float temperature in ºC.
 */
float OBD_get_coolant_temperature(void);

/**
 * @brief Gets current engine oil temperature.
 * 
 * @return float temperature in ºC.
 */
float OBD_get_engine_oil_temperature(void);

/**
 * @brief Gets current engine fuel pressure.
 * 
 * @return float fuel pressure as kPa.
 */
float OBD_get_fuel_pressure(void);

/**
 * @brief Gets current engine RPM.
 * 
 * @return float engine RPM.
 */
float OBD_get_engine_RPM(void);

/**
 * @brief Gets current vehicle speed.
 * 
 * @return float speed in km/h.
 */
float OBD_get_vehicle_speed(void);

/**
 * @brief Gets current air intake temperature.
 * 
 * @return float intake air temperature in ºC.
 */
float OBD_get_intake_air_temperature(void);

/**
 * @brief Gets current throttle position as a percentage.
 * 
 * @return float throttle position.
 */
float OBD_get_throttle_rate(void);

/**
 * @brief Gets current fuel tank calculated level.
 * 
 * @return float fuel tank level as a percentage.
 */
float OBD_get_fuel_tank_level(void);

/**
 * @brief Gets ambient air temperature.
 * 
 * @return float ambient temperature in ºC.
 */
float OBD_get_ambient_air_temperature(void);

/**
 * @brief In hybrid vehicles, estimated battery remaining life.
 * 
 * @return float battery remaining life as a percentage.
 */
float OBD_get_battery_remaining_life(void);

/**
 * @brief Gets current engine fuel rate.
 * 
 * @return float fuel rate as L/h.
 */
float OBD_get_engine_fuel_rate(void);

/**
 * @brief Gets time since engine was started.
 * 
 * @return float time since engine was started.
 */
float OBD_get_engine_runtime(void);

/**
 * @brief Gets current odometer value.
 * 
 * @return float odometer value (in km).
 */
float OBD_get_odometer(void);

/**
 * @brief Gets current gear, if supported.
 * 
 * @return float current gear as a ratio.
 */
float OBD_get_actual_gear(void);

/**
 * @brief Gets current DTCs, if any. Use macro "DECLARE_OBD2_DTC"
 * for creating the array.
 * 
 * @param errs buffer in which to store DTCs.
 */
void OBD_get_DTC(uint8_t errs[OBD2_MAX_ERR_CODES]);

/**
 * @brief Clears all the stored DTCs at the vehicle.
 * 
 * @return int 1 for success, 0 for failure.
 */
int OBD_clear_DTC(void);

/**
 * @brief Gets vehicle identification (VIN)
 * 
 * @return String the VIN identifier.
 */
String OBD_get_VIN(void);

/**
 * @brief Gets current vehicle ECU name.
 * 
 * @return String ECU name.
 */
String OBD_get_ECU_name(void);

#endif /* OBDII_H */
