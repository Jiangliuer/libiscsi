/* 
   Copyright (C) 2013 Ronnie Sahlberg <ronniesahlberg@gmail.com>
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>

#include <CUnit/CUnit.h>

#include "iscsi.h"
#include "scsi-lowlevel.h"
#include "iscsi-test-cu.h"

void
test_write12_flags(void)
{ 
	int ret;
	unsigned char *buf = alloca(block_size);

	CHECK_FOR_DATALOSS;

	logging(LOG_VERBOSE, LOG_BLANK_LINE);
	logging(LOG_VERBOSE, "Test WRITE12 flags");

	logging(LOG_VERBOSE, "Test WRITE12 with DPO==1");
	ret = write12(iscsic, tgt_lun, 0,
		     block_size, block_size,
		     0, 1, 0, 0, 0, buf);
	if (ret == -2) {
		logging(LOG_NORMAL, "[SKIPPED] WRITE12 is not implemented.");
		CU_PASS("WRITE12 is not implemented.");
		return;
	}	
	CU_ASSERT_EQUAL(ret, 0);


	logging(LOG_VERBOSE, "Test WRITE12 with FUA==1 FUA_NV==0");
	ret = write12(iscsic, tgt_lun, 0,
		     block_size, block_size,
		     0, 0, 1, 0, 0, buf);
	CU_ASSERT_EQUAL(ret, 0);


	logging(LOG_VERBOSE, "Test WRITE12 with FUA==1 FUA_NV==1");
	ret = write12(iscsic, tgt_lun, 0,
		     block_size, block_size,
		     0, 0, 1, 1, 0, buf);
	CU_ASSERT_EQUAL(ret, 0);


	logging(LOG_VERBOSE, "Test WRITE12 with FUA==0 FUA_NV==1");
	ret = write12(iscsic, tgt_lun, 0,
		     block_size, block_size,
		     0, 0, 0, 1, 0, buf);
	CU_ASSERT_EQUAL(ret, 0);


	logging(LOG_VERBOSE, "Test WRITE12 with DPO==1 FUA==1 FUA_NV==1");
	ret = write12(iscsic, tgt_lun, 0,
		     block_size, block_size,
		     0, 1, 1, 1, 0, buf);
	CU_ASSERT_EQUAL(ret, 0);
}
