/*
***************************************************************************
*
* Author: Teunis van Beelen
*
* Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017 Teunis van Beelen
*
* Email: teuniz@gmail.com
*
***************************************************************************
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************
*/

/* Last revision: August 5, 2017 */

/* For more info and how to use this library, visit: http://www.teuniz.net/RS-232/ */


#ifndef rs232_INCLUDED
#define rs232_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#if defined(__linux__) || defined(__FreeBSD__)

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/file.h>
#include <errno.h>

#else

#include <windows.h>

#endif

extern int RS232_OpenComport(int, int, const char *);

extern int RS232_PollComport(int, unsigned char *, int);

extern int RS232_SendByte(int, unsigned char);

extern int RS232_SendBuf(int, unsigned char *, int);

extern void RS232_CloseComport(int);

extern void RS232_cputs(int, const char *);

extern int RS232_IsDCDEnabled(int);

extern int RS232_IsCTSEnabled(int);

extern int RS232_IsDSREnabled(int);

extern void RS232_enableDTR(int);

extern void RS232_disableDTR(int);

extern void RS232_enableRTS(int);

extern void RS232_disableRTS(int);

extern void RS232_flushRX(int);

extern void RS232_flushTX(int);

extern void RS232_flushRXTX(int);

extern int RS232_GetPortnr(const char *);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif


