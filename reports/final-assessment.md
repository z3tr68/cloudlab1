# AWS Cloud Penetration Testing Lab
## Final Security Assessment Report

**Assessment Type:** Controlled Cloud and Web Application Penetration Testing  
**Platform:** Amazon Web Services (AWS EC2)  
**Operating Systems:** Ubuntu Linux, Windows  
**Applications:** OWASP Juice Shop, Custom Linux Privilege-Escalation Lab  
**Tools:** Nmap, Nuclei, Burp Suite, Docker, PowerShell, Linux CLI  
**Assessment Status:** Completed

---

## 1. Executive Summary

This project involved deploying and assessing an intentionally vulnerable security testing environment hosted on AWS EC2. The objective was to gain practical experience in network reconnaissance, vulnerability discovery, manual exploitation, Linux privilege escalation, and remediation verification.

Testing identified three exploitable web application weaknesses in OWASP Juice Shop and one deliberately introduced Linux privilege-escalation vulnerability in an isolated Docker container.

The most significant web application finding was a SQL injection vulnerability that allowed administrator authentication bypass. Separately, insecure directory permissions combined with a SUID executable allowed an unprivileged container user to execute commands with effective root privileges.

The Linux vulnerability was remediated and successfully retested. Web application vulnerabilities were documented but intentionally retained in Juice Shop for educational purposes.

## 2. Lab Architecture

The environment consisted of an AWS EC2 instance running Ubuntu Linux with Docker containers hosting intentionally vulnerable applications.

### Components

- **AWS EC2:** Cloud infrastructure hosting the lab.
- **Ubuntu Linux:** Host operating system.
- **Docker:** Containerized application deployment and isolation.
- **OWASP Juice Shop:** Intentionally vulnerable web application.
- **Custom privilege-escalation container:** Ubuntu 24.04 environment with an unprivileged user and a deliberately misconfigured maintenance utility.
- **Windows workstation:** Local testing environment using Burp Suite, Nmap, Nuclei, and PowerShell.
- **SSH tunneling:** Provided access to locally bound application services.

Testing was restricted to infrastructure owned and controlled for educational purposes.

## 3. Assessment Methodology

### Phase 1 — Infrastructure Deployment

Provisioned an Ubuntu EC2 instance, configured SSH access, adjusted security group rules, and deployed OWASP Juice Shop using Docker.

### Phase 2 — Network Reconnaissance

Used Nmap to identify reachable services and investigate exposed ports.

The assessment confirmed SSH accessibility, while application services were accessed through an SSH tunnel rather than directly through unrestricted public exposure.

### Phase 3 — Automated Vulnerability Assessment

Executed a Nuclei scan against the Juice Shop application.

**Scan statistics:**

- Templates loaded: 6,749
- Matches reported: 20
- Scan duration: Approximately 16 minutes

The scan identified informational findings, including exposed application endpoints, missing security headers, and accessible API documentation.

These findings informed subsequent manual testing.

### Phase 4 — Manual Web Application Testing

Used Burp Suite Repeater and HTTP requests to investigate application behavior.

Testing included:

- Unauthenticated file-access validation.
- Restricted backup-file access testing.
- SQL injection testing against authentication functionality.
- Administrator identity verification using an issued JWT.

### Phase 5 — Linux Privilege Escalation

Created a disposable Ubuntu Docker container with an unprivileged account named `trainee`.

Introduced an insecure maintenance workflow involving a SUID executable and a script located in a user-controlled directory.

Demonstrated execution with effective UID 0 after replacing the trusted maintenance script.

### Phase 6 — Remediation and Verification

Updated the container configuration to remove unnecessary SUID permissions and secure maintenance directory ownership.

Rebuilt the container and verified that unauthorized file creation was blocked and the maintenance runner no longer executed with elevated privileges.

## 4. Summary of Security Findings

| ID | Vulnerability | Provisional Severity | Status |
|---|---|---|---|
| 001 | Unauthenticated Sensitive File Disclosure | Medium | Confirmed |
| 002 | File Access Restriction Bypass | Medium | Confirmed |
| 003 | SQL Injection Authentication Bypass | High | Confirmed |
| 004 | SUID Privilege Escalation via Insecure Directory Permissions | High | Remediated |

An additional SQL error-disclosure observation was recorded but not fully validated as an exploitable injection vulnerability.

## 5. Remediation Results

The privilege-escalation exercise included a complete remediation cycle.

**Before remediation:**

- Unprivileged user controlled the maintenance directory.
- Root-owned maintenance utility had SUID permissions.
- Attacker-controlled script executed with effective UID 0.

**After remediation:**

- Maintenance directory ownership changed to root.
- SUID permission removed from the executable.
- Unauthorized file creation was denied.
- Maintenance execution no longer produced elevated privileges.

The remediation demonstrated how enforcing least privilege and protecting trusted execution paths can prevent privilege escalation.

## 6. Key Lessons Learned

**Cloud network security:** AWS security groups, public IP connectivity, and SSH tunneling directly affect the accessibility of deployed services.

**Automated scanning limitations:** Nmap and Nuclei provided valuable reconnaissance data, but manual testing was necessary to validate more significant application vulnerabilities.

**Authentication security:** SQL injection in authentication workflows can allow account impersonation without valid credentials.

**Linux permissions:** Root ownership of a file does not guarantee its integrity when an unprivileged user controls the containing directory.

**Privilege boundaries:** Effective root access inside a Docker container is distinct from root access to the underlying EC2 host.

**Remediation verification:** Demonstrating that a security control prevents a previously successful exploit provides stronger evidence than recommending a fix alone.

## 7. Scope and Limitations

This assessment was conducted against intentionally vulnerable applications and deliberately misconfigured environments.

The project did not demonstrate an escape from a Docker container or root access to the underlying AWS EC2 host.

The web application vulnerabilities were not remediated because OWASP Juice Shop is intentionally vulnerable by design.

Severity ratings are preliminary and were not calculated using formal CVSS scoring.

## 8. Conclusion

This project demonstrated a practical penetration testing workflow covering cloud deployment, reconnaissance, automated assessment, manual exploitation, privilege escalation, and remediation validation.

The resulting findings and supporting lab configurations provide reproducible evidence of security testing skills relevant to cybersecurity analyst, security engineering, and penetration testing roles.

---

**Disclaimer:** All exploitation and testing were performed in controlled, intentionally vulnerable lab environments for educational purposes.