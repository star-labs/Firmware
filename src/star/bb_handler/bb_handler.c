/*
 *
 *   ______    _________        _          _______
 * .' ____ \  |  _   _  |      / \        |_   __ \
 * | (___ \_| |_/ | | \_|     / _ \         | |__) |
 *  _.____`.      | |        / ___ \        |  __ /
 * | \____) | _  _| |_  _  _/ /   \ \_  _  _| |  \ \_  _
 *  \______.'(_)|_____|(_)|____| |____|(_)|____| |___|(_)
 *
 *  01010011 01111001 01110011 01110100 01100101 01101101
 *  00100000 01100110 01101111 01110010 00100000 01010100
 *  01100001 01100011 01110100 01101001 01100011 01100001
 *  01101100 00100000 001000001 01100101 01110010 01101001
 *  01100001 01101100 00100000 01010010 01100101 01100011
 *  01101111 01101110 01101110 01100001 01101001 01110011
 *  01110011 01100001 01101110 01100011 01100101
 */

 /**
 *
 * Denne filen er sterkt inspirert av mavlink.c
 *
 * @details A handler for BB communication
 * @author System for Tactical Aerial Reconnaissance
 * @file bb_handler.c
 *
 */


#include "bb_handler.h"
#include <nuttx/config.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <systemlib/param/param.h>
#include <systemlib/systemlib.h>
#include <systemlib/err.h>
#include <termios.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <uORB/topics/vehicle_command.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/rc_channels.h>
#include <uORB/topics/manual_control_setpoint.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/vehicle_global_position.h>
#include <uORB/topics/vehicle_gps_position.h>
#include <uORB/topics/star_image_metadata.h>
#include <poll.h>
#include <stdbool.h>

volatile bool thread_should_exit = false;		/**< Daemon exit flag */
static volatile bool thread_running = false;	/**< Daemon status flag */
static int bb_task;								/**< Handle of daemon task / thread */

/* protocol interface */
static int uart;
static int baudrate;

/* Buffers for thread*/
char read_buffer[BUFFER_SIZE] = "\0";
char read_buffer_local[BUFFER_SIZE] = "\0";
char send_buffer[BUFFER_SIZE] = "\0";
char tokens[8][32] = {'\0'};



__EXPORT int bb_handler_main(int argc, char *argv[]);
int bb_handler_thread_main(int argc, char *argv[]);
void usage(void);

void bb_send_uart_bytes(uint8_t *ch, int length);
int bb_handler_open_uart(int baud, const char *uart_name, struct termios *uart_config_original, bool *is_usb);

/*
///QUERY Handlers..
//Enn så lenge....
void h_getall();
void h_gettime();
void h_getpos();
void h_getatt();
void h_gettemp();
void h_getlocalpos();
void h_getgpsraw();
void h_ok();
void h_busy();
*/



