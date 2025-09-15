CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
SMART_TARGET = smart_demo
TARGET = parking_simulation
SMART_SRCS = main_smart.cpp Car.cpp Parking.cpp
SMART_OBJS = $(SMART_SRCS:.cpp=.o)
SRCS = main.cpp Car.cpp Parking.cpp
OBJS = $(SRCS:.cpp=.o)

$(SMART_TARGET): $(SMART_OBJS)
	$(CXX) $(CXXFLAGS) -o $(SMART_TARGET) $(SMART_OBJS)

all: $(TARGET) $(SMART_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(SMART_OBJS) $(TARGET) $(SMART_TARGET)

run: $(TARGET)
	./$(TARGET)

run_smart: $(SMART_TARGET)
	./$(SMART_TARGET)

.PHONY: all clean run run_smart