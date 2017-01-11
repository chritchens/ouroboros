/*
 * Ouroboros - Copyright (C) 2016 - 2017
 *
 * CDAP - CDAP request management
 *
 *    Sander Vrijders   <sander.vrijders@intec.ugent.be>
 *    Dimitri Staessens <dimitri.staessens@intec.ugent.be>
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

#ifndef OUROBOROS_CDAP_REQ_H
#define OUROBOROS_CDAP_REQ_H

#include <ouroboros/config.h>
#include <ouroboros/cdap.h>
#include <ouroboros/list.h>
#include <ouroboros/utils.h>

#include <pthread.h>

enum creq_state {
        REQ_NULL = 0,
        REQ_INIT,
        REQ_PENDING,
        REQ_RESPONSE,
        REQ_DONE,
        REQ_DESTROY
};

struct cdap_req {
        struct list_head next;

        struct timespec  birth;

        cdap_key_t       key;

        int              response;
        buffer_t         data;

        enum creq_state  state;
        pthread_cond_t   cond;
        pthread_mutex_t  lock;
};

struct cdap_req * cdap_req_create(cdap_key_t key);

void              cdap_req_destroy(struct cdap_req * creq);

int               cdap_req_wait(struct cdap_req * creq);

void              cdap_req_respond(struct cdap_req * creq,
                                   int               response,
                                   buffer_t          data);

enum creq_state   cdap_req_get_state(struct cdap_req * creq);

#endif /* OUROBOROS_CDAP_REQ_H */