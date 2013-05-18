// MESSAGE STAR_IMAGE_METADATA PACKING

#define MAVLINK_MSG_ID_STAR_IMAGE_METADATA 180

typedef struct __mavlink_star_image_metadata_t
{
 uint64_t time_gps_usec; ///< Time from GPS
 uint64_t gps_timestamp; ///< Local time for LLA and time_gps_usec
 uint64_t att_timestamp; ///< Local time for attitude
 float variance_m; ///< Accuracy of LLA in meters
 uint32_t lat; ///< Latitude in 1E7 degrees
 int32_t lon; ///< Longitude in 1E7 degrees
 int32_t alt; ///< Altitude in 1E3 meters (millimeters) above MSL
 float roll; ///<  Roll angle (rad, Tait-Bryan, NED)
 float pitch; ///<  Pitch angle (rad, Tait-Bryan, NED)
 float yaw; ///<  Yaw angle (rad, Tait-Bryan, NED)
 float view_angle; ///<  Angle of view
 float focal_length; ///< length of the focal
 uint8_t file_name[30]; ///< Name of imagefile
 uint8_t star_sys_id; ///< userdefined ID of this system
} mavlink_star_image_metadata_t;

#define MAVLINK_MSG_ID_STAR_IMAGE_METADATA_LEN 91
#define MAVLINK_MSG_ID_180_LEN 91

#define MAVLINK_MSG_STAR_IMAGE_METADATA_FIELD_FILE_NAME_LEN 30

