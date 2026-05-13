# C Mini Projects — Getting Back Into It

Ordered to ease back into the language, compilation, and project structure.

---

## Stage 1 — Remember the syntax and toolchain

These are single `.c` files. Goal: get comfortable with `gcc main.c -o main && ./main` again.

### 1. FizzBuzz with a twist
Classic, but implement it as a function that takes `n` and prints the sequence.
Reminds you of: functions, loops, printf, integer arithmetic.

### 2. String reverser
Take a string literal, reverse it in-place using a char array and two-pointer swap.
Reminds you of: arrays, pointers, indexing, null terminator, strlen.

### 3. Simple calculator (stdin input)
Read two numbers and an operator from stdin with `scanf`, do the math, print the result.
Reminds you of: scanf, switch/case, basic I/O, handling division by zero.

### 4. Number guessing game
Pick a hardcoded secret number, loop on `scanf` until the user guesses it, print higher/lower hints.
Reminds you of: while loops, conditionals, basic game loop structure.

---

## Stage 2 — Pointers and memory

Single file still, but the focus shifts to the parts of C that don't exist in C# the same way.

### 5. Swap function (the pointer lesson)
Write a `swap(int *a, int *b)` function and call it. Then do the same for strings (char pointers).
Goal: actually feel the difference between pass-by-value and pass-by-pointer.

### 6. Dynamic array
Use `malloc` to allocate an int array of user-specified size, fill it, print it, then `free` it.
Add a `realloc` call to double the capacity. Print addresses alongside values with `%p`.
Reminds you of: malloc/free, pointer arithmetic, the heap.

### 7. Linked list (add, print, free)
Implement a singly linked list with a `Node` struct. Write `push`, `print_list`, and `free_list`.
Reminds you of: structs, struct pointers, `->` notation, heap allocation, NULL termination of lists.

---

## Stage 3 — Structs and logic

Still single file or two files. Building something that feels like a real small program.

### 8. Student grade tracker
Define a `Student` struct with name (char array), grade (float), and id (int).
Create an array of 5 students, compute the average grade, print the top scorer.
Reminds you of: structs, arrays of structs, simple aggregation logic.

### 9. Stack implementation
Implement a fixed-size integer stack with `push`, `pop`, `peek`, `is_empty` using a struct + array.
Use it to check if a string of brackets `{[()]}` is balanced.
Reminds you of: structs with state, returning error codes (int), thinking in C idioms.

### 10. Caesar cipher
Encrypt and decrypt a string from stdin using a shift value also from stdin.
Handle wrap-around (z -> a), and leave non-alpha characters unchanged.
Reminds you of: char arithmetic, modulo, iterating over strings.

---

## Stage 4 — Multiple files and headers

Now you split things up. Goal: understand `#include`, header guards, compiling multiple `.c` files,
and linking them: `gcc main.c utils.c -o main`

### 11. Math utilities library
Create `mathutils.h` and `mathutils.c` with functions: `clamp`, `lerp`, `is_prime`, `factorial`.
Call them from `main.c`. Practice writing a proper header with `#ifndef` guards.

### 12. String utilities library
Create `strutils.h` / `strutils.c` with: `str_trim` (remove leading/trailing spaces),
`str_count_char`, `str_to_upper`, `str_starts_with`. Use only `<string.h>` and `<ctype.h>`.

### 13. Contact book (file I/O + structs)
A `Contact` struct with name and phone number (both char arrays).
Store up to 20 contacts in a fixed array. Support adding, listing, and searching by name.
Save to and load from a `.txt` file using `fopen`/`fprintf`/`fscanf`.
Split into: `contact.h`, `contact.c`, `main.c`.
Reminds you of: file I/O, multi-file projects, separation of concerns in C.

---

## Stage 5 — A small "real" project

One cohesive thing with multiple files, a Makefile, and actual usefulness.

### 14. Terminal particle simulation
Simulate N particles in a 2D box. Each has position (x, y) and velocity (vx, vy).
Each tick, update positions, bounce off walls, print a simple ASCII grid to the terminal.
Use `usleep` to throttle the loop. Split into `particle.h`, `particle.c`, `main.c`.
Stretch goal: add gravity, or simple elastic collision between particles.
This is the physics sim that iSH can actually run — no graphics needed.

### 15. Makefile + multi-file project skeleton
Not a feature, but a skill. Write a `Makefile` that:
- Compiles each `.c` file into a `.o` object file separately
- Links them into the final binary
- Has a `clean` target
- Has a `run` target
Goal: understand separate compilation, object files, and why Makefiles exist.

