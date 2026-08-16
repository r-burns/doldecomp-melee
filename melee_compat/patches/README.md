# aurora patches

Local fixes to `extern/aurora` needed to build here. Submodule working-tree
changes are not captured by the parent repo, so they are kept as patches.

Apply with:

```bash
git -C extern/aurora apply ../../melee_compat/patches/*.patch
```

| Patch | Why |
| --- | --- |
| `aurora-cstring.patch` | `lib/internal.hpp` calls `std::memcpy` without including `<cstring>`. Recent libstdc++ (GCC 16 / Clang 22 here) no longer provides it transitively, so every TU including `internal.hpp` fails. Should go upstream. |
