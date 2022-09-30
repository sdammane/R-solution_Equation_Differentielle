CXX=g++
CXXFLAGS= -g -std=c++11
SRCS= EquaDiff.cpp  odeSol.cpp testEquaDiff.cpp

OBJS=$(SRCS:%.cpp=%.o)
DEPS=$(SRCS:%.cpp=%.d)

all: myExe

myExe: $(OBJS)
			$(CXX) $^ -o $@

-include $(DEPS)

%.o: %.cpp
		$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

clean:
		rm -rf *.o *.d *~
