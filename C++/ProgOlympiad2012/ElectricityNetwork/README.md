#Electricity network

###Assignment

This is a network flow feasibility problem. Implement an electrical grid that contains Cities (consumers) and Electricity plants (producers). For the output, either print out that the network is infeasible to fully connect while satisfying the required electricity consumption of each city or the limited electricity production of each plant. Or print out index of the plant the city is connected to. If it’s a plant, print out the index of the same plant.

Network constraints:
- Through one edge of the network, only the electricity from a single electricity plant can flow.
- A city can only be powered through a singe plant. Also, we can’t pass electricity from one plant through another.
- Each plant has a capacity of electricity it can produce in a day. Each city has a capacity of electricity it consumes in a given day. These capacities must be satisfied.
- Each edge of the network has a capacity, the maximum amout of electricity that can pass through it in a day.

**Sample input**
```
5 5
E 1 5 10
E 1 5 20
M 3 15 10
M 4 5 5
```

**Sample output**
```
2 2 3 3 3
```

**Sample input**
```
5 5
E 1 5 10
E 1 5 20
M 3 12 10
M 4 5 5
```

**Sample output**
```
nemozne
```
