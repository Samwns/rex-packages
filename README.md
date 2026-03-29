# 📦 rex-packages

[![Registry](https://img.shields.io/badge/registry-rex--packages-blue)](https://github.com/Samwns/rex-packages)
[![License](https://img.shields.io/github/license/Samwns/rex-packages)](LICENSE)
[![Packages](https://img.shields.io/badge/packages-community-green)](packages/)
[![REX](https://img.shields.io/badge/powered%20by-REX-orange)](https://github.com/Samwns/REX)
[![Language](https://img.shields.io/badge/language-C%2B%2B-blue)](https://isocpp.org/)

Official **C++ library** registry for the [REX](https://github.com/Samwns/REX) package manager.

This repository stores and distributes C++ libraries that can be installed automatically using the REX package system. Community members can create and publish their own libraries here.

---

## 🧾 Description

`rex-packages` is a simple and structured registry designed to host **C++ libraries** for REX projects. Each package contains its own metadata, public headers, and source files, allowing the REX manager to download, install, and manage dependencies automatically.

---

## 📁 Structure

Each package must be placed in its own directory inside `packages/`:

```
packages/
 └── package-name/
      ├── rex.json          # Package metadata (required)
      ├── include/           # Public C++ headers (.h / .hpp)
      │   └── package-name.hpp
      └── src/               # Source files (.cpp / .c)
          └── package-name.cpp
```

The root `registry.json` file provides a machine-readable index of all available packages and their latest versions. The REX manager reads this file to discover and resolve packages.

---

## 📄 Package Format (`rex.json`)

Each package must include a `rex.json` file with the following metadata:

```json
{
  "name": "mathlib",
  "version": "1.0.0",
  "description": "Simple math utilities for C++ projects",
  "language": "cpp",
  "author": "rex-community",
  "license": "MIT",
  "include": "include",
  "dependencies": {}
}
```

| Field          | Required | Description                                       |
|----------------|----------|---------------------------------------------------|
| `name`         | ✅       | Unique package name (lowercase, `a-z`, `0-9`, `-`) |
| `version`      | ✅       | Semantic version (`MAJOR.MINOR.PATCH`)             |
| `description`  | ✅       | Short description of the library                   |
| `language`     | ✅       | Must be `"cpp"`                                    |
| `author`       | ❌       | Package author or maintainer                       |
| `license`      | ❌       | License identifier (e.g. `MIT`, `Apache-2.0`)      |
| `include`      | ❌       | Header directory relative to package root (default: `include`) |
| `dependencies` | ❌       | Map of package names to required semver versions   |

A JSON Schema is provided at [`schema/rex-package.schema.json`](schema/rex-package.schema.json) for automated validation.

---

## 🗂️ Registry API (`registry.json`)

The root `registry.json` is the machine-readable index consumed by REX:

```json
{
  "registry": "rex-packages",
  "version": "1.0.0",
  "language": "cpp",
  "schema": "schema/rex-package.schema.json",
  "packages": [
    {
      "name": "mathlib",
      "version": "1.0.0",
      "description": "Simple math utilities for C++ projects",
      "path": "packages/mathlib",
      "include": "include",
      "author": "rex-community",
      "license": "MIT"
    }
  ]
}
```

The REX manager can fetch this file from the repository to list, search, and resolve packages.

---

## ⚙️ How it works

The REX package manager will:

1. Fetch `registry.json` from this repository
2. Locate the requested package by name
3. Download the `include/` headers and `src/` files from `packages/<name>/`
4. Copy headers into the project's include path and sources into `/libs`
5. Resolve and install dependencies automatically

---

## ➕ Adding a package

1. Fork this repository
2. Create a folder inside `packages/` named after your library
3. Add your C++ headers in `include/` and source files in `src/`
4. Create a valid `rex.json` with the required fields
5. Add your package entry to `registry.json`
6. Run `python3 scripts/validate.py` to verify everything is correct
7. Open a Pull Request

See [CONTRIBUTING.md](CONTRIBUTING.md) for the full submission guide.

---

## ⚠️ Rules

- Package names must be **unique** and use only lowercase letters, numbers, and hyphens
- Every package **must** include a valid `rex.json` with `language` set to `"cpp"`
- Packages must contain at least one header file (`.h`/`.hpp`) in `include/` and one source file (`.cpp`/`.c`) in `src/`
- Dependencies must be properly declared with their exact semver versions
- Do not include compiled binaries, build artifacts, or IDE project files
- Source code must be placed inside the `include/` and `src/` subdirectories

---

## 📌 Versioning Policy

This registry follows [Semantic Versioning](https://semver.org/) (`MAJOR.MINOR.PATCH`):

| Change type                        | Version bump                         |
|------------------------------------|--------------------------------------|
| Breaking API changes               | MAJOR (`1.0.0` → `2.0.0`)           |
| New features (backwards-compatible)| MINOR (`1.0.0` → `1.1.0`)           |
| Bug fixes / patches               | PATCH (`1.0.0` → `1.0.1`)           |

- Always increment the version in `rex.json` when updating an existing package.
- Never overwrite a published version — create a new version instead.
- The `registry.json` should always reflect the **latest** version of each package.

---

## 🔍 Validation

A validation script is provided to check all packages before submission:

```bash
python3 scripts/validate.py
```

This verifies:
- `rex.json` is valid and has all required fields
- Package name matches its directory
- C++ headers and source files are present
- Dependencies reference existing packages
- `registry.json` is in sync with the `packages/` directory

---

## 🚀 Goal

To provide a simple and efficient **C++ library** distribution system for the REX ecosystem, enabling community members to create and share libraries with ease.

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).
