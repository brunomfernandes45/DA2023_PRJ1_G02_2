# **Instructions**

## **Usage**

To use this project follow the steps below:

1. Clone the repository to your computer.
2. Open the project directory in an IDE (preferably CLion because our project uses CMake).
3. Run the program simply by clicking the button 'Run' on the top of the screen (CLion).
4. Select the input file you want to use. The data files must be '.csv'.  The format of the files should be the following:
    1. For the stations file, the data should be in this order: Name,District,Municipality,Township,Line.
    2. For the network file, the data should be in this order: Station_A,Station_B,Capacity,Service. 
5. Every input (except the files) must be in CamelCase (ex. LisboaOriente).
6. If you're using Windows operating system, you may run into some problems with some characters like 'à', 'ç' or 'ã'. In that case consider using files that don't have those types of characters.

## **Features**

In the main menu there are 10 options, one of them being the exit option. The other 9, in the respective order, do the following:

1. Displays every station's name, district and line.
2. Displays all the information of a chosen station, including its connections.
3. Calculates the maximum number of trains that can simultaneously travel between two stations (Max Flow).
4. Calculates the pairs that require the most amount of trains (Max Flow).
5. Calculates the transportation needs of each municipality and district and displays the top-k.
6. Calculates the maximum number of trains that can simultaneously arrive at a station (Max Flow).
7. Calculates the maximum amount of trains that can simultaneously travel through the minimum cost path between two stations (Min Cost).
8. Calculates the maximum number of trains that can simultaneously travel between two stations with just 1 type of service (Max Flow).
9. Calculates the difference in every station's maximum number of trains that can simultaneously arrive at it after blocking one connection (Max Flow).