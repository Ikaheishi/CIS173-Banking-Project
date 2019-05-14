#pragma once

#include <cstdint>

/**	Return status indication enumerator
 *	Non-zero values expect futher action by the caller.
 */
enum struct ATM_STATUS : uint16_t{
	SUCCESS = 0,
	//ATM status
	UNK_ERROR = 0xFFFF,
	CASH_LOW = 0x4000, //$0
	CASH_FULL = 0x4F00, //$Full
	//Account access/status/creation
	ACT_INVALID = 0xA000, //Account zero
	ACT_EXIST = 0xAE00,	//Account already Exists
	ACT_PASS = 0xAD00, //Access Denied
	ACT_HOLD = 0xAF00, //Account Frozen
	//Account interaction
	FUNDS_INSUFFICENT = 0xB000, //Balance zero
};
