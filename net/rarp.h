/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */


#ifndef __RARP_H__
#define __RARP_H__

#ifndef __NET_H__
#include <net.h>
#endif /* __NET_H__ */


/**********************************************************************/
/*
 *	Global functions and variables.
 */

extern int	RarpTry;

extern void RarpRequest (void);	/* Send a RARP request */

/**********************************************************************/

#endif /* __RARP_H__ */
