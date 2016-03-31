/*
 * Ouroboros - Copyright (C) 2016
 *
 * A simple echo application
 *
 *    Sander Vrijders <sander.vrijders@intec.ugent.be>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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

#include <stdio.h>
#include <string.h>

#define SERVER_AP_NAME "echo-server"
#define BUF_SIZE 256

#include "echo_client.c"
#include "echo_server.c"

static void usage()
{
        printf("Usage: echo-app [OPTION]...\n"
               "Sends an echo between a server and a client\n\n"
               "  -l, --listen              Run in server mode\n"
               "      --help                Display this help text and exit\n");
}

int main(int argc, char ** argv) {

        argc--;
        argv++;
        while (argc > 0) {
                if (strcmp(*argv, "-l") == 0 ||
                    strcmp(*argv, "--listen") == 0) {
                        return server_main();
                } else {
                        usage();
                        return 0;
                }
                argc--;
                argv++;
        }

        return client_main();
}