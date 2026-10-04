# Password Manager
Simple Password Manager written in C++ to manage your login data on Windows

# Screenshots
Opening File: <br>
<img width="598" height="48" alt="image" src="https://github.com/user-attachments/assets/410baa28-d290-4e26-93ab-571f084baac8" />

Menu in manager: <br>
<img width="300" height="286" alt="image" src="https://github.com/user-attachments/assets/22968b17-c81f-4e14-b6f1-4c57c947190c" />

Example input for searching for "Te": <br>
<img width="302" height="332" alt="image" src="https://github.com/user-attachments/assets/b0fbdc97-611f-4568-baf7-42715a797dd3" /> <br>

# Tech Stack
Written completely in C++, using standard C++, Windows API and OpenSSL library

# Features
- Simple CLI Password Manager
- Multiple Encryption Methods (currently only no encryption or Vigenere)
- Ability to add, delete, search, list and select password
- Password is never shown rather copied directly into Clipboard
- Local file includes encrypted passwords and hashed File Password for safe login

# Installation and Setup
Prerequisites:
- Windows PC
- OpenSSL installed

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
- Delete Account: <code>2 id</code>, then follow instructions on screen
- Show List of Accounts: <code>3</code>, shows account id, url, username
- Search for term in URL oder username: <code>4 searchTerm</code>, shows accounts where url and/or username include substring
- Select a Password: <code>5 id</code>, password of accounts with that id copied into clipboard
- Exit the Password Manager: <code>6</code>, also the step that saves everything done in that session
