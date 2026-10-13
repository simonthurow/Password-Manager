# Password Manager
Simple local Password Manager written in C++ to easily manage your login data on Windows and macOS.

# Screenshots
Opening File: <br>
<img width="445" height="17" alt="image" src="https://github.com/user-attachments/assets/699a2923-db4a-4c22-a5df-76bde566df52" />

Menu in manager: <br>
<img width="256" height="167" alt="image" src="https://github.com/user-attachments/assets/d4812f2c-3248-4d03-966d-af9576fa10f1" />

List of all accounts ([4]): <br>
<img width="261" height="312" alt="image" src="https://github.com/user-attachments/assets/12ff4d5f-7f4d-47f9-ac11-aa8b8663adae" />

Example input for searching for "net": <br>
<img width="262" height="241" alt="image" src="https://github.com/user-attachments/assets/26b211e2-46e7-4429-9d02-306013abd62e" />

# Tech Stack
Written completely in C++ using some crypto and security libraries.

# Features
- Simple CLI Password Manager
- Multiple Encryption Methods: No encryption, Vigenere, AES(standard)
- Ability to add, delete, search, list and select password
- Password is never shown rather copied directly into Clipboard
- Local file includes encrypted passwords and hashed File Password for safe login

# Installation and Setup
Prerequisites:
- Windows or Mac PC
- OpenSSL installed when on Windows

Installation Guide: <br>
- Simple Makefile execution <code>make</code>

# Usage
Creating a password file:
- <code> ./pm -c filename </code>
- Then asked to set password

Opening password file:
- <code> ./pm filename </code>
- Then asked to type in password for login

Manager Functions:
- Add Account: <code>1</code>, then follow instructions on screen
- Add Account with password generation: <code>2</code>, then follow instructions on screen
- Delete Account: <code>3 AccountID</code>, then follow instructions on screen
- Show List of Accounts: <code>4</code>, shows account id, url, username
- Search for term in URL or username: <code>5 searchTerm</code>, shows accounts where url and/or username include substring
- Select a Password: <code>6 AccountID</code>, password of account with that id copied into clipboard
- Change the master password of the file: <code>7</code>, then follow instructions on screen
- Exit the Password Manager: <code>8</code>, also the step that saves everything done in that session
