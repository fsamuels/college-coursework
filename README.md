# College Coursework

A collection of coursework from **CSC 210 – Programming Concepts** (Section 001),
completed in the Spring 2000 semester. The course is an introductory/intermediate
programming sequence taught primarily in **C++** (with a small amount of **Perl**),
covering procedural programming, finite-state machines, abstract data types,
class design, operator overloading, inheritance and polymorphism, dynamic data
structures, templates, and basic network sockets.

All work lives under the single top-level directory `CSC 210 - Programming Concepts`,
organized into numbered homework folders (`0_HW` through `8_HW`) plus a few
exploratory folders (`Perl`, `Socket`, `Test`). The notes below describe each
distinct component.

> **Note:** The code targets a late-1990s/2000 C++ toolchain — it uses pre-standard
> headers (`iostream.h`, `fstream.h`, etc.), `void main()` in some files, and the
> X11 / Solaris environment that was used in the course. The graphical assignments
> rely on a course-provided window library (`sxwin`) and the X11 libraries, and the
> per-folder `README` files note they "must be run on a POSIX system."

---

## 0_HW — Hello World

- **What it is:** The introductory assignment.
- **What it does:** Prints `Hello CSC 210 World!` to standard output.
- **Technologies:** C++ (`hello.cpp`).

## 1_HW — Array and String Functions

- **What it is:** A set of low-level array and C-string manipulation exercises.
- **What it does:** Implements functions such as printing and reversing integer
  arrays (`initList.cpp`) and computing string length and reversing C-strings by
  hand without standard library helpers (`str.cpp`), with a test harness
  (`test.cpp`).
- **Technologies:** C++.

## 2_HW — Drawing Program (Finite-State Machine GUI)

- **What it is:** A graphical drawing program used to illustrate finite-state
  machine design within a GUI.
- **What it does:** Lets the user draw rectangles, circles, and line segments on a
  canvas by selecting modes via on-screen buttons; the program transitions between
  states (`MODE_CHANGE`, `WAITING`, `DRAWING`) based on mouse position and clicks.
  Includes a homegrown `String` class.
- **Technologies:** C++ with the `sxwin` window library and X11; built via a
  `makefile`. Modules: `drawing.cpp`, `buttons.{h,cpp}`, `canvas.{h,cpp}`,
  `sxwin.{h,cpp}`, `String.{h,cpp}`, `defs.h`. (Requires a POSIX/X11 system.)

## 3_HW — Finite-State Machine Text Processors

