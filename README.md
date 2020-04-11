# Triaxial Rigid Rotor  - Potential study

The following algorithm is composed of three main parts:

1. Calculates the potential $V(q)$, which is expressed in terms of the Jacobi elliptic functions. Calculation of the `Jacobi Amplitude` is done with the help of C++'s `boost` library.
2. Evaluates the potential at each $q\in[0,8]$ (for a so-called *forward* iteration) and $q\in[-8,0]$ (in a *backward* iteration) for a fixed $\theta$.
   1. Potential is reduced from the set of arguments $\mathbf{X}=\{I,j,A_1,A_2,A_3,\theta\}$ to only $\mathbf{x}=\{\theta\}$.
   2. Generate a potential stack for every $q$ value.
3. Evaluate the minimum value of the potential stack, for a given value of $\theta$.
   1. Iterate for the entire interval $\theta\in[-180,180]$ and generate an array with the minimum values $V_{min}^{\theta}$.

## Iteration method

A straightforward loop ($\mathcal{O}(n)$ with N-360 values) is generated, and then graphically represented:  
* **x-axis**: the coupling angle $\theta$
* **y-axis**: the minimum value of the potential $V(q)$ for that particular $\theta$: $V_{min}^{\theta}$.

In the potential stack generation, the step of $q$ is chosen $h=0.01$.

* size of step influences the precision of the calculations: ** almost $2%$ difference between $h_1=0.1$ and $h_2=0.01$.
* smaller $h$ is better (to some extent).

  