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
#include "OBDII.hpp"

#include <Arduino.h>
#include <CAN.h>
#include <OBD2.h>

const gpio_num_t CAN_rx = GPIO_NUM_34;
const gpio_num_t CAN_tx = GPIO_NUM_35;

static unsigned long last_pid_response_millis = 0LU;
static bool initialized = false;

int OBD_init(void)
{
    int ret;
    CAN.setPins(CAN_rx, CAN_tx);
    ret = OBD2.begin();
    initialized = (ret == 1);

    return ret;
}

void OBD_end(void) {
    initialized = false;
    OBD2.end();
}

static FU32 OBD_read(uint8_t pid)
{
    assert(initialized);
    FU32 ret = OBD2.pidValueRaw(pid)
                   ? (FU32){.raw = OBD2.pidReadRaw(pid)}
                   : (FU32){.value = OBD2.pidRead(pid)};

    // update the time in which we accessed the PID
    last_pid_response_millis = millis();
    return ret;
}

static inline int OBD_read(uint8_t mode, uint8_t pid, void *data, int length)
{
    return OBD2.pidRead(mode, pid, data, length);
}

float OBD_get_engine_load(void)
{
    return OBD_read(CALCULATED_ENGINE_LOAD).value;
}

float OBD_get_coolant_temperature(void)
{
    return OBD_read(ENGINE_COOLANT_TEMPERATURE).value;
}

float OBD_get_engine_oil_temperature(void)
{
    return OBD_read(ENGINE_OIL_TEMPERATURE).value;
}

float OBD_get_fuel_pressure(void) { return OBD_read(FUEL_PRESSURE).value; }

float OBD_get_engine_RPM(void) { return OBD_read(ENGINE_RPM).value; }

float OBD_get_vehicle_speed(void) { return OBD_read(VEHICLE_SPEED).value; }

float OBD_get_intake_air_temperature(void)
{
    return OBD_read(AIR_INTAKE_TEMPERATURE).value;
}

float OBD_get_throttle_rate(void) { return OBD_read(THROTTLE_POSITION).value; }

float OBD_get_fuel_tank_level(void)
{
    return OBD_read(FUEL_TANK_LEVEL_INPUT).value;
}

float OBD_get_ambient_air_temperature(void)
{
    return OBD_read(AMBIENT_AIR_TEMPERATURE).value;
}

float OBD_get_battery_remaining_life(void)
{
    return OBD_read(HYBRID_BATTERY_PACK_REMAINING_LIFE).value;
}

float OBD_get_engine_fuel_rate(void)
{
    return OBD_read(ENGINE_FUEL_RATE).value;
}

float OBD_get_engine_runtime(void)
{
    return OBD_read(RUN_TIME_SINCE_ENGINE_START).value;
}

float OBD_get_odometer(void)
{
    assert(initialized);
    DECLARE_OBD2_DATA(value);
    if (!OBD2.pidRead(0x01, 0xA6, OBD2_DATA_ADDR(value), OBD2_DATA_SIZE(value)))
        return NAN;

    return OBD2_EXPAND(value) / 10.0;
}

float OBD_get_actual_gear(void)
{
    assert(initialized);
    DECLARE_OBD2_DATA(value);
    if (!OBD2.pidRead(0x01, 0xA4, OBD2_DATA_ADDR(value), OBD2_DATA_SIZE(value)))
        return NAN;

    // not supported
    if ((A(value) & 0b00000010) == 0)
        return NAN;

    return ((256.0 * C(value)) + D(value)) / 1000.0;
}

int OBD_get_DTC(uint8_t errs[OBD2_MAX_ERR_CODES])
{
    assert(initialized);

    int read = OBD2.pidRead(0x03, errs, OBD2_MAX_ERR_CODES);
    return (int) (read / 6);
}

int OBD_clear_DTC(void)
{
    assert(initialized);
    return OBD2.clearStoredDTC();
}

String OBD_get_VIN(void)
{
    assert(initialized);
    return OBD2.vinRead();
}

String OBD_get_ECU_name(void)
{
    assert(initialized);
    return OBD2.ecuNameRead();
}
