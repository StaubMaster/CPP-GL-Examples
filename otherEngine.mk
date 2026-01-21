
################################################################
#                            Engine                            #
################################################################

ENGINE_HTTPS := https://github.com/StaubMaster/CPP-GL-Engine.git
ENGINE_REPO := $(REPOS_DIR)/Engine

REPOS_DYNAMIC += $(ENGINE_REPO)

#ENGINE_LIBRARYS = $(call repoLibrarys,$(ENGINE_REPO))
#ENGINE_INCLUDES = $(call repoIncludes,$(ENGINE_REPO))
#ENGINE_ARGUMENTS = $(call repoArguments,$(ENGINE_REPO))

ENGINE_LIBRARYS = $(ENGINE_REPO)/Engine.a
ENGINE_INCLUDES = $(ENGINE_REPO)/include

LIBRARYS += $(ENGINE_LIBRARYS)
INCLUDES += $(ENGINE_INCLUDES)
ARGUMENTS += $(ENGINE_ARGUMENTS)

$(ENGINE_REPO) :
	git clone $(ENGINE_HTTPS) $(ENGINE_REPO) -q
	$(MAKE) -C $(ENGINE_REPO) repos_clone -s

$(ENGINE_LIBRARYS) : $(ENGINE_REPO)
	$(MAKE) -C $(ENGINE_REPO) $(@:$(ENGINE_REPO)/%=%) -s

################################################################
