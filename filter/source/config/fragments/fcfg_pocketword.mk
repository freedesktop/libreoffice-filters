all_fragments+=pocketword

# -----------------------------------------------
# count = 1
T4_POCKETWORD = \
    writer_PocketWord_File

# -----------------------------------------------
# count = 1
F4_POCKETWORD = \
    PocketWord_File

# -----------------------------------------------
# count = 0
L4_POCKETWORD =

# -----------------------------------------------
# count = 0
C4_POCKETWORD =

# -----------------------------------------------
TYPES_4fcfg_pocketword           = $(foreach,i,$(T4_POCKETWORD) types$/$i.xcu          )
FILTERS_4fcfg_pocketword         = $(foreach,i,$(F4_POCKETWORD) filters$/$i.xcu        )
FRAMELOADERS_4fcfg_pocketword    = $(foreach,i,$(L4_POCKETWORD) frameloaders$/$i.xcu   )
CONTENTHANDLERS_4fcfg_pocketword = $(foreach,i,$(C4_POCKETWORD) contenthandlers$/$i.xcu)

# -----------------------------------------------
# needed to get dependencies inside global makefile work!
ALL_4fcfg_pocketword = \
    $(TYPES_4fcfg_pocketword) \
    $(foreach,i,$(FILTERS_4fcfg_base) $(MISC)$/$i) \
    $(FRAMELOADERS_4fcfg_pocketword) \
    $(CONTENTHANDLERS_4fcfg_pocketword)
