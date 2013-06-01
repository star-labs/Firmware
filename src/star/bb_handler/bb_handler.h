/****************************************************************************
 *
 *   Copyright (C) 2012 PX4 Development Team. All rights reserved.
 *   Author: @author Espen Nilsen, Gunnar Sandaker -- STAR
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file bb_handler.h
 *
 */
#include <stdio.h>

/** @brief Makro to compliment 'OK' makro defined in NuttX */
#define NOT_OK 1
/** @brief Makro size of in/out buffers 		*/
#define BUFFER_SIZE 200

/** @brief Max number of images in burst mode*/
#define BURST_MAX 100

/**
 * @brief Global flag for debug. use commandline argument: debugon/debugoff
 */
bool bb_debug_mode = false;


/** @brief internal cmd-types (to BB)*/
typedef enum {
	S_IMAGE 	= 0,
	S_VIDEO 	= 1,
	S_BURST 	= 2,
	S_SERIE 	= 3,
	S_STOP 		= 4,
	S_FORCE 	= 5,
} internal_cmd_t;

/** @brief internal query-types (from BB) */
typedef enum {
	S_NA 			= 0,
	S_GETTIME 		= 1,
	S_GETPOS 		= 2,
	S_GETATT 		= 3,
	S_GETTEMP 		= 4,
	S_GETLOCALPOS 	= 5,
	S_GETGPSRAW 	= 6,
	S_OK 			= 7,
	S_BUSY 			= 8,
	S_GETALL 		= 9,
	S_GETSENSORS	= 10,
} internal_query_t;

/** @brief Structure for connecting the commands we send to BB against our internal names */
struct cmds_s {
	char cmd_name[20];
	internal_cmd_t signal;
};

/** @brief Structure for connecting received commands from BB against our internal names */
struct query_s {
	char cmd_name[20];
	internal_query_t signal;
};


/* BB komunikasjons variable */

/** @brief Commands that BeagleBoard Capture parses */
const struct cmds_s cmds[] = {
	{.cmd_name = "image", 	.signal = S_IMAGE},
	{.cmd_name = "video", 	.signal = S_VIDEO},
	{.cmd_name = "burst", 	.signal = S_BURST},
	{.cmd_name = "serie", 	.signal = S_SERIE},
	{.cmd_name = "stop", 	.signal = S_STOP},
	{.cmd_name = "force", 	.signal = S_FORCE},
};
/** @brief Querys that BeagleBoard Handler responds to */
const struct query_s querys[] = {
	{.cmd_name = "getall", 		.signal = S_GETALL},
	{.cmd_name = "gettime", 	.signal = S_GETTIME},
	{.cmd_name = "getpos", 		.signal = S_GETPOS},
	{.cmd_name = "getatt", 		.signal = S_GETATT},
	{.cmd_name = "gettemp", 	.signal = S_GETTEMP},
	{.cmd_name = "getlocalpos", .signal = S_GETLOCALPOS},
	{.cmd_name = "getgpsraw", 	.signal = S_GETGPSRAW},
	{.cmd_name = "ok", 			.signal = S_OK},
	{.cmd_name = "busy", 		.signal = S_BUSY},
	{.cmd_name = "getsensors", 	.signal = S_GETSENSORS},


};

/** @brief Number of querys for BB_handler */
const int n_query = sizeof(querys) / sizeof(querys[0]);

/** @brief Number of commands for BB Capture */
const int n_cmds = sizeof(cmds) / sizeof(cmds[0]);

/**
 * @brief Internal debugging function for bb_handler, dependent on bb_debug_mode.
 * @param char* , debug text
 *
 */
void bb_debug(char* debug_str)
{
	if(bb_debug_mode == true)
	{
		fprintf(stderr, "[bb_handler] %s", debug_str);
		fflush(stderr);
	}
}

/**
 * @brief get cmd_name from cmd number.
 * @param internal_cmd_t
 */
const char* get_command(internal_cmd_t c)
{
	for(int i = 0; i < n_cmds; i++){
		if(cmds[i].signal == c)
			return cmds[i].cmd_name;
	}

	/* Dette "kan ikke" skje, i s�fall er det ikke samsvar mellom internal_cmd_t typen og cmds strukten. */
	return "error";
}

