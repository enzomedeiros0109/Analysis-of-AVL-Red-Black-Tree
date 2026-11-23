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
