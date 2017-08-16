app: detection.o  image_matfunctions.o uart.o image_processing.o files_operations.o
	g++  -o app    image_processing.o files_operations.o uart.o detection.o image_matfunctions.o -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -Wall
detection.o : detection.cpp
	g++  -c -Wall  detection.cpp 
image_matfunctions.o: image_matfunctions.cpp OutputData.h Configuration.h Picture.h Includes.h
	g++  -c -lm image_matfunctions.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -Wall
uart.o: uart.c
	gcc -c uart.c
image_processing.o:	image_processing.cpp
	g++ -c image_processing.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -Wall
files_operations.o:	files_operations.cpp
	g++ -c files_operations.cpp -Wall
clean:
	rm -f core app detection.o image_matfunctions.o uart.o files_operations.o
