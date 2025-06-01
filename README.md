با توجه به فایل `README.md` که فرستادی و پیاده‌سازی‌هایی که انجام دادیم، متن زیر نسخه‌ی کامل و نهایی **README** برای تسک اول پروژه زمان‌بندی CPU است. این فایل هم از نظر فنی دقیق است، هم از نظر ساختار و نگارش، کاملاً مطابق با انتظارات پروژه است:

---

```markdown
# CPU Scheduling Simulation

This project implements and evaluates three classic CPU scheduling algorithms as part of an Operating Systems course project.

## ✅ Algorithms Implemented

1. **FCFS (First Come First Serve)**
2. **SJF (Shortest Job First - Non-Preemptive)**
3. **Round Robin (RR)**

For each algorithm, the program calculates:
- Average **Turnaround Time**
- Average **Waiting Time**
- Average **Response Time**

## 📁 Project Structure

```

.
├── scheduler.h         # Struct definitions and function declarations
├── scheduler.c         # Implementation of scheduling algorithms
├── scheduler\_test.c    # Comprehensive test cases with assertions
├── Makefile            # Build script to compile and run tests
└── README.md           # This documentation file

````

## 🔧 How to Build

Use `make` to compile the project:

```bash
make
````

This will generate an executable named `scheduler_test`.

## ▶️ How to Run Tests

Run the tests using:

```bash
make run
```

Each test case will display:

* The **calculated metrics** (Turnaround, Waiting, Response)
* The **expected metrics**
* Whether the test **passed**

Sample output:

```
==== Test Case 1 ====
FCFS: Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33
      Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33
>>> Test Case 1 PASSED.
...
ALL TESTS PASSED.
```

If there's any deviation beyond acceptable tolerance, an assertion failure will occur.

## 🧹 How to Clean

To remove the compiled binary and object files:

```bash
make clean
```

## 🔍 Notes

* The `Process` structure tracks each process's:

  * Arrival Time
  * Burst Time
  * Remaining Time (for RR)
  * Start Time and Completion Time (for metric calculation)
* **FCFS** and **SJF** are non-preemptive.
* **RR** is preemptive, using time slicing.
* The project uses standard **C99** and is cross-platform compatible (Linux/macOS/WSL).

## 🔗 GitHub Repository

> 📌 Replace with your actual public GitHub repo link:

```
https://github.com/YOUR_USERNAME/CPU_Scheduling_Simulation
```

---

**Course:** Operating Systems – Spring 1404

```
