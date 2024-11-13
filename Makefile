CXX = g++
CXXFLAGS = -Iinclude -Iinclude/glfw -Iinclude/imgui
LDFLAGS = -lmingw32 -lglfw3 -lopengl32
SRC_DIR = src
BUILD_DIR = build
EXEC = $(BUILD_DIR)/main.exe

IMGUI_SRCS = include/imgui/imgui_demo.cpp \
include/imgui/imgui_draw.cpp \
include/imgui/imgui_impl_glfw.cpp \
include/imgui/imgui_impl_opengl3.cpp \
include/imgui/imgui_tables.cpp \
include/imgui/imgui_widgets.cpp \
include/imgui/imgui.cpp

# find all .cpp files in SRC_DIR
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(IMGUI_SRCS)

# generate object files from source files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# default target compile and link
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

# compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BUILD_DIR)/%.o: $(IMGUI_SRCS)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# clean up build files
clean:
	rm -f $(BUILD_DIR)/*.o $(EXEC)