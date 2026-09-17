
################################################################

NEW_POLY_HEDRA_DIR       := $(OTHER_DIR)/NewPolyHedra
NEW_POLY_HEDRA_LIBRARYS  := $(NEW_POLY_HEDRA_DIR)/NewPolyHedra.a
NEW_POLY_HEDRA_INCLUDES  := $(NEW_POLY_HEDRA_DIR)/
NEW_POLY_HEDRA_ARGUMENTS :=

OTHER_LIST += $(NEW_POLY_HEDRA_DIR)
LIBRARYS   += $(NEW_POLY_HEDRA_LIBRARYS)
INCLUDES   += $(NEW_POLY_HEDRA_INCLUDES)
ARGUMENTS  += $(NEW_POLY_HEDRA_ARGUMENTS)

$(NEW_POLY_HEDRA_LIBRARYS) : $(NEW_POLY_HEDRA_DIR)
	$(MAKE) -C $(NEW_POLY_HEDRA_DIR) -s $(@:$(NEW_POLY_HEDRA_DIR)/%=%)

################################################################