int bb_handler_open_uart(int baud, const char *uart_name, struct termios *uart_config_original, bool *is_usb)
{
	/* process baud rate */
	int speed;

	switch (baud) {
	case 0:      speed = B0;      break;
	case 50:     speed = B50;     break;
	case 75:     speed = B75;     break;
	case 110:    speed = B110;    break;
	case 134:    speed = B134;    break;
	case 150:    speed = B150;    break;
	case 200:    speed = B200;    break;
	case 300:    speed = B300;    break;
	case 600:    speed = B600;    break;
	case 1200:   speed = B1200;   break;
	case 1800:   speed = B1800;   break;
	case 2400:   speed = B2400;   break;
	case 4800:   speed = B4800;   break;
	case 9600:   speed = B9600;   break;
	case 19200:  speed = B19200;  break;
	case 38400:  speed = B38400;  break;
	case 57600:  speed = B57600;  break;
	case 115200: speed = B115200; break;
	case 230400: speed = B230400; break;
	case 460800: speed = B460800; break;
	case 921600: speed = B921600; break;

	default:
		fprintf(stderr, "[bb_handler] ERROR: Unsupported baudrate: %d\n\tsupported examples:"
				"\n\n\t9600\n19200\n38400\n57600\n115200\n230400\n460800\n921600\n\n", baud);
		return -EINVAL;
	}

	/* open uart */
	printf("[bb_handler] UART is %s, baudrate is %d\n", uart_name, baud);
	uart = open(uart_name, O_RDWR | O_NOCTTY | O_NONBLOCK); //skulle man byttet flagg til O_NDELAY

	/* Try to set baud rate */
	struct termios uart_config;
	int termios_state;
	*is_usb = false;

	/* make some wild guesses including that USB serial is indicated by either /dev/ttyACM0 or /dev/console */
	if (strcmp(uart_name, "/dev/ttyACM0") != OK && strcmp(uart_name, "/dev/console") != OK) {

		/* Back up the original uart configuration to restore it after exit */
		if ((termios_state = tcgetattr(uart, uart_config_original)) < 0) {
			fprintf(stderr, "[bb_handler] ERROR getting baudrate / termios config for %s: %d\n", uart_name, termios_state);
			close(uart);
			return -1;
		}

		/* Fill the struct for the new configuration */
		tcgetattr(uart, &uart_config);

		/* Clear ONLCR flag (which appends a CR for every LF) */
		uart_config.c_oflag &= ~ONLCR;

		/* Set baud rate */
		if (cfsetispeed(&uart_config, speed) < 0 || cfsetospeed(&uart_config, speed) < 0) {
			fprintf(stderr, "[bb_handler] ERROR setting baudrate / termios config for %s: %d (cfsetispeed, cfsetospeed)\n", uart_name, termios_state);
			close(uart);
			return -1;
		}


		if ((termios_state = tcsetattr(uart, TCSANOW, &uart_config)) < 0) {
			fprintf(stderr, "[bb_handler] ERROR setting baudrate / termios config for %s (tcsetattr)\n", uart_name);
			close(uart);
			return -1;
		}

	} else {
		*is_usb = true;
		//fprintf(stderr, "[bb_handler] Sorry; kan ikke bruke usb!!\n");
	}

	return uart;
}


void bb_send_uart_bytes(uint8_t *ch, int length)
{

	write(uart, ch, (size_t)(sizeof(uint8_t) * length));
}


