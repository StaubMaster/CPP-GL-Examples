
################################################################

SPLINE_DIR := $(OTHER_DIR)/Spline

OTHER_LIST += $(SPLINE_DIR)

SPLINE_LIBRARYS := $(SPLINE_DIR)/Spline.a
SPLINE_INCLUDES := $(SPLINE_DIR)/../
SPLINE_ARGUMENTS :=

LIBRARYS += $(SPLINE_LIBRARYS)
INCLUDES += $(SPLINE_INCLUDES)
ARGUMENTS += $(SPLINE_ARGUMENTS)

$(SPLINE_LIBRARYS) : $(SPLINE_DIR)
	$(MAKE) -C $(SPLINE_DIR) -s $(@:$(SPLINE_DIR)/%=%)

################################################################
