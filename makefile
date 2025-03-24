# Configuration MinGW64
CXX := g++
WX_CONFIG := wx-config
WX_CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS := $(shell $(WX_CONFIG) --libs)

CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude $(WX_CXXFLAGS)
LDFLAGS := $(WX_LIBS)
TARGET := StaffHub.exe

# Sources
SRC_DIR := src
SRCS := \
	$(SRC_DIR)/Employee/Employee.cpp \
	$(SRC_DIR)/Employee/Manager.cpp \
	$(SRC_DIR)/Employee/Programmer.cpp \
	$(SRC_DIR)/Controllers/EmployeeController.cpp \
	$(SRC_DIR)/Controllers/InterfaceController.cpp \
	$(SRC_DIR)/Utils/FileReader.cpp \
	$(SRC_DIR)/Utils/StringUtility.cpp \
	$(SRC_DIR)/Main.cpp

OBJS := $(SRCS:.cpp=.o)

# Règles
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean