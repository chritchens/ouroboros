/*
 * Ouroboros - Copyright (C) 2016 - 2017
 *
 * Normal IPC Process - RIB configuration
 *
 *    Dimitri Staessens <dimitri.staessens@ugent.be>
 *    Sander Vrijders   <sander.vrijders@ugent.be>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., http://www.fsf.org/about/contact/.
 */

#ifndef OUROBOROS_IPCPD_NORMAL_RIB_CONFIG_H
#define OUROBOROS_IPCPD_NORMAL_RIB_CONFIG_H

/* RIB configuration for normal */
#define RIB_MAX_PATH_LEN 256

#define DLR          "/"
#define BOOT_NAME    "boot"
#define MEMBERS_NAME "members"
#define ROUTING_NAME "fsdb"
#define BOOT_PATH    DLR BOOT_NAME
#define MEMBERS_PATH DLR MEMBERS_NAME
#define ROUTING_PATH DLR ROUTING_NAME

#endif /* OUROBOROS_IPCPD_NORMAL_RIB_CONFIG_H */
