/*
 * Ouroboros - Copyright (C) 2016 - 2017
 *
 * The Flow and Retransmission control component
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
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef OUROBOROS_IPCPD_NORMAL_FRCT_H
#define OUROBOROS_IPCPD_NORMAL_FRCT_H

#include <ouroboros/shared.h>
#include <ouroboros/utils.h>

#include "frct_pci.h"

#define FRCT_PROTO "FRCT"

struct frct_i;

int         frct_init(void);

int         frct_fini(void);

cep_id_t    frct_i_create(uint64_t  address,
                          qoscube_t cube);

int         frct_i_destroy(cep_id_t cep_id);

int         frct_i_set_id(cep_id_t cep_id,
                          cep_id_t r_cep_id);

cep_id_t    frct_i_get_id(cep_id_t cep_id);

uint64_t    frct_i_get_addr(cep_id_t cep_id);

int         frct_i_write_sdu(cep_id_t             id,
                             struct shm_du_buff * sdb);

int         frct_post_sdu(struct shm_du_buff * sdb);

#endif /* OUROBOROS_IPCPD_NORMAL_FRCT_H */
