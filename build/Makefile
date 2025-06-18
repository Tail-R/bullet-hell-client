ifeq ($(OS), Windows_NT)
	CP = copy
	RM = del /Q
	MKDIR = if not exist "$(dir $@)" mkdir "$(dir $@)"
	RMDIR_R = rmdir /S /Q
	EXE = .exe
else
	CP = cp
	RM = rm -f
	MKDIR = mkdir -p $(dir $@)
	RMDIR_R =
	EXE =
endif

ROOTDIR = ..
SRCDIR = ../src
OBJDIR = obj

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lws2_32
INCLUDES = -I../SDL2/include -I../glad/include -I../glm
LIBRARIES = -L../SDL2/lib

SRCS = $(SRCDIR)/main.cpp \
	$(ROOTDIR)/glad/src/glad.c \
	$(SRCDIR)/logger/logger.cpp \
	$(SRCDIR)/frame/frame_template.cpp \
	$(SRCDIR)/frame/frame_serializer.cpp \
	$(SRCDIR)/socket/socket.cpp \
	$(SRCDIR)/packet_stream/packet_stream.cpp \
	$(SRCDIR)/renderer/renderer.cpp \

OBJS_CPP = $(filter %.cpp, $(SRCS))
OBJS_C = $(filter %.c, $(SRCS))

OBJS_CPP_OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(OBJS_CPP))
OBJS_C_OBJ = $(patsubst $(ROOTDIR)/glad/src/%.c, $(OBJDIR)/%.o, $(OBJS_C))

OBJS = $(OBJS_CPP_OBJ) $(OBJS_C_OBJ)

TARGET = bullet_hell$(EXE)

# Build rules
# $< is the input files (e.g., main.cpp)
# $@ is the output files (e.g., main.o)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBRARIES) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(MKDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(ROOTDIR)/glad/src/%.c
	$(MKDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)
	$(RMDIR_R) $(OBJDIR)
