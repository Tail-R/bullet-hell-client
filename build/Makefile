ifeq ($(OS), Windows_NT)
	CP = copy
	RM = del /Q
	MKDIR = if not exist $(dir $@) mkdir $(dir $@)
	SEP = \\
	EXE = .exe
	LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lws2_32
	INCLUDES = -I..\\SDL2\\include
	LIBRARIES = -L..\\SDL2\\lib
else
	CP = cp
	RM = rm -f
	MKDIR = mkdir -p $(dir $@)
	SEP = /
	EXE =
	LDFLAGS =
	INCLUDES =
	LIBRARIES =
endif

SRCDIR = ..$(SEP)src
OBJDIR = obj

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wundef -Wcast-align -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wuseless-cast -Wnon-virtual-dtor -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wswitch-enum -Wno-unused-parameter
SRCS = $(SRCDIR)$(SEP)main.cpp \
	$(SRCDIR)$(SEP)logger$(SEP)logger.cpp \
	$(SRCDIR)$(SEP)frame$(SEP)frame_template.cpp \
	$(SRCDIR)$(SEP)frame$(SEP)frame_serializer.cpp \
	$(SRCDIR)$(SEP)socket$(SEP)socket.cpp \
	$(SRCDIR)$(SEP)packet_stream$(SEP)packet_stream.cpp \
	$(SRCDIR)$(SEP)renderer$(SEP)renderer.cpp \
	$(SRCDIR)$(SEP)sprite$(SEP)sprite.cpp

OBJS = $(patsubst ..$(SEP)src$(SEP)%.cpp, $(OBJDIR)$(SEP)%.o, $(SRCS))
TARGET = bullet_hell$(EXE)

# Build rules
# $< is the input files (e.g., main.cpp)
# $@ is the output files (e.g., main.o)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBRARIES) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJDIR)$(SEP)%.o: ..$(SEP)src$(SEP)%.cpp
	$(MKDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET) $(OBJS)
