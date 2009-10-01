/*
    This file is part of Kismet

    Kismet is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Kismet is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Kismet; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __PACKETSOURCE_DOT15D4_H__
#define __PACKETSOURCE_DOT15D4_H__

#include "config.h"

#include <usb.h>
#include <pthread.h>

#include <packetchain.h>
#include <packetsource.h>

// Kismet DLT for 15.4
#define KDLT_IEEE802_15_4		195

// three-bit frametype
#define DOT154_FH_FRAMETYPE(f)	((f) & 0x07)

// single bits
#define DOT154_FH_SECURITY(f)	((f) & 0x08)
#define DOT154_FH_PENDING(f)	((f) & 0x10)
#define DOT154_FH_ACKREQ(f)		((f) & 0x20)
#define DOT154_FH_INTRAPAN(f)	((f) & 0x40)

// two-bit values
#define DOT154_DESTADDRMODE_MASK	0x3072
#define DOT154_FRAMEVERSION_MASK	0x12288
#define DOT154_SOURCEADDRMODE_MASK	0x49152

#define DOT154_FH_DESTADDRMODE(f)	((unsigned int) ((f) & 0xC00) >> 10)
#define DOT154_FH_FRAMEVERSION(f)	((unsigned int) ((f) & 0x3000) >> 12)
#define DOT154_FH_SRCADDRMODE(f)	((unsigned int) ((f) & 0xC000) >> 14)

int kis_dot15d4_dissector(CHAINCALL_PARMS);

enum dot15d4_type {
	d15d4_type_beacon = 0x00,
	d15d4_type_data = 0x01,
	d15d4_type_command = 0x03
};
extern const char *dot15d4_type_str[];

enum dot15d4_cmd_subtype {
	d15d4_subtype_cmd_assocreq = 0x01,
	d15d4_subtype_cmd_assocresp = 0x02,
	d15d4_subtype_cmd_disassoc = 0x03,
	d15d4_subtype_cmd_datareq = 0x04,
	d15d4_subtype_cmd_panconf = 0x05,
	d15d4_subtype_cmd_orphan = 0x06,
	d15d4_subtype_cmd_beaconreq = 0x07,
	d15d4_subtype_cmd_coordrealign = 0x08,
	d15d4_subtype_cmd_gtsreq = 0x09
};
extern const char *dot15d4_cmd_subtype_str[];

class dot15d4_packinfo : public packet_component {
public:
	dot15d4_packinfo() {
		self_destruct = 1;

		frame_header = 0;
		type = 0;
		security = 0;
		sourceaddr_mode = 0;
		destaddr_mode = 0;
		version = 0;
		seqno = 0;
		pan = 0;
		source_addr = 0;
		dest_addr = 0;
	};

	uint16_t frame_header;

	unsigned int type;
	unsigned int security;
	unsigned int sourceaddr_mode;
	unsigned int destaddr_mode;
	unsigned int version;

	unsigned int seqno;
	unsigned int pan;

	long unsigned int source_addr;
	long unsigned int dest_addr;

};

#endif