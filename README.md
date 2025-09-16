# 🏦 Banking App in C

> *"Because every programmer deserves a bank of their own :)"*

A **command-line banking application** built in **C**, designed to help you practice **file handling, structs, and authentication**.
It’s a small, fun, and educational project for anyone who wants to see how banking operations could work under the hood.

---

## ✨ Features

* ✅ Create accounts with unique account numbers
* 🔒 Set a personal 4-digit PIN for authentication
* 💵 Deposit and withdraw money safely
* 📊 Check balance anytime
* ❌ Delete (deactivate) accounts
* 💾 Persistent storage with file handling (`accounts.txt`)
* 🛡 Optional accounts.dat for those who want compact, binary storage and extra privacy
* 🖥️ Works entirely in the **terminal/console**

---

## 🚀 Why This Project?

This isn’t just another console app. It’s **your playground for learning C**:

* Practice **structs and arrays**
* Understand **file I/O** (save and load account data)
* Implement **simple authentication systems**
* Build a **menu-driven CLI application**

Think of it as your mini “real-world banking system” without the stress of actual money 💸.

---

## 🖐 Getting Started

Clone the repo:

```bash
git clone https://github.com/yourusername/c-banking-app.git
cd c-banking-app
```

Build the project using GCC:

```bash
gcc src/banking.c -o banking
```

Run it:

```bash
./banking
```

Or, if you include the Makefile:

```bash
make run
```

---

## 📂 Project Structure
c-banking-app/
├── src/
│   └── banking.c        
├── data/                
│   ├── accounts.txt     
│   └── accounts.dat     
├── .gitignore           
├── Makefile             
├── README.md            
└── LICENSE              

---

## 💡 Example Usage

```
===========================================
     WELCOME TO SIMPLE BANKING APP
===========================================

Have an account? (y/n): y
Enter your account number: 10001
Enter your PIN: ****
Authentication successful!

=== BANKING MENU ===
1. Create New Account
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. Display All Accounts
6. Delete Account
7. Exit
```

---

## 🔧 Tech Stack

* **Language:** C (C11)
* **Compiler:** GCC
* **Tools:** Terminal / VS Code

---

## 🎨 Fun Fact

Even though this is a console app, it’s a **tiny glimpse of how real banks manage accounts**.
From **unique account numbers** to **secure PINs**, everything you learn here can be a stepping stone for more complex projects.

---

## 📄 License

MIT License – feel free to **study, modify, and share**.

