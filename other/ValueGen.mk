
################################################################

VALUE_GEN_DIR       := $(OTHER_DIR)/ValueGen
VALUE_GEN_LIBRARYS  := $(VALUE_GEN_DIR)/ValueGen.a
VALUE_GEN_INCLUDES  := $(VALUE_GEN_DIR)/
VALUE_GEN_ARGUMENTS :=

OTHER_LIST += $(VALUE_GEN_DIR)
LIBRARYS   += $(VALUE_GEN_LIBRARYS)
INCLUDES   += $(VALUE_GEN_INCLUDES)
ARGUMENTS  += $(VALUE_GEN_ARGUMENTS)

$(VALUE_GEN_LIBRARYS) : $(VALUE_GEN_DIR)
	$(MAKE) -C $(VALUE_GEN_DIR) -s $(@:$(VALUE_GEN_DIR)/%=%)

################################################################
