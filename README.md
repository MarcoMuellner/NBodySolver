# NBodySolver

NbodySolver provides simple implementations of four different
numerical methods to solve the gravitational N-Body problem.
The available implementations are:

- Euler method
- Leapfrog method
- RK4 method
- Verlet (not yet functional)

## Build
Create a build directory

```bash
mkdir build && cd build
```

Call cmake

```
cmake ..
```

and build the software
```
make
```
To run the code simply call

```
./NBodySolver
``

