/*
 * Copyright (C) 2010 Texas Instruments
 * Author: Balaji T K
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _LINUX_BQ2415X_I2C_H
#define _LINUX_BQ2415X_I2C_H

#define BQ2415x_START_CHARGING		(1 << 0)
#define BQ2415x_STOP_CHARGING		(1 << 1)
#define BQ2415x_CHARGER_FAULT		(1 << 2)

#define BQ2415x_CHARGE_DONE		0x20
#define BQ2415x_FAULT_VBUS_OVP		0x31
#define BQ2415x_FAULT_SLEEP		0x32
#define BQ2415x_FAULT_BAD_ADAPTOR	0x33
#define BQ2415x_FAULT_BAT_OVP		0x34
#define BQ2415x_FAULT_THERMAL_SHUTDOWN	0x35
#define BQ2415x_FAULT_TIMER		0x36
#define BQ2415x_FAULT_NO_BATTERY	0x37

/* not a bq generated event,we use this to reset the
 * the timer from the twl driver.
 */
#define BQ2415x_RESET_TIMER		0x38

struct bq2415x_charger_callbacks {
	void (*set_charge_current)(struct bq2415x_charger_callbacks *ptr,
						int cable_type);
	void (*set_termination_current)(struct bq2415x_charger_callbacks *ptr,
						int term_type);
	void (*get_charger_register)(struct bq2415x_charger_callbacks *ptr);

	void (*set_charger_voreg)(struct bq2415x_charger_callbacks *ptr);

	void (*set_control_800)(struct bq2415x_charger_callbacks *ptr);

	void (*set_control_limit)(struct bq2415x_charger_callbacks *ptr);
};

/* BQ24153 / BQ24156 / BQ24158 */
/* Status/Control Register */
#define REG_STATUS_CONTROL		0x00
#define		TIMER_RST		(1 << 7)
#define		ENABLE_STAT_PIN		(1 << 6)

/* Control Register */
#define REG_CONTROL_REGISTER		0x01
#define	INPUT_CURRENT_LIMIT_SHIFT	6
#define	ENABLE_ITERM_SHIFT		3

/* Control/Battery Voltage Register */
#define REG_BATTERY_VOLTAGE		0x02
#define	VOLTAGE_SHIFT			2

/* Vender/Part/Revision Register */
#define REG_PART_REVISION		0x03

/* Battery Termination/Fast Charge Current Register */
#define REG_BATTERY_CURRENT		0x04
#define	BQ24156_CURRENT_SHIFT		3
#define	BQ24153_CURRENT_SHIFT		4

/* Special Charger Voltage/Enable Pin Status Register */
#define REG_SPECIAL_CHARGER_VOLTAGE	0x05

/* Safety Limit Register */
#define REG_SAFETY_LIMIT		0x06
#define	MAX_CURRENT_SHIFT		4

#define BQ24153 (1 << 3)
#define BQ24156 (1 << 6)
#define BQ24157 (1 << 7)
#define BQ24158 (1 << 8)

#define BQ2415x_WATCHDOG_TIMEOUT	20000

struct bq2415x_platform_data {
	int max_charger_currentmA;
	int max_charger_voltagemV;
	int termination_currentmA;
	int cin_limit_current;
	int charge_ac_current;
	int charge_usb_current;
	int first_term_currentmA;
	/* int second_term_currentmA; */
	void (*set_charge)(int flag);
	void (*enable_irq_handler)(void);
	void (*set_full_charge)(void);
	void (*register_callbacks)(struct bq2415x_charger_callbacks *ptr);
	int ta_gpio;
	int ta_irq;
	int ta_enable_gpio;
	int vf_gpio;
	int vf_irq;
};

#endif