---

## Stage S — Build your own string type

This one sits between stages 3 and 4 in difficulty but deserves its own section because it is
the single best exercise for internalizing how C memory actually works. You are rebuilding
what C++ std::string and C# string do under the hood, from scratch.

### S. Dynamic string struct
Define a String struct with three fields:

  char *data;      // heap-allocated char buffer
  int   length;    // how many characters are currently in it
  int   capacity;  // how much memory is actually allocated

The key idea: when length reaches capacity, realloc to double the capacity.
This is called a growth strategy — the same trick std::vector uses internally.

Write these functions in mystring.h / mystring.c:
  str_new(const char *initial)    -- allocate and copy initial value
  str_append(String *s, ...)      -- grow if needed, then copy new chars in
  str_copy(String *s)             -- return a fresh independent heap copy
  str_equals(String *a, String *b)
  str_free(String *s)             -- free the inner buffer, zero the struct

Then write a main.c that creates strings, appends to them in a loop, and
calls str_free at the end. Reason through every malloc/realloc/free manually.

What this teaches:
  - The difference between the struct on the stack and its data on the heap
  - Why you must free the inner buffer, not just the struct itself
  - Defensive programming: what if malloc returns NULL?
  - Why C# strings feel "free" -- because this is happening invisibly

Stretch goal: add str_find(String *s, const char *needle) returning an index,
and str_slice(String *s, int start, int end) returning a new String.

---

## Fat Structs / Data-Oriented Thinking

Inspired by Casey Muratori's "The Big OOPs" talk and the Handmade Hero project.
The core idea: instead of inheritance trees and virtual dispatch, use a single flat
struct with all possible fields. Data is dumb. Logic lives in systems (free functions).
Call with: ideas a, ideas b, ideas c, ideas d, ideas e

### A. Fat entity pool
Build a fixed array of 256 Entity structs. Each has position, velocity, health,
and a flags field (bitmask for is_active, is_player, is_enemy, etc.).
Write update_all() and render_all() as plain loops that check flags inline.
No function pointers. No type dispatch. No switch on a type enum.
Then mentally compare: what would this look like with a base class + virtual update()?
That contrast is the whole lesson.

### B. SoA vs AoS benchmark
Implement the same particle sim twice:
  AoS: struct Particle { float x, y, vx, vy; }  particles[1000];
  SoA: struct { float xs[1000], ys[1000], vxs[1000], vys[1000]; } particles;
Run 100,000 ticks of position update on each. Time with clock() from <time.h>.
Print the results. On iSH the gap is small due to emulation, but the code
structure difference is the real lesson -- SoA is what DOD people mean by
cache-friendly layout.

### C. Immediate mode terminal UI
IMGUI is Muratori's other big idea: UI widgets own no state. The caller passes
everything in on every frame. Implement a tiny terminal IMGUI:
  draw_button(const char *label, int selected)
  draw_progress_bar(int value, int max)
  draw_menu(const char **items, int count, int selected)
These just printf to stdout. Build a simple interactive menu on top using raw
stdin reads. Feels completely different from any retained-mode widget system.

### D. System vs object refactor
Pick any small simulation (Conway's Game of Life is perfect).
First implement it the "OOP way": a Cell struct with an update_cell() function
that takes a pointer to one cell and its neighbours.
Then refactor: the data is a flat grid array, the logic is simulate_step().
The second version is pure DOD -- data is dumb, the system transforms it.
Notice how the second version is easier to serialize, easier to parallelise,
and easier to reason about in terms of what actually touches memory.

### E. Flat binary serialization
One of fat structs' practical superpowers: because layout is flat and known,
you can save the entire state with fwrite(&entity, sizeof(Entity), 1, f)
and load it back with fread. No serialization library. No JSON. No schema.
Build a save/load system for the entity pool from project A.
Then try the same with a tagged union approach and feel the difference.
Stretch: add a version field to the struct so you can detect and migrate old saves.

---

## Toolchain cheatsheet (iSH / Alpine)

```sh
# Install the C toolchain
apk add build-base

# Single file
gcc main.c -o main
./main

# Multiple files
gcc main.c utils.c -o main

# With warnings (recommended habit)
gcc -Wall -Wextra main.c -o main

# With debug symbols (for when things go wrong)
gcc -g main.c -o main

# Run with Makefile
make
make clean
```
