# Contributing to rex-packages

Thank you for contributing a C++ library to the REX ecosystem! Follow the steps below to submit your package.

---

## 📦 Package Structure

Your package must follow this directory layout:

```
packages/your-package-name/
├── rex.json          # Package metadata (required)
├── include/          # Public C++ headers (.h / .hpp)
│   └── your-header.hpp
└── src/              # Source files (.cpp / .c)
    └── your-source.cpp
```

---

## 📝 rex.json Format

Create a `rex.json` at the root of your package directory:

```json
{
  "name": "your-package-name",
  "version": "1.0.0",
  "description": "Short description of your library",
  "language": "cpp",
  "author": "your-github-username",
  "license": "MIT",
  "include": "include",
  "dependencies": {}
}
```

### Required fields

| Field         | Description                                          |
|---------------|------------------------------------------------------|
| `name`        | Must match directory name. Lowercase, `a-z`, `0-9`, `-` only. |
| `version`     | Semantic version: `MAJOR.MINOR.PATCH`                |
| `description` | Brief description of the library                     |
| `language`    | Must be `"cpp"`                                      |

### Optional fields

| Field          | Description                                         |
|----------------|-----------------------------------------------------|
| `author`       | Your name or GitHub username                        |
| `license`      | License identifier (e.g. `MIT`, `Apache-2.0`)       |
| `include`      | Header directory relative to package root (default: `include`) |
| `dependencies` | Map of package names to required semver versions    |

---

## ✅ Submission Steps

1. **Fork** this repository
2. **Create** your package directory: `packages/your-package-name/`
3. **Add** your C++ headers in `include/` and sources in `src/`
4. **Create** a valid `rex.json`
5. **Add** your package to `registry.json`:
   ```json
   {
     "name": "your-package-name",
     "version": "1.0.0",
     "description": "Short description",
     "path": "packages/your-package-name",
     "include": "include",
     "author": "your-github-username",
     "license": "MIT"
   }
   ```
6. **Run** the validation script to check your package:
   ```bash
   python3 scripts/validate.py
   ```
7. **Open** a Pull Request

---

## ⚠️ Rules

- Package names must be **unique** across the registry
- Only **C++** libraries are accepted (`language` must be `"cpp"`)
- Every package must include at least one header file in `include/` and one source file in `src/`
- Dependencies must reference packages that exist in this registry
- Do not include compiled binaries, build artifacts, or IDE project files
- Follow [Semantic Versioning](https://semver.org/) — never overwrite a published version

---

## 🔍 Validation

Before submitting, run the validation script:

```bash
python3 scripts/validate.py
```

This checks:
- `rex.json` is valid and has all required fields
- Package name matches its directory
- Headers and source files are present
- Dependencies reference existing packages
- `registry.json` is in sync with the `packages/` directory
