CFLAGS := -Wall -Wextra -Werror $(shell pkg-config --cflags --libs opencv4)

facedet: facedet.cpp
	$(CXX) facedet.cpp $(CFLAGS) -o facedet

clean:
	rm facedet
