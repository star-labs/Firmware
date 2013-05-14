
#
# Makefile for the px4fmu_STAR configuration
#

#
# Imports
#

# $(PX4_BASE)/makefiles/config_px4fmu_default.mk

include $(MK_DIR)/config_px4fmu_default.mk

#
# STAR modules
#
MODULES		+= star/bb_handler