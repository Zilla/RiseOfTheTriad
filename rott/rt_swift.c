/*
Copyright (C) 1994-1995 Apogee Software, Ltd.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
//****************************************************************************
//
// RT_SWIFT.C
//
// SWIFT services module - for CYBERMAN use in ROTT.
//
//****************************************************************************

/* TODO: Remove file and references */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "compat_stdlib.h"
#include <string.h>
#include "rt_def.h"
#include "rt_swift.h"
#include "_rt_swft.h"
//MED

//****************************************************************************
//
// SWIFT_Initialize ()
//
// Test for presence of SWIFT extensions and SWIFT device.
// Returns 1 (TRUE) if SWIFT features are available, 0 otherwise.
// Remember to call SWIFT_Terminate() if SWIFT_Initialize succeeds!
//
//****************************************************************************

int SWIFT_Initialize(void)
{
   return 0;
}

//****************************************************************************
//
// SWIFT_Terminate ()
//
// Free resources required for SWIFT support.  If SWIFT_Initialize has
// not been called, or returned FALSE, this function does nothing.
// SWIFT_Terminate should always be called at some time after a call to
// SWIFT_Initialize has returned TRUE.
//
//****************************************************************************

void SWIFT_Terminate(void)
{

}

//****************************************************************************
//
// SWIFT_GetAttachedDevice ()
//
// Returns the device-type code for the attached SWIFT device, if any.
//
//****************************************************************************

int SWIFT_GetAttachedDevice(void)
{
   return 0;
}

//****************************************************************************
//
// SWIFT_GetStaticDeviceInfo ()
//
// Reads static device data.
//
//****************************************************************************

int SWIFT_GetStaticDeviceInfo(SWIFT_StaticData *psd)
{
   (void)psd;
   return 0;
}

//****************************************************************************
//
// SWIFT_Get3DStatus ()
//
// Read the current input state of the device.
//
//****************************************************************************

void SWIFT_Get3DStatus(SWIFT_3DStatus *pstat)
{
   (void)pstat;
}

//****************************************************************************
//
// SWIFT_TactileFeedback ()
//
// Generates tactile feedback to user.
// d   = duration of tactile burst, in milliseconds.
// on  = motor on-time per cycle, in milliseconds.
// off = motor off-time per cycle, in milliseconds.
//
//****************************************************************************

void SWIFT_TactileFeedback(int d, int on, int off)
{
   (void)d;
   (void)on;
   (void)off;
}

//****************************************************************************
//
// SWIFT_GetDynamicDeviceData ()
//
// Returns Dynamic Device Data word - see SDD_* above
//
//****************************************************************************

unsigned SWIFT_GetDynamicDeviceData(void)
{
   return 0;
}

//****************************************************************************
//
// MouseInt ()
//
// Generate a call to the mouse driver (interrupt 33h) in real mode,
// using the DPMI function 'Simulate Real-Mode Interrupt'.
//
//****************************************************************************

void MouseInt(struct rminfo *prmi)
{
   (void)prmi;
}

//****************************************************************************
//
// freeDOS ()
//
// Release real-mode DOS memory block via DPMI
//
//****************************************************************************

void freeDOS(short sel)
{
   (void)sel;
}

//****************************************************************************
//
// allocDOS ()
//
// Allocate a real-mode DOS memory block via DPMI
//
//****************************************************************************

void *allocDOS(unsigned nbytes, short *pseg, short *psel)
{
   (void)nbytes;
   (void)pseg;
   (void)psel;
   return NULL;
}