#define MAVLINK_MESSAGE_INFO_STAR_IMAGE_METADATA { \
	"STAR_IMAGE_METADATA", \
	14, \
	{  { "time_gps_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_star_image_metadata_t, time_gps_usec) }, \
         { "gps_timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_star_image_metadata_t, gps_timestamp) }, \
         { "att_timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_star_image_metadata_t, att_timestamp) }, \
         { "variance_m", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_star_image_metadata_t, variance_m) }, \
         { "lat", NULL, MAVLINK_TYPE_UINT32_T, 0, 28, offsetof(mavlink_star_image_metadata_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 32, offsetof(mavlink_star_image_metadata_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_INT32_T, 0, 36, offsetof(mavlink_star_image_metadata_t, alt) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_star_image_metadata_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_star_image_metadata_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_star_image_metadata_t, yaw) }, \
         { "view_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_star_image_metadata_t, view_angle) }, \
         { "focal_length", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_star_image_metadata_t, focal_length) }, \
         { "file_name", NULL, MAVLINK_TYPE_UINT8_T, 30, 60, offsetof(mavlink_star_image_metadata_t, file_name) }, \
         { "star_sys_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 90, offsetof(mavlink_star_image_metadata_t, star_sys_id) }, \
         } \
}


/**
 * @brief Pack a star_image_metadata message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_gps_usec Time from GPS
 * @param gps_timestamp Local time for LLA and time_gps_usec
 * @param att_timestamp Local time for attitude
 * @param variance_m Accuracy of LLA in meters
 * @param lat Latitude in 1E7 degrees
 * @param lon Longitude in 1E7 degrees
 * @param alt Altitude in 1E3 meters (millimeters) above MSL
 * @param roll  Roll angle (rad, Tait-Bryan, NED)
 * @param pitch  Pitch angle (rad, Tait-Bryan, NED)
 * @param yaw  Yaw angle (rad, Tait-Bryan, NED)
 * @param file_name Name of imagefile
 * @param view_angle  Angle of view
 * @param focal_length length of the focal
 * @param star_sys_id userdefined ID of this system
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_star_image_metadata_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t time_gps_usec, uint64_t gps_timestamp, uint64_t att_timestamp, float variance_m, uint32_t lat, int32_t lon, int32_t alt, float roll, float pitch, float yaw, const uint8_t *file_name, float view_angle, float focal_length, uint8_t star_sys_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[91];
	_mav_put_uint64_t(buf, 0, time_gps_usec);
	_mav_put_uint64_t(buf, 8, gps_timestamp);
	_mav_put_uint64_t(buf, 16, att_timestamp);
	_mav_put_float(buf, 24, variance_m);
	_mav_put_uint32_t(buf, 28, lat);
	_mav_put_int32_t(buf, 32, lon);
	_mav_put_int32_t(buf, 36, alt);
	_mav_put_float(buf, 40, roll);
	_mav_put_float(buf, 44, pitch);
	_mav_put_float(buf, 48, yaw);
	_mav_put_float(buf, 52, view_angle);
	_mav_put_float(buf, 56, focal_length);
	_mav_put_uint8_t(buf, 90, star_sys_id);
	_mav_put_uint8_t_array(buf, 60, file_name, 30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 91);
#else
	mavlink_star_image_metadata_t packet;
	packet.time_gps_usec = time_gps_usec;
	packet.gps_timestamp = gps_timestamp;
	packet.att_timestamp = att_timestamp;
	packet.variance_m = variance_m;
	packet.lat = lat;
	packet.lon = lon;
	packet.alt = alt;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.view_angle = view_angle;
	packet.focal_length = focal_length;
	packet.star_sys_id = star_sys_id;
	mav_array_memcpy(packet.file_name, file_name, sizeof(uint8_t)*30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 91);
#endif

	msg->msgid = MAVLINK_MSG_ID_STAR_IMAGE_METADATA;
	return mavlink_finalize_message(msg, system_id, component_id, 91, 47);
}

/**
 * @brief Pack a star_image_metadata message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_gps_usec Time from GPS
 * @param gps_timestamp Local time for LLA and time_gps_usec
 * @param att_timestamp Local time for attitude
 * @param variance_m Accuracy of LLA in meters
 * @param lat Latitude in 1E7 degrees
 * @param lon Longitude in 1E7 degrees
 * @param alt Altitude in 1E3 meters (millimeters) above MSL
 * @param roll  Roll angle (rad, Tait-Bryan, NED)
 * @param pitch  Pitch angle (rad, Tait-Bryan, NED)
 * @param yaw  Yaw angle (rad, Tait-Bryan, NED)
 * @param file_name Name of imagefile
 * @param view_angle  Angle of view
 * @param focal_length length of the focal
 * @param star_sys_id userdefined ID of this system
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_star_image_metadata_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t time_gps_usec,uint64_t gps_timestamp,uint64_t att_timestamp,float variance_m,uint32_t lat,int32_t lon,int32_t alt,float roll,float pitch,float yaw,const uint8_t *file_name,float view_angle,float focal_length,uint8_t star_sys_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[91];
	_mav_put_uint64_t(buf, 0, time_gps_usec);
	_mav_put_uint64_t(buf, 8, gps_timestamp);
	_mav_put_uint64_t(buf, 16, att_timestamp);
	_mav_put_float(buf, 24, variance_m);
	_mav_put_uint32_t(buf, 28, lat);
	_mav_put_int32_t(buf, 32, lon);
	_mav_put_int32_t(buf, 36, alt);
	_mav_put_float(buf, 40, roll);
	_mav_put_float(buf, 44, pitch);
	_mav_put_float(buf, 48, yaw);
	_mav_put_float(buf, 52, view_angle);
	_mav_put_float(buf, 56, focal_length);
	_mav_put_uint8_t(buf, 90, star_sys_id);
	_mav_put_uint8_t_array(buf, 60, file_name, 30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 91);
#else
	mavlink_star_image_metadata_t packet;
	packet.time_gps_usec = time_gps_usec;
	packet.gps_timestamp = gps_timestamp;
	packet.att_timestamp = att_timestamp;
	packet.variance_m = variance_m;
	packet.lat = lat;
	packet.lon = lon;
	packet.alt = alt;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.view_angle = view_angle;
	packet.focal_length = focal_length;
	packet.star_sys_id = star_sys_id;
	mav_array_memcpy(packet.file_name, file_name, sizeof(uint8_t)*30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 91);
#endif

	msg->msgid = MAVLINK_MSG_ID_STAR_IMAGE_METADATA;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 91, 47);
}

/**
 * @brief Encode a star_image_metadata struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param star_image_metadata C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_star_image_metadata_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_star_image_metadata_t* star_image_metadata)
{
	return mavlink_msg_star_image_metadata_pack(system_id, component_id, msg, star_image_metadata->time_gps_usec, star_image_metadata->gps_timestamp, star_image_metadata->att_timestamp, star_image_metadata->variance_m, star_image_metadata->lat, star_image_metadata->lon, star_image_metadata->alt, star_image_metadata->roll, star_image_metadata->pitch, star_image_metadata->yaw, star_image_metadata->file_name, star_image_metadata->view_angle, star_image_metadata->focal_length, star_image_metadata->star_sys_id);
}

/**
 * @brief Send a star_image_metadata message
 * @param chan MAVLink channel to send the message
 *
 * @param time_gps_usec Time from GPS
 * @param gps_timestamp Local time for LLA and time_gps_usec
 * @param att_timestamp Local time for attitude
 * @param variance_m Accuracy of LLA in meters
 * @param lat Latitude in 1E7 degrees
 * @param lon Longitude in 1E7 degrees
 * @param alt Altitude in 1E3 meters (millimeters) above MSL
 * @param roll  Roll angle (rad, Tait-Bryan, NED)
 * @param pitch  Pitch angle (rad, Tait-Bryan, NED)
 * @param yaw  Yaw angle (rad, Tait-Bryan, NED)
 * @param file_name Name of imagefile
 * @param view_angle  Angle of view
 * @param focal_length length of the focal
 * @param star_sys_id userdefined ID of this system
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_star_image_metadata_send(mavlink_channel_t chan, uint64_t time_gps_usec, uint64_t gps_timestamp, uint64_t att_timestamp, float variance_m, uint32_t lat, int32_t lon, int32_t alt, float roll, float pitch, float yaw, const uint8_t *file_name, float view_angle, float focal_length, uint8_t star_sys_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[91];
	_mav_put_uint64_t(buf, 0, time_gps_usec);
	_mav_put_uint64_t(buf, 8, gps_timestamp);
	_mav_put_uint64_t(buf, 16, att_timestamp);
	_mav_put_float(buf, 24, variance_m);
	_mav_put_uint32_t(buf, 28, lat);
	_mav_put_int32_t(buf, 32, lon);
	_mav_put_int32_t(buf, 36, alt);
	_mav_put_float(buf, 40, roll);
	_mav_put_float(buf, 44, pitch);
	_mav_put_float(buf, 48, yaw);
	_mav_put_float(buf, 52, view_angle);
	_mav_put_float(buf, 56, focal_length);
	_mav_put_uint8_t(buf, 90, star_sys_id);
	_mav_put_uint8_t_array(buf, 60, file_name, 30);
	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STAR_IMAGE_METADATA, buf, 91, 47);
#else
	mavlink_star_image_metadata_t packet;
	packet.time_gps_usec = time_gps_usec;
	packet.gps_timestamp = gps_timestamp;
	packet.att_timestamp = att_timestamp;
	packet.variance_m = variance_m;
	packet.lat = lat;
	packet.lon = lon;
	packet.alt = alt;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.view_angle = view_angle;
	packet.focal_length = focal_length;
	packet.star_sys_id = star_sys_id;
	mav_array_memcpy(packet.file_name, file_name, sizeof(uint8_t)*30);
	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STAR_IMAGE_METADATA, (const char *)&packet, 91, 47);
#endif
}

#endif

// MESSAGE STAR_IMAGE_METADATA UNPACKING


/**
 * @brief Get field time_gps_usec from star_image_metadata message
 *
 * @return Time from GPS
 */
static inline uint64_t mavlink_msg_star_image_metadata_get_time_gps_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field gps_timestamp from star_image_metadata message
 *
 * @return Local time for LLA and time_gps_usec
 */
static inline uint64_t mavlink_msg_star_image_metadata_get_gps_timestamp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field att_timestamp from star_image_metadata message
 *
 * @return Local time for attitude
 */
static inline uint64_t mavlink_msg_star_image_metadata_get_att_timestamp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  16);
}

