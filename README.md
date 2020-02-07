Vending Machine C++
====================

This is a C++ virtual vending machine program allowing clients to select an item from a vending machine. 
Changes are returned to the client and the employee if the coins inserted is more than the remaining price.

The vending machines allows for elevated actions performed by a technician with NFC authentication check. 

A technician can reset the vending machine to its initial state, activate and deactivate the distributor mechanism.

Upon NFC verification an employee can select a coffee for free.

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
