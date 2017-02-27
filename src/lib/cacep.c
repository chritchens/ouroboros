/*
 * Ouroboros - Copyright (C) 2016 - 2017
 *
 * The Common Application Connection Establishment Protocol
 *
 *    Dimitri Staessens <dimitri.staessens@ugent.be>
 *    Sander Vrijders   <sander.vrijders@ugent.be>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#include <ouroboros/config.h>
#include <ouroboros/cacep.h>
#include <ouroboros/dev.h>
#include <ouroboros/errno.h>

#include <stdlib.h>
#include <string.h>

#include "cacep.pb-c.h"
typedef CacepMsg cacep_msg_t;

#define BUF_SIZE 64

int read_msg(int                fd,
             struct conn_info * info)
{
        uint8_t                      buf[BUF_SIZE];
        cacep_msg_t *                msg;
        ssize_t                      len;

        len = flow_read(fd, buf, BUF_SIZE);
        if (len < 0)
                return -1;

        msg = cacep_msg__unpack(NULL, len, buf);
        if (msg == NULL)
                return -1;

        strcpy(info->protocol, msg->protocol);

        info->pref_version = msg->pref_version;
        info->pref_syntax  = msg->pref_syntax;

        cacep_msg__free_unpacked(msg, NULL);

        return 0;
}

static int send_msg(int                      fd,
                    const struct conn_info * info)
{
        cacep_msg_t msg = CACEP_MSG__INIT;
        uint8_t *   data = NULL;
        size_t      len  = 0;

        msg.ae_name      = (char *) info->ae_name;
        msg.protocol     = (char *) info->protocol;
        msg.pref_version = info->pref_version;
        msg.pref_syntax  = info->pref_syntax;
        if (msg.pref_syntax < 0)
                return -1;

        len = cacep_msg__get_packed_size(&msg);
        if (len == 0)
                return -1;

        data = malloc(len);
        if (data == NULL)
                return -ENOMEM;

        cacep_msg__pack(&msg, data);

        if (flow_write(fd, data, len) < 0) {
                free(data);
                return -1;
        }

        free(data);

        return 0;
}

int cacep_connect(int                      fd,
                  const struct conn_info * in,
                  struct conn_info *       out)
{
        if (in == NULL || out == NULL)
                return -EINVAL;

        if (send_msg(fd, in))
                return -1;

        if (read_msg(fd, out))
                return -1;

        if (strcmp(in->ae_name, out->ae_name) ||
            strcmp(in->protocol, out->protocol) ||
            in->pref_version != out->pref_version ||
            in->pref_syntax != out->pref_syntax)
                return -EPROTO;

        return 0;
}

int cacep_listen(int                      fd,
                 const struct conn_info * in,
                 struct conn_info *       out)
{
        if (in == NULL || out == NULL)
                return -EINVAL;

        if (send_msg(fd, in))
                return -1;

        if (read_msg(fd, out))
                return -1;

        if (strcmp(in->ae_name, out->ae_name) ||
            strcmp(in->protocol, out->protocol) ||
            in->pref_version != out->pref_version ||
            in->pref_syntax != out->pref_syntax)
                return -EPROTO;

        return 0;
}
