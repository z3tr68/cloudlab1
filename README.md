# AWS Cloud Penetration Testing Lab

**AWS EC2 | Ubuntu Linux | Docker | Burp Suite | Nmap | Nuclei | OWASP Juice Shop**

## Project Overview

A hands-on cybersecurity lab designed to simulate a penetration testing engagement against intentionally vulnerable infrastructure hosted on Amazon Web Services (AWS).

The project covers cloud infrastructure deployment, network reconnaissance, automated vulnerability assessment, manual exploitation, Linux privilege escalation, and remediation verification.

Testing was performed against OWASP Juice Shop and a custom Ubuntu Docker container configured with an intentional privilege-escalation vulnerability.

## Lab Architecture

```text
Windows Workstation
│
├── Nmap — Network Reconnaissance
├── Nuclei — Vulnerability Scanning
├── Burp Suite — Web Application Testing
│
└── SSH / SSH Tunnel
    │
    ▼
AWS EC2 — Ubuntu Linux
│
├── Docker Container: OWASP Juice Shop
│   ├── Authentication Testing
│   ├── SQL Injection
│   └── File Access Vulnerabilities
│
└── Docker Container: Privilege Escalation Lab
    ├── Ubuntu 24.04
    ├── Unprivileged User: trainee
    ├── SUID Maintenance Utility
    └── Vulnerable / Remediated Configurations
```

The lab used AWS security groups to control inbound traffic and SSH tunneling to access application services.

## Tools and Technologies

| Tool | Purpose |
|---|---|
| AWS EC2 | Cloud infrastructure hosting |
| Ubuntu Linux | Host and container operating systems |
| Docker | Deployment of isolated testing environments |
| Nmap | Network reconnaissance and service identification |
| Nuclei | Automated vulnerability assessment |
| Burp Suite | HTTP interception, request manipulation, and exploitation |
| OWASP Juice Shop | Intentionally vulnerable web application |
| PowerShell / Bash | System administration and security testing |
| Git / GitHub | Version control and technical documentation |

## Methodology

### 1. Infrastructure Deployment

- Provisioned an Ubuntu EC2 instance.
- Configured SSH connectivity and security group rules.
- Deployed OWASP Juice Shop using Docker.
- Established SSH tunneling for application testing.

### 2. Network Reconnaissance

- Performed port scanning and service identification using Nmap.
- Identified externally accessible SSH services.
- Investigated application services through an SSH tunnel.

### 3. Automated Vulnerability Assessment

Executed Nuclei against OWASP Juice Shop.

**Scan results:**
- 6,749 templates loaded
- 20 matches reported
- Approximately 16-minute scan duration

Results included application fingerprinting, missing security headers, exposed API documentation, and discoverable application paths.

Automated findings were used to guide further manual investigation.

### 4. Manual Web Application Exploitation

Used Burp Suite and HTTP request analysis to investigate and validate vulnerabilities in OWASP Juice Shop.

**Confirmed findings:**

| ID | Vulnerability | Result |
|---|---|---|
| 001 | Unauthenticated Sensitive File Disclosure | Retrieved confidential document |
| 002 | File Access Restriction Bypass | Accessed restricted backup file |
| 003 | SQL Injection Authentication Bypass | Authenticated as administrator without valid credentials |

SQL injection testing demonstrated that manipulated authentication input could cause the application to issue an administrator-associated JWT, which was subsequently used to access authenticated API endpoints.

### 5. Linux Privilege Escalation

Built a custom Ubuntu Docker container containing a deliberately vulnerable maintenance workflow.

The vulnerability involved:

- A root-owned SUID executable.
- A maintenance script stored in a directory controlled by an unprivileged user.
- Insufficient protection of the privileged execution path.

Starting as `trainee` (UID 1001), replaced the maintenance script and demonstrated execution with **effective UID 0 (root)** inside the container.

### 6. Remediation and Verification

Remediated the privilege-escalation vulnerability by:

- Changing maintenance directory ownership to root.
- Removing unnecessary SUID permissions.
- Rebuilding the container.
- Verifying that unauthorized file creation was denied.
- Confirming that the maintenance utility no longer executed with elevated privileges.

The exercise demonstrated the full process of vulnerability identification, exploitation, remediation, and verification.

## Reproducing the Privilege-Escalation Lab

The repository contains both vulnerable and remediated Docker configurations.

**Prerequisites:** Docker installed on a Linux environment. Use only an isolated, disposable lab system.

Navigate to the lab directory:

```bash
cd privilege-escalation
```

### Build the vulnerable image

```bash
docker build -f Dockerfile.vulnerable -t privesc-lab:vulnerable .
```

Launch the container:

```bash
docker run --rm -it \
  --network none \
  --cap-drop ALL \
  --security-opt no-new-privileges:false \
  privesc-lab:vulnerable
```

### Build the remediated image

```bash
docker build -f Dockerfile.remediated -t privesc-lab:remediated .
```

Launch the remediated container:

```bash
docker run --rm -it \
  --network none \
  --cap-drop ALL \
  --security-opt no-new-privileges \
  privesc-lab:remediated
```

The vulnerable configuration intentionally permits a privilege transition inside the container. Do not run it with `--privileged`, mount host directories, or expose the Docker socket.

The exercise demonstrates effective root privileges inside a container, not root access to the underlying EC2 host.

## Project Documentation

- [Vulnerability Assessment Findings](vulnerability-assessment/findings.md) — Technical findings, evidence, impact, and remediation recommendations.
- [Final Security Assessment Report](reports/final-assessment.md) — Executive summary, methodology, results, and lessons learned.
- [Vulnerable Dockerfile](privilege-escalation/Dockerfile.vulnerable) — Original insecure configuration.
- [Remediated Dockerfile](privilege-escalation/Dockerfile.remediated) — Corrected permissions and privilege settings.
- [Maintenance Runner Source](privilege-escalation/maintenance-runner.c) — Source code for the custom maintenance utility.

## Key Takeaways

- Gained practical experience deploying and securing cloud-hosted lab infrastructure.
- Used automated reconnaissance to guide manual vulnerability investigation.
- Demonstrated SQL injection leading to administrator authentication bypass.
- Validated unauthorized file disclosure and file-access restriction bypass.
- Exploited insecure Linux permissions to achieve effective root privileges inside a container.
- Implemented and verified remediation using least-privilege principles.
- Documented findings using a structured penetration testing methodology.

## Scope and Disclaimer

All testing was performed against intentionally vulnerable applications and controlled lab infrastructure for educational purposes.

The privilege-escalation exercise was performed inside an isolated Docker container. No container escape or EC2 host compromise was demonstrated.

The vulnerable configuration is provided solely for security training and should never be deployed in a production environment.