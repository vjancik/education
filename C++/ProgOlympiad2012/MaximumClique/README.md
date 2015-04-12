#Maximum Clique

###Assignment

In a network of connected spies. Find the biggest network of fully interconnected spies. That is, in a network of nodes connected by edges, find a group where every node is directly connected by an edge with every other node. Such a group is called a clique. Find the maximum clique inside a network.

This is an NP-Hard problem, but was relaxed, because of a constraint. The constraint is that for a group of K spies, there is at most 3\*k number of edges between them. This means that the largest possible clique is of 7 elements.

**Sample Input**
```
5 6
1 2
1 3
1 4
1 5
3 2
4 2
```

**Sample Output**
```
1 2 3
```
