CC = g++
DEBUG = -g
CFLAGS = -std=c++14 -Wall -c $(DEBUG)
LFLAGS = $(DEBUG)

#output dirs
EXEC = cards
BUILD_DIR = build
SRC_DIR = src
LIB_DIR = libs
RES_DIR = resources

#determine the required files
SRCS = $(shell find $(SRC_DIR) -name *.cpp)
HEADERS = $(shell find $(SRC_DIR) -name *.h)
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

#libraries
LIBS = glad

LIB_DIRS = $(addprefix $(LIB_DIR)/, $(LIBS))
LIB_INC = $(addsuffix /include, $(LIB_DIRS))

LIB_DEPS = $(addprefix $(BUILD_DIR)/lib, $(addsuffix .a, $(LIBS)))

#linking
LIB_FLAGS = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -L$(BUILD_DIR) $(addprefix -l, $(LIBS))

INC_DIRS = $(shell find $(SRC_DIR) -type d) $(LIB_DIR)/stb $(LIB_DIR)/glm $(LIB_INC)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

CPPFLAGS = $(CFLAGS) $(INC_FLAGS)

RM = rm
MKDIR = mkdir -p

$(BUILD_DIR)/$(EXEC): $(OBJS) $(LIB_DEPS) $(BUILD_DIR)/$(RES_DIR)
	$(MKDIR) $(BUILD_DIR)
	$(CC) $(OBJS) $(LIB_FLAGS) $(LFLAGS) -o $@

$(BUILD_DIR)/%.o: %.cpp $(BUILD_DIR)/%.d
	$(MKDIR) $(dir $@)
	$(CC) $(CPPFLAGS) $< -o $@

$(BUILD_DIR)/lib%.a:
	make -C $(LIB_DIR)/$(@:$(BUILD_DIR)/lib%.a=%)
	cp $(@:$(BUILD_DIR)/lib%.a=$(LIB_DIR)/%/src/lib)$(@:$(BUILD_DIR)/lib%=%) $@;

$(BUILD_DIR)/$(RES_DIR):
	ln -s ../$(RES_DIR) $(BUILD_DIR)/$(RES_DIR)

clean:
	$(RM) -r $(BUILD_DIR)

run: $(BUILD_DIR)/$(EXEC)
	$(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/%.d: %.cpp
	$(MKDIR) $(dir $@)
	printf $(dir $@) > $@
	$(CC) $(CPPFLAGS) -MM -MG $*.cpp >> $@

ifneq "$(MAKECMDGLOBALS)" "clean"
-include $(SRCS:%.cpp=$(BUILD_DIR)/%.d)
endif
