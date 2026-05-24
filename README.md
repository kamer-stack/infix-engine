# infix-engine

### Infix to Postfix Expression Converter and Evaluator

A command-line program that tokenizes an infix arithmetic expression, converts it to postfix notation using the Shunting Yard Algorithm, and evaluates the result using a custom stack implementation.

Also includes a gamified web interface (`index.html`) built with the same logic.

---

## Screenshots

### Web Interface

![Web Interface](<img width="1810" height="984" alt="window" src="https://github.com/user-attachments/assets/7f7e9601-ab6b-4702-be2e-2859def66e8a" />)


### Terminal Output
![Terminal Output](<img width="738" height="1054" alt="terminal" src="https://github.com/user-attachments/assets/50acc4f8-411c-4337-9c3b-eb93f3abfab1" />)

---

## How to Compile

```bash
g++ tokenizer.cpp converter.cpp evaluator.cpp main.cpp -o program
```

## How to Run

```bash
./program
```

Type your expression and press Enter.

---

## Example

**Input:**
```
a + b * (c + 2)
```

**Output:**
```
a b c 2 + * +
Enter value for a: 3
Enter value for b: 5
Enter value for c: 2
23
```

---

## Features

- Full tokenizer with C++ identifier validation
- Infix to postfix using Shunting Yard Algorithm
- Supports all 3 bracket types — `()` `[]` `{}`
- Unary minus support — `-a`, `-(a+b)`
- Custom stack using linked list (no STL stack)
- Variable prompts via `stderr`, result via `stdout`
- Proper exit codes for all error types

---

## Exit Codes

| Code | Meaning | Example |
|------|---------|---------|
| 0 | Success | `a + b * c` |
| 1 | Syntax error | `a ++ b`, `(a + b]` |
| 2 | Runtime error | division by zero |
| 3 | Logical error | empty expression, `()` |

---

## Test Cases

| Input | Expected |
|-------|----------|
| `a + b * (c + 2)` | `a b c 2 + * +` → 23 |
| `{a + [b * (c + d)]}` | `a b c d + * +` → 15 |
| `-a + b` | `0 a - b +` |
| `(a + b]` | Syntax error: mismatched brackets |
| `a / b` (b=0) | Runtime error: division by zero |
| `()` | Logical error: empty brackets |
| `*a + b` | Syntax error: cannot start with * |

---

## File Structure

```
infix-engine/
├── main.cpp           → entry point, handles I/O and exit codes
├── tokenizer.h/cpp    → breaks expression into typed tokens
├── converter.h/cpp    → infix to postfix (Shunting Yard Algorithm)
├── evaluator.h/cpp    → evaluates postfix using a stack
├── stack.h            → custom linked list stack implementation
├── index.html         → gamified web interface
└── screenshots/
    ├── website.png
    └── terminal.png

```

---

## Web Version

Open `index.html` in any browser for an interactive gamified version with XP, coins and streak system.

Live demo: **https://github.com/kamer-stack/infix-engine**

---

> Built with C++ | Custom Stack | Shunting Yard Algorithm
