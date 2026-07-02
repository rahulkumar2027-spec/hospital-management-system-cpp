# Hospital Management System (C++)

## Overview

A console-based Hospital Management System written in C++. It simulates hospital
operations — patient admission, employee salary calculation, pharmacy costing,
billing, scan booking, and a cafeteria — and doubles as a demonstration of
core Object-Oriented Programming concepts.

Patient records persist across runs using simple text-file storage, so
admitted patients are still there the next time you launch the program.

---

## How to Build & Run

```bash
g++ -Wall -Wextra -std=c++17 Code.cpp -o hospital
./hospital
```

Tested with `g++` on Linux; no external dependencies. `patients.txt` will be
created in the working directory the first time you admit a patient.

---

## Features

### 1. Patient Admission Management
- Admit new patients (name, age, auto-assigned ID).
- View patient details by ID.
- Records are saved to `patients.txt` on exit and reloaded on the next run.
- Admission is rejected with a clear error once hospital capacity (500) is reached.

### 2. Employee Management
- Register employee details across four categories: Doctor, Admin, Housekeeping, Maintenance.
- Calculate monthly salary from hours worked and employee type.

### 3. Pharmacy Module
- Calculate total supplier cost of tablets (int overload) and vials (float overload).
- Demonstrates function overloading.

### 4. Billing Module
- Calculate charges for General Ward and ICU stays.
- Combine both into a total bill using an overloaded `+` operator.

### 5. Scan Department
- List available imaging services (X-Ray, MRI, CT-Scan) and estimated duration.
- Select and confirm a scan type.

### 6. Cafeteria Module
- Order tea, coffee, sandwiches, or cookies and get a running total.

---

## Class Structure

```text
hospital
   |
   v
info
   |
   +------> patient
   |
   +------> employee

scan
ptime
   |
   v
scantime (multiple inheritance)

Person (virtual base class)
   |
   +--> PatientRole -----+
   |                     +--> DualRolePerson
   +--> StaffRole -------+
```

---

## OOP Concepts Demonstrated

| Concept | Where |
|---|---|
| Classes and Objects | `hospital`, `patient`, `employee`, `bill`, `cafe` |
| Inheritance | `patient` / `employee` → `info` → `hospital` |
| Multiple Inheritance | `scantime` inherits `scan` and `ptime` |
| Virtual Base Class | `PatientRole` / `StaffRole` both inherit `Person` virtually; `DualRolePerson` inherits both without duplicating `Person` (solves the diamond problem) |
| Constructors | All major classes |
| Function Overloading | `add(int,int)` / `add(float,float)` |
| Function Overriding | `display()` across `typesalone` → `typesalfour` |
| Static Members | `hospital::capacity` |
| Friend Function | `calcsal(employee&)` |
| Virtual Functions & Runtime Polymorphism | `typesalthree::display()` called through a base pointer to a derived object |
| Operator Overloading | `bill operator+` |
| Exception Handling | Custom checks (invalid age, negative hours/charges, full capacity, patient/scan not found) throw `std::invalid_argument` / `std::runtime_error`, caught with `try`/`catch` in `main()` |
| File Handling | `patients.txt` — patient records are written with `ofstream` and read back with `ifstream` |
| Dynamic Containers | `std::vector<patient>` instead of a fixed-size array |
| Dynamic Memory Allocation | `new cafe` / `delete cafe` |
| Inline Functions | Welcome message functions |
| `this` Pointer | Parameterized `bill` constructor |

---

## Known Limitations (by design, for a learning project)

- Single-file, console-only — no GUI or database.
- Only patient records persist to file; employee/billing/scan/cafeteria data is
  per-session only, to keep the file-handling demo simple and easy to explain.
- No authentication/roles — this models hospital *operations*, not access control.
