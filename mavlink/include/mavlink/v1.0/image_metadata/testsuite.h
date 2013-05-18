/** @file
 *	@brief MAVLink comm protocol testsuite generated from image_metadata.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef IMAGE_METADATA_TESTSUITE_H
#define IMAGE_METADATA_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_image_metadata(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

	mavlink_test_image_metadata(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_star_image_metadata(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_star_image_metadata_t packet_in = {
		93372036854775807ULL,
	93372036854776311ULL,
	93372036854776815ULL,
	185.0,
	963498920,
	963499128,
	963499336,
	297.0,
	325.0,
	353.0,
	381.0,
	409.0,
	{ 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214 },
	147,
	};
	mavlink_star_image_metadata_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.time_gps_usec = packet_in.time_gps_usec;
        	packet1.gps_timestamp = packet_in.gps_timestamp;
        	packet1.att_timestamp = packet_in.att_timestamp;
        	packet1.variance_m = packet_in.variance_m;
        	packet1.lat = packet_in.lat;
        	packet1.lon = packet_in.lon;
        	packet1.alt = packet_in.alt;
        	packet1.roll = packet_in.roll;
        	packet1.pitch = packet_in.pitch;
        	packet1.yaw = packet_in.yaw;
        	packet1.view_angle = packet_in.view_angle;
        	packet1.focal_length = packet_in.focal_length;
        	packet1.star_sys_id = packet_in.star_sys_id;
        
        	mav_array_memcpy(packet1.file_name, packet_in.file_name, sizeof(uint8_t)*30);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_star_image_metadata_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_star_image_metadata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_star_image_metadata_pack(system_id, component_id, &msg , packet1.time_gps_usec , packet1.gps_timestamp , packet1.att_timestamp , packet1.variance_m , packet1.lat , packet1.lon , packet1.alt , packet1.roll , packet1.pitch , packet1.yaw , packet1.file_name , packet1.view_angle , packet1.focal_length , packet1.star_sys_id );
	mavlink_msg_star_image_metadata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_star_image_metadata_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_gps_usec , packet1.gps_timestamp , packet1.att_timestamp , packet1.variance_m , packet1.lat , packet1.lon , packet1.alt , packet1.roll , packet1.pitch , packet1.yaw , packet1.file_name , packet1.view_angle , packet1.focal_length , packet1.star_sys_id );
	mavlink_msg_star_image_metadata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_star_image_metadata_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_star_image_metadata_send(MAVLINK_COMM_1 , packet1.time_gps_usec , packet1.gps_timestamp , packet1.att_timestamp , packet1.variance_m , packet1.lat , packet1.lon , packet1.alt , packet1.roll , packet1.pitch , packet1.yaw , packet1.file_name , packet1.view_angle , packet1.focal_length , packet1.star_sys_id );
	mavlink_msg_star_image_metadata_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_image_metadata(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_star_image_metadata(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // IMAGE_METADATA_TESTSUITE_H
