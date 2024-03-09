executable: driver.o
	g++ -o executable driver.o

driver.o: driver.cpp Graph.h
	g++ -c driver.cpp

clean:
	rm *.o executable