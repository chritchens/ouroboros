/*
 * Ouroboros - Copyright (C) 2016 - 2018
 *
 * Quality of Service cube
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
 * Foundation, Inc., http://www.fsf.org/about/contact/.
 */

#include <ouroboros/qos.h>
#include <ouroboros/qoscube.h>

#include <string.h>

qoscube_t qos_spec_to_cube(qosspec_t qs)
{
        if (qs.loss == 0)
                return QOS_CUBE_DATA;
        else if (qs.delay <= qos_voice.delay &&
            qs.bandwidth <= qos_voice.bandwidth &&
            qs.availability >= qos_voice.availability &&
            qs.maximum_interruption <= qos_voice.maximum_interruption)
                return QOS_CUBE_VOICE;
        else if (qs.delay <= qos_video.delay &&
                 qs.bandwidth <= qos_video.bandwidth &&
                 qs.availability >= qos_video.availability &&
                 qs.maximum_interruption <= qos_video.maximum_interruption)
                return QOS_CUBE_VIDEO;
        else if (qs.in_order == 1)
                return QOS_CUBE_BE;
        else
                return QOS_CUBE_RAW;
}

qosspec_t qos_cube_to_spec(qoscube_t qc)
{
        switch (qc) {
        case QOS_CUBE_VOICE:
                return qos_voice;
        case QOS_CUBE_VIDEO:
                return qos_video;
        case QOS_CUBE_BE:
                return qos_best_effort;
        case QOS_CUBE_DATA:
                return qos_data;
        default:
                return qos_raw;
        }
}
