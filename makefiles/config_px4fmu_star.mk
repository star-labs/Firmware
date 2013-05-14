
#
# Makefile for the px4fmu_STAR configuration
#

#
# Imports
#

# $(PX4_BASE)/makefiles/config_px4fmu_default.mk

#PX4_MK_DIR

#include $(MK_DIR)/config_px4fmu_default.mk

include $(PX4_MK_DIR)/config_px4fmu_default.mk

#
# STAR modules
#
MODULES		+= star/bb_handler