int bb_handler_thread_main(int argc, char *argv[]){

	int ch;
	char *device_name = "/dev/ttyS1";
	baudrate = 57600;

	char *tp;


	/* work around some stupidity in task_create's argv handling */
	argc -= 2;
	argv += 2;


	while ((ch = getopt(argc, argv, "b:d:eo")) != EOF) {
		switch (ch) {
		case 'b':
			baudrate = strtoul(optarg, NULL, 10);

			if (baudrate == 0)
				errx(1, "invalid baud rate '%s'", optarg);
			break;
		case 'd':
			device_name = optarg;
			break;
		default:
			usage();
			break;
		}
	}

	struct termios uart_config_original;

	bool usb_uart;

	/* print welcome text */
	warnx("\nBB Handler v1.0/a serial interface starting...");




	/* advertise star_image_metadata topic */
	struct star_image_metadata_s metadata;
	memset(&metadata, 0, sizeof(metadata));
	int image_metadata_pub_fd = orb_advertise(ORB_ID(star_image_metadata), &metadata);


	/* default values for arguments */
	uart = bb_handler_open_uart(baudrate, device_name, &uart_config_original, &usb_uart);

	if (uart < 0){
		err(1, "could not open %s", device_name);
	}
	thread_running = true;


	int com_sub_fd = orb_subscribe(ORB_ID(vehicle_command));
	orb_set_interval(com_sub_fd, 1000);
	struct vehicle_command_s vehicle_s;

	int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));
	orb_set_interval(sensor_sub_fd, 1000);
	struct sensor_combined_s sensors_s;

	int rc_sub_fd = orb_subscribe(ORB_ID(rc_channels));
	orb_set_interval(rc_sub_fd, 500);
	struct rc_channels_s rc_s;

	int mc_sub_fd = orb_subscribe(ORB_ID(manual_control_setpoint));
	orb_set_interval(mc_sub_fd, 500);
	struct manual_control_setpoint_s mc_s;

	int global_position_sub_fd = orb_subscribe(ORB_ID(vehicle_global_position));
	orb_set_interval(global_position_sub_fd, 500);
	struct vehicle_global_position_s vgp_s;

	int vehicle_attitude_sub_fd = orb_subscribe(ORB_ID(vehicle_attitude));
	orb_set_interval(vehicle_attitude_sub_fd, 500);
	struct vehicle_attitude_s va_s;

	/** filedescriptor til å abbonere på GPS data*/
	int gps_sub_fd = orb_subscribe(ORB_ID(vehicle_gps_position));
	orb_set_interval(gps_sub_fd, 500);
	struct vehicle_gps_position_s gps_s;



	struct pollfd fds[] = {
			{ .fd = com_sub_fd,   				.events = POLLIN },
			{ .fd = sensor_sub_fd,  			.events = POLLIN },
			{ .fd = rc_sub_fd,  				.events = POLLIN },
			{ .fd = mc_sub_fd,  				.events = POLLIN },
			{ .fd = global_position_sub_fd,  	.events = POLLIN },
			{ .fd = vehicle_attitude_sub_fd,  	.events = POLLIN },
			{ .fd = gps_sub_fd,  				.events = POLLIN },
	};

	unsigned int num_fds = sizeof(fds) / sizeof(fds[0]);


	bool is_trigged = false;
	internal_query_t selected = S_NA;
	int send_len = 0;
	char separator = '|';
	char split_str = " ";

	while (!thread_should_exit) {

		int poll_ret = poll(fds, num_fds, 1000);

		int n_result = read(uart, read_buffer, (size_t) BUFFER_SIZE -1);

		if(n_result > 0)
		{

			read_buffer[n_result] = '\0';

			if(strlen(read_buffer) + strlen(read_buffer_local) > BUFFER_SIZE - 1)
			{
				bb_debug("Buffer owerflow\n\n");
				read_buffer_local[0] = '\0';
			}


			strcat(read_buffer_local, read_buffer);
		}



		if(strchr(read_buffer_local, (int)separator) != NULL){
			//Hvis vi ikke har håndtert siste komando fra BB, så bare fortsett...

			////SKRIV OM DETTE TIL HELLER Å BYGGE OPP read_buffer_local SLIK AT DEN HÅNDTERES OM VI MOTTAR \n SYMBOL....



			tp = strtok(read_buffer_local, split_str);
			int t_count = 0;
			while (tp != NULL)
			{
				strcpy(tokens[t_count++], tp);
				tp = strtok (NULL, split_str);
			}



			size_t newline_pos = strcspn(tokens[0], "|");

			/**
			 * "Reparerer" tokens[0] -- strcspn returnerer lengden av strengen om ikke \n blir funnet,
			 *  vi kan derfor trygt alltid overskrive denne verdien med '\0'
			 */

			tokens[0][ (int)newline_pos ] = '\0';

			for(int i = 0; i < n_query; i++){

				bb_debug(sprintf("Buffer er: %s og Query som testes er: %s\n", tokens[0], querys[i].cmd_name));

				if(strcmp(tokens[0], querys[i].cmd_name) == 0)
				{
					selected 		= querys[i].signal;
					break;
				}
			}

			switch(selected){
				case S_GETALL:
					send_len = sprintf(send_buffer, "%llu %llu %llu %04.15f %u %u %u %04.15f %04.15f %04.15f\n", //endres !!!!!!!!!!!!!!
										gps_s.time_gps_usec, 		//< uint64_t
										gps_s.timestamp_position,	//< uint64_t
										va_s.timestamp,				//< uint64_t
										gps_s.p_variance_m,			//< float
										gps_s.lat,					//< uint32_t
										gps_s.lon,					//< uint32_t
										gps_s.alt,					//< uint32_t
										va_s.roll,					//< float
										va_s.pitch,					//< float
										va_s.yaw);					//< float

					break;

				case S_GETTIME:
					send_len = sprintf(send_buffer, "%llu\n", gps_s.time_gps_usec);
					break;

				case S_OK:
					/*
					 * DETTE BØR FLYTTES VEKK HERFRA....
					 */

					//tokens[0]; //OK MELDING
					//tokens[1]; //filnavn

					/** vi vet at vi kun får første parameter så vi tipper at dette er alltid ok */
					if(tokens[1] != NULL)
					{

						size_t special_pos = strcspn(tokens[1], "|");

						/**
						 * "Reparerer" tokens[0] -- strcspn returnerer lengden av strengen om ikke \n blir funnet.
						 *  vi kan derfor trygt alltid overskrive denne verdien med '\0'
						 */

						tokens[1][(int)special_pos] = '\0'; //NULL;//"\0";

						strcpy(metadata.file_name, tokens[1]);


						orb_publish(ORB_ID(star_image_metadata), image_metadata_pub_fd, &metadata);

						bb_debug(sprintf("Sender data til star_image_metadata topic. Filnavn: %s\n\n", metadata.file_name));



					}else{
						/** not so good :( */
						bb_debug("Mottok ikke Filnavn\n\n");


					}

					/** This command has no response! */
					send_buffer[0] = '\0';


					break;

				case S_GETPOS:
					send_len = sprintf(send_buffer, "%f %f %f\n",
							gps_s.lat,					//< uint32_t
							gps_s.lon,					//< uint32_t
							gps_s.alt);					//< uint32_t
					break;

				case S_GETATT:
					send_len = sprintf(send_buffer, "%f %f %f\n",
							va_s.roll,					//< float
							va_s.pitch,					//< float
							va_s.yaw);					//< float
					break;

				case S_GETTEMP:
					send_len = sprintf(send_buffer, "%f\n", sensors_s.baro_temp_celcius);
					break;

				case S_GETLOCALPOS:
				case S_GETGPSRAW:
					send_len = sprintf(send_buffer, "%d %d %d %f %f %f %d %f %f %f %f %f %f %llu %u\n",
							gps_s.lat,
							gps_s.lon,
							gps_s.alt,

							gps_s.s_variance_m_s,
							gps_s.p_variance_m,
							gps_s.c_variance_rad,
							gps_s.fix_type,

							gps_s.eph_m,
							gps_s.epv_m,

							gps_s.vel_m_s,
							gps_s.vel_n_m_s,
							gps_s.vel_e_m_s,
							gps_s.vel_d_m_s,

							gps_s.time_gps_usec,
							gps_s.satellites_visible);

					break;

				case S_NA:
				default:

					bb_debug("Ukjent komando\n\n");

					//send_len = sprintf(send_buffer, "Feil eller ugyldig komando\n");

					break;
			}

			/**
			 * Send data over uart om det er noe i bufferen
			 */
			send_len = strlen(send_buffer);
			if(send_len > 0)
			{
				bb_send_uart_bytes((uint8_t *)send_buffer, send_len);
			}


			selected = S_NA;
			read_buffer_local[0] = '\0';
		}


		if(poll_ret == 0){

		}else if(poll_ret < 0){
			fprintf(stderr, "IT DOES NOT MAKE SENSE - Har du glemt A starte uORB?\n");
			fflush(stderr);
		}else{
			if (fds[0].revents & POLLIN){


				orb_copy(ORB_ID(vehicle_command), com_sub_fd, &vehicle_s);

				if (vehicle_s.command == VEHICLE_CMD_DO_CONTROL_VIDEO){

					/* 	 Control onboard camera system.
					 * | Camera ID (-1 for all)
					 * | Transmission: 0: disabled, 1: enabled compressed, 2: enabled raw
					 * | Transmission mode: 0: video stream, >0: single images every n seconds (decimal)
					 * | Recording: 0: disabled, 1: enabled compressed, 2: enabled raw
					 * | Empty| Empty| Empty|
					 *
					 *	Dette vil jo ikke funke. Hva om vi prøver følgende
					 *
					 *	Control BB camera
					 *	param1| 0:image, 1:stop, 2:burst, 3:video,
					 *	param2| 0:one image, >0:number of images
					 *	param3| stop after seconds
					 *	param4| image per second, seconds per image if negative
					 *	param5| NOT IN USE
					 *	param6| NOT IN USE
					 *	param7| NOT IN USE
					 *
					 *	============================
					 *
					 *	Param1
					 *
					 */

					bb_debug("NOT IMPLEMENTED: VEHICLE_CMD_DO_CONTROL_VIDEO\n\n");

					int valg = (int) vehicle_s.param1;
					bool cap_wp_error = false;

					if(valg < 0 || valg > 5){
						cap_wp_error = true;
					}




				}

			}


			if (fds[1].revents & POLLIN){
				orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &sensors_s);
			}
/*
			if (fds[2].revents & POLLIN){

				orb_copy(ORB_ID(rc_channels), rc_sub_fd, &rc_s);

				if(rc_s.chan[rc_s.function[AUX_3]].scaled > 0)
				{
					bb_send_uart_bytes(cmds[0], strlen(cmds[0]));
					bb_debug("Ta(r) bilde RC");
				}


			}
*/
			if (fds[3].revents & POLLIN){


				orb_copy(ORB_ID(manual_control_setpoint), mc_sub_fd, &mc_s);
				char send_str[80];
				if(mc_s.aux3 > 0 && !is_trigged){

					for(int q = 0; q < n_cmds; q++){
						if(cmds[q].signal == S_IMAGE){

							strcpy(send_str, cmds[q].cmd_name);
							strcat(send_str, "\n");

							bb_send_uart_bytes((uint8_t *)send_str, (int)strlen(send_str));
							break;
						}
					}


					bb_debug("Ta(r) bilde MC\n");
					is_trigged = true;

				}

				if(mc_s.aux3 < 0)
					is_trigged = false;
			}

			if (fds[4].revents & POLLIN){
				//GLOBAL POSTITION
				orb_copy(ORB_ID(vehicle_global_position), global_position_sub_fd, &vgp_s);
			}
			if (fds[5].revents & POLLIN){
				//vehicle_attitude
				orb_copy(ORB_ID(vehicle_attitude), vehicle_attitude_sub_fd, &va_s);
			}
			/* there could be more file descriptors here, in the form like:
			 * if (fds[1..n].revents & POLLIN) {}
			 */
		}

		/** Sleep for 0.2 s */
		usleep(200000);
	}

	/* Reset the UART flags to original state */
	if (!usb_uart)
			tcsetattr(uart, TCSANOW, &uart_config_original);

	thread_running = false;

	exit(0);
}

