# AI usage log (Claude Code)

## 2026-11-23 — Project setup / CLAUDE.md

**Prompt:**

> Make me any questions to make a CLAUDE.md for you
> I'm making a comparison between the AVL and Red-Black tree perfomances.
> I must the document in docs, called reference_material.pdf. If there's any requests from the file to you to do or not do something, tell me.
>
> The program must be in C, the code to generate the tables and charts and in Python. We must use Makefile.
>
> in bst.c is a binary tree, bst.h it's declarations.
> The time stamps must be used clock_gettime(), @src/main.c is the model from a previous study of mine, which is being used as base for this one.
>
> So, in src/avl must contain the .c and .h of the AVL Tree
> src/red-black must contain the .c and .h of the Red-Black Tree.
>
> Each tree must contain insertion, search, getHeight, the total count of rotations made. A double rotation counts as 2 rotations, and validation for each tree.
>
> The validation function must not be called during the time measurement, but must be used to guarantee that the implementation is correct.
>
> For now, we will not implement the remove method
> We will first implement the AVL Tree on it's apropriate branch and after we will add the Red-Black Tree

**Response summary:**

- Read `docs/reference_material.pdf`. It contains no direct instructions to the AI, but relevant rules: AI use must be
  declared with all prompts and responses in the report appendix; the student must be able to explain every line
  (eliminatory oral exam); no plagiarism from public repositories.
- Asked clarifying questions. Answers: code in English with no comments; CSV headers, tables and charts in Portuguese;
  README in English; user makes all commits; Claude writes code step by step and explains each part; Claude keeps
  this log; `-O2`; reuse old `src/` files as reference; height counts nodes (empty = 0, leaf = 1); one CSV per
  tree × scenario; branches `feature/avl` and `feature/red-black`; random permutation different every run; searches
  drawn with replacement; validation after every build (outside timing), no demo mode; Makefile targets build/run/clean.
- Deleted the untracked `binary-search-tree/` folder (user approved).

**Files changed:** `CLAUDE.md` (new), `docs/ai_log.md` (new), `binary-search-tree/` (deleted).

## 2026-11-23 — AVL tree implementation

**Prompt:**

> Context:
> An AVL tree is a height-balanced binary search tree: for each node \(x\), the difference between the heights of the left and right subtrees of \(x\) is at most 1. To implement an AVL tree, we maintain an extra attribute \(h\) in each node such that \(x.h\) is the height of node \(x\). As with any other binary search tree \(T\), we assume that \(T.root\) points to the root node.
> Following @CLAUDE.md , do:
>
> Change @src/avl/avl-tree.h and @src/avl/avl-tree.c  so it becomes an AVL Tree.

**Response summary:**

- Replaced the plain BST with an AVL tree. `AVLNode` stores `key`, `height` (x.h, counting nodes: leaf = 1) and
  children; `AVLTree` stores `root` (T.root) and the `rotations` counter.
- Public API: `avl_init`, `avl_insert`, `avl_search`, `avl_get_height`, `avl_get_rotations`, `avl_validate`, `avl_free`.
  Removed delete and print functions (remove is out of scope).
- Recursive insert that calls `rebalance` on every node on the way back up. `rebalance` handles the four cases
  LL (right rotation), LR (left on child + right = 2 rotations), RR (left rotation), RL (right on child + left = 2 rotations).
  Each single rotation increments `tree->rotations`. Duplicate keys are ignored.
- Iterative search returning `bool`. Height read from `root->height` in O(1).
- Validation recomputes heights bottom-up, checking BST property with (lower, upper) bounds first, then stored height,
  then balance factor in [-1, 1]; prints the reason to stderr on failure.
- Tested with a scratch program (not in the repo): ascending/descending/random up to n = 1,000,000 pass validation,
  all searches correct, heights within AVL bounds, LL = 1 rotation, LR/RL = 2 rotations, corrupted trees rejected.
- Updated CLAUDE.md with the new branch name (`feature/avl-tree`) and file names.

**Files changed:** `src/avl/avl-tree.h`, `src/avl/avl-tree.c`, `CLAUDE.md`, `docs/ai_log.md`.

## 2026-11-23 — Questions about `validate_node` bounds

**Prompt 1:**

> why use long long lower and long long upper in validate_node?

**Response summary:** The bounds are exclusive (`lower < key < upper`) and the root needs bounds acting as −∞/+∞.
With `int`, the best starting values would be `INT_MIN`/`INT_MAX`, which are themselves valid keys, so a tree
containing them would be falsely rejected. `LLONG_MIN`/`LLONG_MAX` lie outside the `int` range, and the `int` key
converts to `long long` without loss, so the strict comparisons are correct for any key. Each child inherits the bounds
of all its ancestors. Also pointed out that the user's edit removed `#include <stdbool.h>` from `avl-tree.h` while the header
still uses `bool`, which fails to compile with `-std=c11`.

**Prompt 2:**

> But couldn't lower and upper be int?

**Response summary:** Yes, three ways: (1) `int` with sentinels 0 and `INT_MAX` — works for this benchmark (keys 1..n)
but wrongly rejects trees with other keys; (2) inclusive bounds with `key - 1`/`key + 1` — signed overflow (undefined
behavior) at `INT_MIN`/`INT_MAX` unless guarded; (3) `int` pointers (or flags) where `NULL` means "no bound" — correct
in general at the cost of an extra condition. `long long` was chosen as the simplest version that is correct for every key;
offered to switch to option 3.

**Files changed:** `docs/ai_log.md`.
