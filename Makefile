app: detection.o  functions.o
	g++ -o app   detection.o functions.o -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -Wall
detection.o : detection.cpp
	g++ -c  detection.cpp -Wall
functions.o: functions.cpp functions.h
	g++ -c -lm functions.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -Wall

clean:
	rm -f core app detection.o functions.o
