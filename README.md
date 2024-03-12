## Traveling Salesman Problem
Consider 5 cities of interest, namely a) Reno, b) San Francisco, c) Salt Lake City, d) Seattle, and e) Las Vegas. 
Using information from the road network and assuming a metric of 40 miles per gallon, the cost of each travelling in terms of gas was calculated.
Based that information:
- A graph was created with each of its vertices corresponding to one of these cities and its edges being weighted by the associated miles for each trip.
- The Traveling Salesman Problem was solved in a way such that traveling salesman starts from Reno, visits all cities in the 
cityData.txt file and returns to Reno. This problem was solved in the brute force-way, by identifying all possible paths.

## HOW TO RUN
There is a supplied makefile, in a terminal run "make", a file called "executable" should be made. 
Run the program by entering "./executable". 
To make adjustments in city data, alter the "cityData.txt" file. Efficient path solution will be in the "solution.txt" file.
The start/finish city should be the first item in cityData.txt.