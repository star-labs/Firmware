
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

# Blir dette rett variabel?
#export MODULE_SEARCH_DIRS += $(PX4_MODULE_SRC)/star/


#
# STAR modules
#
MODULES		+= star/bb_handler