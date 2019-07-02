CXX = g++

EXECUTABLE = photoFilters

SRCS = *.cpp
OBJS  = *.o

IMFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`

$(EXECUTABLE): $(OBJS)
	$(CXX) $(IMFLAGS) $(OBJS) -o $(EXECUTABLE) 

$(OBJS): $(SRCS)
	$(CXX) $(SRCS) $(IMFLAGS) -c $< 

clean:
	$(RM) $(OBJS)
	$(RM) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)