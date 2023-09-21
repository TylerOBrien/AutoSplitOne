NAME      := AutoSplitOne
BINARY    := bin/$(NAME)
SUB_DIR   := Aso Aso/Analyzers Aso/Graphics Aso/Math Aso/IO

SRC_DIR   := $(addprefix src/,$(SUB_DIR))
BUILD_DIR := $(addprefix build/,$(SUB_DIR))
SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJS      := $(patsubst src/%.cpp,build/%.o,$(SRC))

CC        := g++
LD        := g++
LIBS      := -lncurses -lopencv_core -lopencv_videoio -lws
INCLUDES  := -I include -I /usr/local/include/wsserver -I /usr/local/include/opencv4
CFLAGS    := -Wall -O3 $(INCLUDES) -c

vpath %.cpp $(SRC_DIR)

define cc-subdir
$1/%.o: %.cpp
	$(CC) $(CFLAGS) $$< -o $$@
endef

all: prepare build/main.o $(OBJS)
	$(LD) -Wl,-s build/main.o $(OBJS) $(LIBS) -o $(BINARY)

prepare: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) -o $@ $?

clean:
	@rm -rf $(BUILD_DIR) build/main.o

$(foreach bdir,$(BUILD_DIR),$(eval $(call cc-subdir,$(bdir))))
