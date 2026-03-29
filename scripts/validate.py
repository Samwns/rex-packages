#!/usr/bin/env python3
"""
Validates all packages in the rex-packages registry.

Checks performed for each package directory under packages/:
  1. rex.json exists and is valid JSON
  2. Required fields are present: name, version, description, language
  3. Package name matches its directory name
  4. Language is "cpp"
  5. Version follows semver format (MAJOR.MINOR.PATCH)
  6. An include/ directory with at least one header (.h or .hpp) exists
  7. A src/ directory with at least one source file (.cpp or .c) exists
  8. Dependencies (if declared) reference packages that exist in the registry
  9. registry.json is consistent with on-disk packages

Exit code 0 on success, 1 on any validation failure.
"""

import json
import os
import re
import sys

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PACKAGES_DIR = os.path.join(REPO_ROOT, "packages")
REGISTRY_PATH = os.path.join(REPO_ROOT, "registry.json")

SEMVER_RE = re.compile(r"^\d+\.\d+\.\d+$")
NAME_RE = re.compile(r"^[a-z][a-z0-9-]*$")

errors = []


def error(msg):
    errors.append(msg)
    print(f"  ERROR: {msg}")


def validate_package(pkg_dir):
    pkg_name = os.path.basename(pkg_dir)
    print(f"Validating package: {pkg_name}")

    # 1. rex.json exists
    rex_json_path = os.path.join(pkg_dir, "rex.json")
    if not os.path.isfile(rex_json_path):
        error(f"[{pkg_name}] Missing rex.json")
        return

    # 2. rex.json is valid JSON
    try:
        with open(rex_json_path, "r") as f:
            meta = json.load(f)
    except json.JSONDecodeError as e:
        error(f"[{pkg_name}] Invalid JSON in rex.json: {e}")
        return

    # 3. Required fields
    for field in ("name", "version", "description", "language"):
        if field not in meta:
            error(f"[{pkg_name}] Missing required field '{field}' in rex.json")

    # 4. Name matches directory
    if meta.get("name") != pkg_name:
        error(
            f"[{pkg_name}] Package name '{meta.get('name')}' does not match directory name"
        )

    # 5. Name format
    if not NAME_RE.match(meta.get("name", "")):
        error(f"[{pkg_name}] Invalid package name format (must be lowercase, a-z0-9-)")

    # 6. Language is cpp
    if meta.get("language") != "cpp":
        error(f"[{pkg_name}] Language must be 'cpp', got '{meta.get('language')}'")

    # 7. Semver
    version = meta.get("version", "")
    if not SEMVER_RE.match(version):
        error(f"[{pkg_name}] Invalid version format '{version}' (expected MAJOR.MINOR.PATCH)")

    # 8. include/ with headers (recursive search)
    include_dir_name = meta.get("include", "include")
    include_dir = os.path.join(pkg_dir, include_dir_name)
    if not os.path.isdir(include_dir):
        error(f"[{pkg_name}] Missing '{include_dir_name}/' directory")
    else:
        headers = []
        for root, _dirs, files in os.walk(include_dir):
            headers.extend(f for f in files if f.endswith(".h") or f.endswith(".hpp"))
        if not headers:
            error(f"[{pkg_name}] No header files (.h/.hpp) found in '{include_dir_name}/'")

    # 9. src/ with sources (recursive search)
    src_dir = os.path.join(pkg_dir, "src")
    if not os.path.isdir(src_dir):
        error(f"[{pkg_name}] Missing 'src/' directory")
    else:
        sources = []
        for root, _dirs, files in os.walk(src_dir):
            sources.extend(f for f in files if f.endswith(".cpp") or f.endswith(".c"))
        if not sources:
            error(f"[{pkg_name}] No source files (.cpp/.c) found in 'src/'")

    # 10. Dependencies reference existing packages
    deps = meta.get("dependencies", {})
    if not isinstance(deps, dict):
        error(f"[{pkg_name}] 'dependencies' must be an object")
    else:
        for dep_name, dep_ver in deps.items():
            dep_path = os.path.join(PACKAGES_DIR, dep_name)
            if not os.path.isdir(dep_path):
                error(
                    f"[{pkg_name}] Dependency '{dep_name}' not found in packages/"
                )
            if not SEMVER_RE.match(dep_ver):
                error(
                    f"[{pkg_name}] Dependency '{dep_name}' has invalid version '{dep_ver}'"
                )

    print(f"  Done: {pkg_name}")
    return meta


def validate_registry():
    print("Validating registry.json")

    if not os.path.isfile(REGISTRY_PATH):
        error("Missing registry.json at repository root")
        return

    try:
        with open(REGISTRY_PATH, "r") as f:
            registry = json.load(f)
    except json.JSONDecodeError as e:
        error(f"Invalid JSON in registry.json: {e}")
        return

    if "packages" not in registry:
        error("registry.json missing 'packages' array")
        return

    # Collect on-disk packages
    on_disk = set()
    if os.path.isdir(PACKAGES_DIR):
        on_disk = {
            d
            for d in os.listdir(PACKAGES_DIR)
            if os.path.isdir(os.path.join(PACKAGES_DIR, d))
        }

    registry_names = set()
    for entry in registry["packages"]:
        name = entry.get("name", "")
        registry_names.add(name)
        if name not in on_disk:
            error(f"registry.json lists '{name}' but no matching directory in packages/")

    for pkg in on_disk:
        if pkg not in registry_names:
            error(f"Package '{pkg}' exists on disk but is not listed in registry.json")

    print("  Done: registry.json")


def main():
    print(f"Repository root: {REPO_ROOT}")
    print(f"Packages dir:    {PACKAGES_DIR}")
    print()

    # Validate each package
    if os.path.isdir(PACKAGES_DIR):
        for entry in sorted(os.listdir(PACKAGES_DIR)):
            pkg_path = os.path.join(PACKAGES_DIR, entry)
            if os.path.isdir(pkg_path):
                validate_package(pkg_path)
                print()
    else:
        print("No packages/ directory found (empty registry).")
        print()

    # Validate registry
    validate_registry()
    print()

    # Summary
    if errors:
        print(f"Validation FAILED with {len(errors)} error(s):")
        for e in errors:
            print(f"  - {e}")
        sys.exit(1)
    else:
        print("All packages validated successfully.")
        sys.exit(0)


if __name__ == "__main__":
    main()
