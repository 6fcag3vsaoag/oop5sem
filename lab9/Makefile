CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TRANSACTION_TARGET = transaction_demo
SMART_TARGET = smart_demo
TARGET = parking_simulation
TRANSACTION_SRCS = main_transaction.cpp Car.cpp Parking.cpp
TRANSACTION_OBJS = $(TRANSACTION_SRCS:.cpp=.o)
SMART_SRCS = main_smart.cpp Car.cpp Parking.cpp
SMART_OBJS = $(SMART_SRCS:.cpp=.o)
SRCS = main.cpp Car.cpp Parking.cpp
OBJS = $(SRCS:.cpp=.o)

$(TRANSACTION_TARGET): $(TRANSACTION_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TRANSACTION_TARGET) $(TRANSACTION_OBJS)

$(SMART_TARGET): $(SMART_OBJS)
	$(CXX) $(CXXFLAGS) -o $(SMART_TARGET) $(SMART_OBJS)

all: $(TARGET) $(SMART_TARGET) $(TRANSACTION_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(SMART_OBJS) $(TRANSACTION_OBJS) $(TARGET) $(SMART_TARGET) $(TRANSACTION_TARGET)

run: $(TARGET)
	./$(TARGET)

run_smart: $(SMART_TARGET)
	./$(SMART_TARGET)

run_transaction: $(TRANSACTION_TARGET)
	./$(TRANSACTION_TARGET)

.PHONY: all clean run run_smart run_transaction