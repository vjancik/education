#IOS Project 2

###Assignment

Implement in C, the synchronization problem *Building H2O*. The details of which can be found in [The Little Book of Semaphores](http://www.greenteapress.com/semaphores/downey08semaphores.pdf)(Page 143).

####Description

There exist two types of processes: Oxygen, Hydrogen. To create a molecule, one atom of oxygen and two atom of hydrogen must exist and be consumed by the bonding.

####Usage

```
./h2o N GH GO B
```

- `N` is the number of processes representing oxygen. The number of processes representing hydrogen is always `2*N`, `N > 0`.
- `GH` is the maximum amount of time (in milliseconds), after which a new hydrogen process is generated. `GH >= 0 && GH < 5001`.
- `GO` is the maximum amount of time (in milliseconds), after which a new oxygen process is generated. `GO >= 0 && GO < 5001`.
- `B` is the maximum amount of time (in milliseconds) it takes to `bond` the atoms into a molecule. `B >= 0 && B < 5001`.
- All parameters are whole numbers.

####Implementation details

- Each atom is one process.
- The main process generates two processes, each for generation of one type of atom processes.
- Each atom process executes their actions in parallel with the others, and concurrently output the information about their actions to `h2o.out`
- Shared memory and semaphores are used for synchronization.

####Example Input, Output

Input: `$ ./h2o 1 0 0 0`

Output: `h2o.out`

```
1	: H 1	: started
2	: H 1	: waiting
3	: H 2	: started
4	: H 2	: waiting
5	: O 1	: started
6	: O 1	: ready
7	: O 1	: begin bonding
8	: H 2	: begin bonding
9	: H 1	: begin bonding
10	: H 1	: bonded
11	: H 2	: bonded
12	: O 1	: bonded
13	: O 1	: finished
14	: H 2	: finished
15	: H 1	: finished
```
