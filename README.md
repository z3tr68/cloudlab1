# AWS Cloud Penetration Testing Lab

## Overview
Hands-on cybersecurity project focused on cloud infrastructure security, network reconnaissance, vulnerability assessment, and controlled penetration testing using AWS EC2.

## Technologies
- **Cloud:** AWS EC2, Ubuntu Linux
- **Application:** OWASP Juice Shop, Docker
- **Security Tools:** Nmap, Nuclei
- **Development:** PowerShell, Git, GitHub

## Project Objectives
1. Deploy and secure an AWS-hosted penetration testing environment.
2. Identify exposed services through network reconnaissance.
3. Perform automated vulnerability assessments.
4. Manually validate security weaknesses.
5. Demonstrate controlled exploitation and Linux privilege escalation.
6. Document findings, remediation strategies, and lessons learned.

## Progress
- [x] Deploy Ubuntu EC2 instance
- [x] Configure SSH access and AWS security groups
- [x] Deploy OWASP Juice Shop using Docker
- [x] Perform network reconnaissance using Nmap
- [x] Complete Nuclei vulnerability scan
- [ ] Validate identified vulnerabilities
- [ ] Perform controlled exploitation
- [ ] Demonstrate Linux privilege escalation
- [ ] Document remediation and final findings

## Initial Findings
- SSH identified as the only externally reachable service among four tested ports.
- Nuclei completed an assessment using 6,749 templates and returned 20 informational matches.
- Unauthenticated directory listing identified at `/ftp/` in OWASP Juice Shop.

## Disclaimer
All security testing is conducted against intentionally vulnerable infrastructure owned and controlled by the project author for educational purposes.