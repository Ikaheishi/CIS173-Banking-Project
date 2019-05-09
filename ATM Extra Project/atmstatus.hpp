#pragma once

#include <cstdint>

/**	Return status indication enumerator
 *	Non-zero values expect futher action by the caller.
 */
enum struct ATM_STATUS : uint8_t{
	SUCCESS = 0,
	//ATM status
	UNK_ERROR = 0xFF,
	CASH_LOW = 0x40, //$0
	CASH_FULL = 0x4F, //$Full
	//Account access/status/creation
	ACT_INVALID = 0xA0, //Account zero
	ACT_EXIST = 0xAE,	//Account already Exists
	ACT_PASS = 0xAD, //Access Denied
	ACT_HOLD = 0xAF, //Account Frozen
	//Account interaction
	FUNDS_INSUFFICENT = 0xB0, //Balance zero
};