/**
 * @details
 * The deamon app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 *
 * @brief Creates the tread for the deamon
 *
 * @param int argc, number of arguments (atomaticly calculated)
 * @param char *argv[], list of passed arguments
 *
 * @return 0 on success,  1 on error
 */
int bb_handler_main(int argc, char *argv[]){

	if (argc < 2) {
		warnx("missing command");
		usage();
	}

	if (!strcmp(argv[1], "start")) {

		/* this is not an error */
		if (thread_running)
			errx(0, "bb_handler already running\n");

		thread_should_exit = false;
		bb_task = task_spawn("bb_responder",
				SCHED_DEFAULT,
				SCHED_PRIORITY_DEFAULT,
				2048,
				bb_handler_thread_main,
				(const char **)argv);

		if (bb_task < 1){
			errx(0, "Klarte ikke A lage thread\n");
		}
		exit(0);
	}

	if (!strcmp(argv[1], "stop")) {
		thread_should_exit = true;

		while (thread_running) {
			usleep(200000);
			fprintf(stdout, ".");
			fflush(stdout);
		}

		warnx("\nterminated.");
		exit(0);
	}

	if (!strcmp(argv[1], "status")) {
		if (thread_running) {
			errx(0, "running");

		} else {
			errx(1, "not running");
		}
	}

	warnx("unrecognized command");
	usage();
	/* not getting here */
	return 0;

}

/**
 * @brief Printer bruk av deamon
 * @retval void
 *
 */
void usage()
{
	fprintf(stderr, "usage: bb_hanlder start [-d <devicename>] [-b <baud rate>]\n"
			"       bb_hanlder stop\n"
			"       bb_hanlder status\n");
	exit(1);
}


/*EOF*/