- **What it is:** Two command-line programs built as finite-state machines.
- **What it does:**
  - `number.cpp` — parses a hexadecimal, octal, or integer string from the command
    line (using Horner's Rule) and converts it between bases, with input error
    checking.
  - `index.cpp` — reads a text file and computes a readability index by counting
    words, syllables, and sentences as a character-by-character state machine.
- **Technologies:** C++.

## 4_HW — Pizza Ordering (Classes & Operator Overloading)

- **What it is:** An object-oriented model of pizzas and customer orders.
- **What it does:** A `Pizza` class tracks size, price, and toppings; an `Order`
  class associates a customer name and phone number with pizzas and computes a
  total. Both classes overload the `<<` output operator for formatted printing,
  exercised by `pizzaDriver.cpp`.
- **Technologies:** C++. Files: `Pizza.{h,cpp}`, `Order.{h,cpp}`, `defs.h`,
  `pizzaDriver.cpp`.

## 5_HW — Spell Checker / Dynamic Dictionary

- **What it is:** A dynamically resizing `Dictionary` abstract data type and a
  spell-checking program built on it.
- **What it does:** The `Dictionary` class stores a growable, sorted list of words
  (starting capacity grows as needed). `main.cpp` implements a `spellCheck` program
  that reads an input file against a dictionary file and reports words not found.
  `industrial.cpp` is a stress-test driver that performs tens of thousands of random
  insert/lookup operations. Sample word-list data files are included
  (`smallDictionary`, `smallDictionary2`, `textfile`).
- **Technologies:** C++. Files: `Dictionary.{h,cpp}`, `main.cpp`, `industrial.cpp`,
  `test.cpp`.

## 6_HW — Worm Game: Worm Class

- **What it is:** The core `Worm` data structure for a Snake/Worm-style game.
- **What it does:** Models the worm as a chain of `WormSegment` objects, handling
  its length, head position, direction, movement, and collision/`existsAt` queries.
  A `Level` class manages the playing field. `wormDriver.cpp` tests the `Worm` class
  in isolation. Includes a homegrown `String` class.
- **Technologies:** C++ with the `sxwin` window library and X11; built via a
  `makefile`. Files: `Worm.{h,cpp}`, `WormSegment.{h,cpp}`, `Level.{h,cpp}`,
  `String.{h,cpp}`, `gameDefs.h`, `sxwin.{h,cpp}`, `wormDriver.cpp`, `wormGame.cpp`.
  (Requires a POSIX/X11 system.)

## 7_HW — Vector Class (Dynamic Linked Structure)

- **What it is:** A fixed-length numeric `Vector` ADT backed by a linked node
  structure.
- **What it does:** Supports element get/set (1-indexed), length, addition, inner
  product, copy, and assignment, with an overloaded `<<` operator for debugging.
  `testVector.cpp` is an interactive command-driven test program for the operations.
- **Technologies:** C++. Files: `Vector.{h,cpp}`, `testVector.cpp`, `makefile`.

## 8_HW — Worm Game: Polymorphic Game Objects

- **What it is:** An extension of the worm game (6_HW) adding an inheritance
  hierarchy of interactive game objects, demonstrating polymorphism.
- **What it does:** Defines an abstract `Object` base class with a virtual `action()`
  method invoked when the worm encounters a tile, plus concrete subclasses for
  power-ups and hazards: `PlusObject`, `MinusObject`, `GrowObject`, `ShrinkObject`,
  `FasterObject`, `SlowerObject`, `DieObject`, and `WallObject`. The `Level` class
  stores a grid of `Object` pointers so new behaviors can be added with minimal code
  changes. A compiled sample executable (`wormGame`) is included.
- **Technologies:** C++ with the `sxwin` window library and X11; built via a
  `makefile`. Files: `Object.h`, the `*Object.{h,cpp}` family, `Level.{h,cpp}`
  (with `Level_mods.cpp` / `Level_old.cpp` variants), `Worm.{h,cpp}`,
  `WormSegment.{h,cpp}`, `String.{h,cpp}`, `gameDefs.h`, `sxwin.{h,cpp}`,
  `sys_utils.h`, `wormGame.cpp`. (Requires a POSIX/X11 system.)

## Perl — First Perl Script

- **What it is:** An introductory Perl exercise.
- **What it does:** Prompts for a username on standard input and prints a greeting.
- **Technologies:** Perl (`myfirst.pl`), using `strict` and warnings.

## Socket — Network Socket Experiments

- **What it is:** Small exploratory programs for BSD/POSIX socket programming.
- **What it does:** `echo.cpp` creates a TCP socket, binds it to the echo port (7),
  and listens for connections; `test.cpp` is a minimal socket-creation snippet.
- **Technologies:** C/C++ with the POSIX sockets API (`sys/socket.h`,
  `netinet/in.h`).

## Test — C++ Templates Practice

- **What it is:** Self-directed practice with C++ function templates.
- **What it does:** `mytemplates.h` defines generic `swap`, `average`, and
  `whoIsBigger` template functions; `swap_test.cpp`, `average_test.cpp`, and
  `whoisbigger_test.cpp` exercise them across `int`, `float`, and `double` types.
- **Technologies:** C++ templates.

---

### Ambiguities / notes

- **6_HW and 8_HW are related but distinct assignments.** 6_HW builds the `Worm`
  data structure; 8_HW reuses much of that code and adds the polymorphic `Object`
  hierarchy. They are documented as separate components above because they are
  separate homework folders with different goals, despite the shared files
  (`Worm`, `WormSegment`, `String`, `sxwin`).
- **Authorship is mixed.** Several files carry the student's header
  (Forrest Samuels), while skeleton/driver and library files credit course staff
  (e.g., Matt Stallmann, Suzanne Balik) — typical of provided starter code for
  these assignments.
- **`String`, `sxwin`, and related support files are duplicated** across the
  graphical assignments (2_HW, 6_HW, 8_HW); each homework folder is self-contained.
