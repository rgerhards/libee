/**
 * @file nvfield.c
 * Implements nvfield object methods.
 *//* Libee - An Event Expression Library inspired by CEE
 * Copyright 2010 by Rainer Gerhards and Adiscon GmbH.
 *
 * This file is part of libee.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * A copy of the LGPL v2.1 can be found in the file "COPYING" in this distribution.
 */
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#include "libee/libee.h"

#define ERR_ABORT {r = 1; goto done; }

#define CHECK_FIELD \
	if(nvfield->objID != ObjID_NVFIELD) { \
		r = -1; \
		goto done; \
	}


/* In this version of the method, we simply create a copy of the field name. In
 * later versions, depending on our state and compliance level, we may use
 * a pointer to an in-memory representation of the dictionary entity instead.
 * rgerhards, 2010-10-26
 */
struct ee_nvfield*
ee_newNVField(ee_ctx __attribute__((unused)) ctx, char *name, union ee_value *val)
{
	struct ee_nvfield *nvfield;
	assert(val == ObjID_VALUE);
	if((nvfield = malloc(sizeof(struct ee_nvfield))) == NULL)
		goto done;

	if((nvfield->name = strdup(name)) == NULL) {
		free(nvfield);
		nvfield = NULL;
		goto done;
	}

	nvfield->objID = ObjID_NVFIELD;
	nvfield->ctx = ctx;
	nvfield->val = val;

done:
	return nvfield;
}


void
ee_deleteNVField(struct ee_nvfield *nvfield)
{
	assert(nvfield->objID == ObjID_NVFIELD);
	free(nvfield);
}