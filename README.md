Vending Machine C++
====================

This is a vending machine simulator developed in C++. The program allows clients to purchase from a wide selection of items, remaining changes are returned to the client.

The vending machines allow elevated actions performed by a technician upon NFC verification. 

A technician can reset the vending machine to its initial state, activate and deactivate the distributor mechanism. 
A technician can also output data from the vending machine including money in, money out, distributor state, and quantity of the item sold.

An authenticated employee may select a free coffee.

Technician NFC:
- SZR547HTXG
- 4AXLDRM0VL

Employee NFC:
- NP3IL6R2XZ
- 4OLVT9H8L0
- 243NFWSF8P
- KRCBBVC49H

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

Prerequisites
---------------------

 * CMake 3.15
 * Boost.test
 * gcc
 * Git

To Clone
---------------------

```bash
git clone https://github.com/Exotic-Coder/VendingMachine.git
```

To Build
---------------------

```bash
cmake -Bbuild -H.
cmake --build build --target VendingMachine
```

To Open
---------------------

Linux
```bash
cd build
./VendingMachine
```

Windows
```bash
cd build
VendingMachine.exe
```

## Automated Unit Tests

To Build
---------------------

```bash
cd tests
cmake -Bbuild -H.
cmake --build build --target testing
```

To Test
---------------------

Linux
```bash
cd build
./testing
```

Windows
```bash
cd build
testing.exe
```