/**
 * @brief Get field variance_m from star_image_metadata message
 *
 * @return Accuracy of LLA in meters
 */
static inline float mavlink_msg_star_image_metadata_get_variance_m(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field lat from star_image_metadata message
 *
 * @return Latitude in 1E7 degrees
 */
static inline uint32_t mavlink_msg_star_image_metadata_get_lat(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  28);
}

/**
 * @brief Get field lon from star_image_metadata message
 *
 * @return Longitude in 1E7 degrees
 */
static inline int32_t mavlink_msg_star_image_metadata_get_lon(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  32);
}

/**
 * @brief Get field alt from star_image_metadata message
 *
 * @return Altitude in 1E3 meters (millimeters) above MSL
 */
static inline int32_t mavlink_msg_star_image_metadata_get_alt(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  36);
}

/**
 * @brief Get field roll from star_image_metadata message
 *
 * @return  Roll angle (rad, Tait-Bryan, NED)
 */
static inline float mavlink_msg_star_image_metadata_get_roll(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field pitch from star_image_metadata message
 *
 * @return  Pitch angle (rad, Tait-Bryan, NED)
 */
static inline float mavlink_msg_star_image_metadata_get_pitch(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field yaw from star_image_metadata message
 *
 * @return  Yaw angle (rad, Tait-Bryan, NED)
 */
static inline float mavlink_msg_star_image_metadata_get_yaw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field file_name from star_image_metadata message
 *
 * @return Name of imagefile
 */
static inline uint16_t mavlink_msg_star_image_metadata_get_file_name(const mavlink_message_t* msg, uint8_t *file_name)
{
	return _MAV_RETURN_uint8_t_array(msg, file_name, 30,  60);
}

/**
 * @brief Get field view_angle from star_image_metadata message
 *
 * @return  Angle of view
 */
static inline float mavlink_msg_star_image_metadata_get_view_angle(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field focal_length from star_image_metadata message
 *
 * @return length of the focal
 */
static inline float mavlink_msg_star_image_metadata_get_focal_length(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field star_sys_id from star_image_metadata message
 *
 * @return userdefined ID of this system
 */
static inline uint8_t mavlink_msg_star_image_metadata_get_star_sys_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  90);
}

/**
 * @brief Decode a star_image_metadata message into a struct
 *
 * @param msg The message to decode
 * @param star_image_metadata C-struct to decode the message contents into
 */
static inline void mavlink_msg_star_image_metadata_decode(const mavlink_message_t* msg, mavlink_star_image_metadata_t* star_image_metadata)
{
#if MAVLINK_NEED_BYTE_SWAP
	star_image_metadata->time_gps_usec = mavlink_msg_star_image_metadata_get_time_gps_usec(msg);
	star_image_metadata->gps_timestamp = mavlink_msg_star_image_metadata_get_gps_timestamp(msg);
	star_image_metadata->att_timestamp = mavlink_msg_star_image_metadata_get_att_timestamp(msg);
	star_image_metadata->variance_m = mavlink_msg_star_image_metadata_get_variance_m(msg);
	star_image_metadata->lat = mavlink_msg_star_image_metadata_get_lat(msg);
	star_image_metadata->lon = mavlink_msg_star_image_metadata_get_lon(msg);
	star_image_metadata->alt = mavlink_msg_star_image_metadata_get_alt(msg);
	star_image_metadata->roll = mavlink_msg_star_image_metadata_get_roll(msg);
	star_image_metadata->pitch = mavlink_msg_star_image_metadata_get_pitch(msg);
	star_image_metadata->yaw = mavlink_msg_star_image_metadata_get_yaw(msg);
	star_image_metadata->view_angle = mavlink_msg_star_image_metadata_get_view_angle(msg);
	star_image_metadata->focal_length = mavlink_msg_star_image_metadata_get_focal_length(msg);
	mavlink_msg_star_image_metadata_get_file_name(msg, star_image_metadata->file_name);
	star_image_metadata->star_sys_id = mavlink_msg_star_image_metadata_get_star_sys_id(msg);
#else
	memcpy(star_image_metadata, _MAV_PAYLOAD(msg), 91);
#endif
}
