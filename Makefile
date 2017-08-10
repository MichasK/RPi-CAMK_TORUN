app: detection.o  functions.o uart.o
	g++ -pg -o app   detection.o functions.o -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -Wall
detection.o : detection.cpp
	g++ -pg -c  detection.cpp -Wall
functions.o: functions.cpp OutputData.h Configuration.h Picture.h Includes.h
	g++ -pg -c -lm functions.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -Wall
uart.o: uart.c
	gcc -c uart.c

clean:
	rm -f core app detection.o functions.o uart.o
