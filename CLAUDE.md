# CLAUDE.md

Empirical comparison of **AVL** vs **Red-Black** trees (university assignment, Unifor — Construção e Análise de Algoritmos).
The assignment spec is `docs/reference_material.pdf` (Portuguese). It is the source of truth; re-read it when in doubt.

The repo was cloned from a previous study (Insertion Sort vs Merge Sort). `src/main.c`, `src/table.py`, `src/graphics.py`
and `src/theoretical_graphics.py` are **references**: keep the same overall structure and adapt them to the trees.

## Working rules

- **Never commit, push, or merge.** The user makes all commits. Creating/switching branches is allowed.
- Branches: `feature/avl` first (AVL only), then `feature/red-black`. Do not start the Red-Black tree until asked.
- **No comments or docstrings in any code** (C, Python, Makefile). Explanations go in the chat, not in the code.
- **Explain every step.** The oral exam is eliminatory: the user must be able to explain every line. After each
  implementation step, explain in the chat what was done and why (e.g. where each AVL case LL/RR/LR/RL is handled
  and when it happens; which node decides each Red-Black insertion fix-up case; how validation works and what it
  checks first). Implement in small steps, not one big dump.
- Do not copy implementations verbatim from public repositories or textbooks (plagiarism rule in the spec).
- **AI log:** the spec requires every AI prompt and response in the report appendix. After each task, append an
  entry to `docs/ai_log.md`: date, the user's prompt verbatim, a summary of the response, and files changed.
- Remove/delete operations are **out of scope for now** (bonus item; may be added later).

## Language

- Code (identifiers, function names, terminal output): **English**.
- CSV headers, table images and chart labels/titles: **Portuguese**.
- `README.md`: **English**.

## Layout

```
src/main.c              benchmark driver (both trees, same inputs)
src/avl/                AVL tree .c + .h
src/red-black/          Red-Black tree .c + .h
src/table.py            statistics + tables (adapted from previous study)
src/graphics.py         comparison charts AVL vs RB
src/theoretical_graphics.py  regressions vs theory
data/                   generated CSVs, tables, charts
docs/                   spec PDF, ai_log.md
```

`src/avl/bst.c|h` and `src/red-black/bst.c|h` are a plain BST used as a starting point. Both trees are linked into one
executable, so public symbols must be prefixed (`avl_*`, `rb_*`) and types distinct (`AVLNode`/`AVLTree`, `RBNode`/`RBTree`).

## Tree requirements (each tree)

- Integer keys. Duplicates are ignored on insert (inputs are distinct anyway).
- `insert` (restores balance), `search` (returns whether the key is present), `get_height`, rotation counter, `validate`, `free`.
- **Height counts nodes:** empty tree = 0, single node = 1.
- **Rotation counter:** +1 per single rotation; a double rotation counts as 2 (implement double rotations as two counted
  single rotations). The counter lives in the tree struct, not a global.
- **Validation:**
  - AVL: BST property (min/max bounds, not just parent-child) and balance factor in [-1, 1] on every node
    (and stored heights consistent).
  - Red-Black: BST property + the 5 RB properties (every node red or black; root black; NIL leaves black;
    red node has black children; same black-height on every root-to-NIL path).

## Benchmark requirements (src/main.c)

- Timing only with `clock_gettime(CLOCK_MONOTONIC, ...)`, measured in batch (total time of n operations), seconds as double,
  same formula as the previous study.
- **Validation never runs inside the timed region.** It runs after every build (outside timing); on failure print an
  error and exit with non-zero status.
- n ∈ {1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000}; **50 repetitions** per (tree × scenario × n).
- Scenarios: ascending (1..n), descending (n..1), random (random permutation of 1..n via Fisher-Yates,
  **a new permutation every repetition, different every run** → seed from time, not fixed).
- Per repetition: generate the key array and the search array **once**, then give **both trees the same keys in the same
  order and the same searches**. Searches: n keys drawn **with replacement** from 1..n (all exist in the tree).
- Measurements per repetition per tree: build time (n inserts into an empty tree), search time (n searches),
  height after build, rotations during build.
- Make sure `-O2` can't optimize away the search loop (accumulate/check the found count).
- Allocate/fill arrays and free trees outside the timed region.
- Output: one CSV per tree × scenario, e.g. `data/avl/avl_crescente.csv`, `data/red-black/rb_aleatorio.csv`,
  one row per repetition, Portuguese headers (e.g. `n,repeticao,tempo_construcao_s,tempo_busca_s,altura,rotacoes`),
  header written once (unlike the previous study, which repeated it).
- Paths are relative to the project root (the binary is run from the root via `make run`).

## Build

Makefile at the root. Flags: `-Wall -Wextra -std=c11 -O2` (report must state them). Targets: `all`/build, `run`, `clean`
(plus `fclean`/`re`). Must compile `src/main.c`, `src/avl/*.c` and `src/red-black/*.c`. No demo target.

## Analysis (Python, run from the root with `.venv/bin/python src/<script>.py`)

Dependencies in `requirements.txt` (pandas, scipy, matplotlib, numpy).

- Build and search time: mean, sample std dev (ddof=1), 95% CI (Student t), min, max.
- Height and rotations: mean (constant across repetitions in ascending/descending scenarios).
- Charts: AVL vs RB, one per scenario and metric, 95% CI error bars on time charts.
- Regression: build time vs n compared to n·log(n); mean height fit to a·log₂(n) + b, compare a with ≈1.44 (AVL)
  and ≈2 (RB).
