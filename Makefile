.SUFFIXES:

include $(DEVKITPPC)/wii_rules

TARGET := Nektarynki
BUILD := build
SOURCES := src
DATA := assets
INCLUDES := include

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT := $(CURDIR)/$(TARGET)
export VPATH := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR := $(CURDIR)/$(BUILD)

CPPFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))

export LD := $(CXX)
export OFILES := $(CPPFILES:.cpp=.o)

export INCLUDE := $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
	-I$(DEVKITPRO)/libogc/include \
	-I$(PORTLIBS)/include

export LIBDIRS := $(PORTLIBS)

export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

export LIBS := -lgrrlib -lpngu `$(PREFIX)pkg-config freetype2 libpng libjpeg --libs` -lfat -lwiiuse -lbte -logc -lm

.PHONY: all clean

all: $(BUILD)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	rm -rf $(BUILD) $(OUTPUT).elf $(OUTPUT).dol

else

DEPENDS := $(OFILES:.o=.d)

$(OUTPUT).dol: $(OUTPUT).elf

$(OUTPUT).elf: $(OFILES)

-include $(DEPENDS)

endif
