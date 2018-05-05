CFLAGS := -Wall -Wextra -Werror $(shell pkg-config --cflags --libs opencv)

facedet: facedet.cpp
	$(CXX) $(CFLAGS) facedet.cpp -o facedet

clean:
	rm facedet
