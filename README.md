# 📦 rex-packages

[![Registry](https://img.shields.io/badge/registry-rex--packages-blue)](https://github.com/Samwns/rex-packages)
[![License](https://img.shields.io/github/license/Samwns/rex-packages)](LICENSE)
[![Packages](https://img.shields.io/badge/packages-community-green)](packages/)
[![REX](https://img.shields.io/badge/powered%20by-REX-orange)](https://github.com/Samwns/REX)

Official package registry for the [REX](https://github.com/Samwns/REX) library manager.

This repository stores and distributes packages that can be installed automatically using the REX package system.

---

## 🧾 Description

`rex-packages` is a simple and structured registry designed to host libraries for REX projects. Each package contains its own metadata and source code, allowing the REX manager to download, install, and manage dependencies automatically.

---

## 📁 Structure

Each package must be placed in its own directory inside `packages/`:

```
packages/
 ├── package-name/
 │    ├── rex.json
 │    └── src/
 └── another-package/
      ├── rex.json
      └── src/
```

The root `registry.json` file provides a machine-readable index of all available packages and their latest versions.

---

## 📄 Package Format (`rex.json`)

Each package must include a `rex.json` file with basic metadata:

```json
{
  "name": "mathlib",
  "version": "1.0.0",
  "description": "Simple math utilities",
  "dependencies": {
    "utils": "1.0.0"
  }
}
```

| Field          | Required | Description                                    |
|----------------|----------|------------------------------------------------|
| `name`         | ✅       | Unique package name (lowercase, no spaces)     |
| `version`      | ✅       | Semantic version (`MAJOR.MINOR.PATCH`)         |
| `description`  | ✅       | Short description of the package               |
| `dependencies` | ❌       | Map of package names to required versions      |

---

## ⚙️ How it works

The REX package manager will:

1. Locate the package in this repository via `registry.json`
2. Download its files from the `packages/<name>/src/` directory
3. Install it into the `/libs` directory of your project
4. Resolve and install dependencies automatically

---

## ➕ Adding a package

1. Fork this repository
2. Create a folder inside `packages/` named after your package
3. Add your source code inside `src/`
4. Create a valid `rex.json` with the required fields
5. Update `registry.json` to include your package entry
6. Open a Pull Request with your changes

---

## ⚠️ Rules

- Package names must be **unique** and use only lowercase letters, numbers, and hyphens
- Every package **must** include a valid `rex.json` file
- Dependencies must be properly declared with their exact versions
- Avoid unnecessary or large binary files
- Source code must go inside the `src/` subdirectory

---

## 📌 Versioning Policy

This registry follows [Semantic Versioning](https://semver.org/) (`MAJOR.MINOR.PATCH`):

| Change type              | Version bump |
|--------------------------|-------------|
| Breaking changes         | MAJOR (`1.0.0` → `2.0.0`) |
| New features (backwards-compatible) | MINOR (`1.0.0` → `1.1.0`) |
| Bug fixes / patches      | PATCH (`1.0.0` → `1.0.1`) |

- Always increment the version in `rex.json` when updating an existing package.
- Never overwrite a published version — create a new version instead.
- The registry `registry.json` should always reflect the **latest** version of each package.

---

## 🚀 Goal

To provide a simple and efficient package distribution system for the REX ecosystem, enabling community members to create and share libraries with ease.

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).
