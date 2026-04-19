# Changelog

All notable changes to this project will be documented in this file.

## [1.1.1] - 2026-04-19

### Added

* GitHub Actions CI workflow for x64 Release build validation.
* GitHub Actions release workflow to build and publish a zip on version tags.

### Changed

* Improved compatibility and reliability on modern Windows versions.
* Updated register/uninstall scripts with robust elevation and x64 regsvr32 usage.

### Fixed

* COM site handling and lifecycle edge cases.
* Multiple WinAPI helper memory safety issues.
