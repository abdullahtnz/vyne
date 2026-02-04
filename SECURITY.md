# Security Policy

## Supported Versions

Since Vyne is currently in active development, only the latest version of the source code is supported with security updates. If you are using an older build, please update to the latest commit to ensure you have the most recent fixes.

| Version | Supported          |
| ------- | ------------------ |
| Main (Latest) | :white_check_mark: |
| < 1.0.0 | :x:                |

## Reporting a Vulnerability

I take the security and stability of the Vyne Interpreter seriously. If you discover a security vulnerability (such as a buffer overflow, memory leak, or a way to escape the VM sandbox), please follow these steps:

### 1. Do Not Open a Public Issue
To protect other users, please do **not** report security vulnerabilities via public GitHub Issues. 

### 2. Private Reporting
Please report any suspected vulnerabilities by contacting the maintainer directly via email:
**4tvnexmgmt@gmail.com**

### 3. What to Include
When reporting, please provide:
* A brief description of the vulnerability.
* A Proof of Concept (PoC) script written in Vyne that demonstrates the crash or exploit.
* Information about your operating system (e.g., Windows 10/11) and your build environment (MinGW/GCC).

### 4. What to Expect
* **Acknowledgement:** I will acknowledge your report within 48–72 hours.
* **Investigation:** I will investigate the cause (checking the VM stack, AST evaluation, and memory management).
* **Fix:** Once a fix is ready, I will push a commit to the main branch and notify you so you can verify the solution.

## Scope
This policy covers the core Vyne VM, the compiler, and official modules like `vglib`, `vcore`, and `vmem`.

---
*Thank you for helping keep the Vyne project secure!*
