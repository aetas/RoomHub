[TODO: how to do wiring of boards - e.g. connect main board to io board]

## RJ45 ports connections

It assumes RJ45 connector is using T568B termination. It means wires in connector are in order:
1. orange-white
2. orange
3. green-white
4. blue
5. blue-white
6. green
7. brown-white
8. brown

Then wires usage is following:

| Color        | usage          |
| ------------ | -------------- |
| orange       | +5V            |
| orange-white | GND            |
| blue         | digital in/out |
| blue-white   | digital in/out |
| green        | digital in/out |
| green-white  | digital in/out |
| brown        | PJON           |
| brown-white  | analog in      |

[TODO: check if PJON is on brown or brown-white!]