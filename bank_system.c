#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_ACCOUNTS 100
#define MAX_NAME_LENGTH 50
#define ACCOUNTS_FILE "data/accounts.txt"

typedef struct {
    int account_number;
    char name[MAX_NAME_LENGTH];
    float balance;
    char phone[15];
    int is_active;
    char pin[5];   
} Account;

Account accounts[MAX_ACCOUNTS];
int total_accounts = 0;

void display_menu(void);
void create_account(void);
void deposit_money(void);
void withdraw_money(void);
 void check_balance(void);
void display_all_accounts(void);
void delete_account(void);
void load_accounts_from_file(void);
void save_accounts_to_file(void);
int find_account_by_number(int acc_num);
int generate_account_number(void);
 int authenticate_user(int acc_num);
void get_pin_input(char *pin);
void clear_input_buffer(void);

int main() {

    int choice;

    printf("===========================================\n");
    printf("     WELCOME TO  YOUR BANKING SYSTEM      \n");
    printf("===========================================\n\n");

    load_accounts_from_file();

    printf("Have an account? (y/n): ");
    char has_account;
    scanf("%c", &has_account);
    clear_input_buffer();

    if(has_account == 'y' || has_account == 'Y') {
        int acc_num;
        printf("Enter your account number: ");
        if(scanf("%d", &acc_num) != 1) {
            printf("Invalid account number!\n");
            return 1;
        }
        clear_input_buffer();

        if(!authenticate_user(acc_num)) {
            printf("Authentication failed! Exiting...\n");
            return 1;
        }
    } else {
        printf("You need an account to use the banking system. Please create one... :)\n");
        create_account();
    }

    while(1) {
        display_menu();
        printf("Enter your choice: ");

        if(scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch(choice) {
            case 1:
                create_account();
                break;
            case 2:
                deposit_money();
                break;
            case 3:
                withdraw_money();
                break;
            case 4:
                check_balance();
                break;
            case 5:
                display_all_accounts();
                break;
            case 6:
                delete_account();
                break;
            case 7:
                save_accounts_to_file();
                printf("Thank you for using our Banking System!\n");
                printf("All data has been saved successfully.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        system("clear || cls"); //just for wind + linux :)
    }

    return 0;
}

void display_menu(void) {
    printf("\n===========================================\n");
    printf("              BANKING MENU                \n");
    printf("===========================================\n");
    printf("1. Create New Account\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Check Balance\n");
    printf("5. Display All Accounts\n");
    printf("6. Delete Account\n");
    printf("7. Exit\n");
    printf("===========================================\n");
}

void create_account(void) {
    if(total_accounts >= MAX_ACCOUNTS) {
        printf("Error: Maximum account limit reached!\n");
        return;
    }

    Account *new_account = &accounts[total_accounts];

    printf("\n=== CREATE NEW ACCOUNT ===\n");
    new_account->account_number = generate_account_number();

    printf("Enter account holder name: ");
    fgets(new_account->name, MAX_NAME_LENGTH, stdin);
    new_account->name[strcspn(new_account->name, "\n")] = 0;

    printf("Enter phone number: ");
    fgets(new_account->phone, 15, stdin);
    new_account->phone[strcspn(new_account->phone, "\n")] = 0;

    printf("Enter initial deposit amount: $");
    if(scanf("%f", &new_account->balance) != 1 || new_account->balance < 0) {
        printf("Invalid amount! Account creation failed.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Set a 4-digit PIN: ");
    scanf("%4s", new_account->pin);
    clear_input_buffer();

    new_account->is_active = 1;
    total_accounts++;

    printf("\n=== ACCOUNT CREATED SUCCESSFULLY ===\n");
    printf("Account Number: %d\n", new_account->account_number);
    printf("Account Holder: %s\n", new_account->name);
    printf("Phone: %s\n", new_account->phone);
    printf("Initial Balance: $%.2f\n", new_account->balance);
    printf("PIN set successfully!\n");

    save_accounts_to_file();
}

void deposit_money(void) {
    int acc_num;
    float amount;

    printf("\n=== DEPOSIT MONEY ===\n");
    printf("Enter account number: ");
    if(scanf("%d", &acc_num) != 1) {
        printf("Invalid account number!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    int index = find_account_by_number(acc_num);
    if(index == -1) {
        printf("Account not found!\n");
        return;
    }
    if(!accounts[index].is_active) {
        printf("Account is inactive!\n");
        return;
    }

    printf("Current Balance: $%.2f\n", accounts[index].balance);
    printf("Enter deposit amount: $");
    if(scanf("%f", &amount) != 1 || amount <= 0) {
        printf("Invalid amount!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    accounts[index].balance += amount;

    printf("\n=== DEPOSIT SUCCESSFUL ===\n");
    printf("Amount Deposited: $%.2f\n", amount);
    printf("New Balance: $%.2f\n", accounts[index].balance);

    save_accounts_to_file();
}

void withdraw_money(void) {
    int acc_num;
    float amount;

    printf("\n=== WITHDRAW MONEY ===\n");
    printf("Enter account number: ");
    if(scanf("%d", &acc_num) != 1) {
        printf("Invalid account number!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    int index = find_account_by_number(acc_num);
    if(index == -1) {
        printf("Account not found!\n");
        return;
    }
    if(!accounts[index].is_active) {
        printf("Account is inactive!\n");
        return;
    }

    printf("Current Balance: $%.2f\n", accounts[index].balance);
    printf("Enter withdrawal amount: $");
    if(scanf("%f", &amount) != 1 || amount <= 0) {
        printf("Invalid amount!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if(amount > accounts[index].balance) {
        printf("Insufficient balance! Available Balance: $%.2f\n", accounts[index].balance);
        return;
    }

    accounts[index].balance -= amount;

    printf("\n=== WITHDRAWAL SUCCESSFUL ===\n");
    printf("Amount Withdrawn: $%.2f\n", amount);
    printf("Remaining Balance: $%.2f\n", accounts[index].balance);

    save_accounts_to_file();
}

// my blance check
void check_balance(void) {
    int acc_num;

    printf("\n=== CHECK BALANCE ===\n");
    printf("Enter account number: ");
    if(scanf("%d", &acc_num) != 1) {
        printf("Invalid account number!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    int index = find_account_by_number(acc_num);
    if(index == -1) {
        printf("Account not found!\n");
        return;
    }
    if(!accounts[index].is_active) {
        printf("Account is inactive!\n");
        return;
    }

    printf("\n=== ACCOUNT DETAILS ===\n");
    printf("Account Number: %d\n", accounts[index].account_number);
    printf("Account Holder: %s\n", accounts[index].name);
    printf("Phone Number: %s\n", accounts[index].phone);
    printf("Current Balance: $%.2f\n", accounts[index].balance);
}

// accouts disp
void display_all_accounts(void) {
    if(total_accounts == 0) {
        printf("\nNo accounts found!\n");
        return;
    }

    printf("\n=== ALL ACCOUNTS ===\n");
    printf("%-10s %-20s %-15s %-10s %-8s\n",
           "Acc No.", "Name", "Phone", "Balance", "Status");
    printf("-------------------------------------------------------------------\n");

    for(int i = 0; i < total_accounts; i++) {
        if(accounts[i].is_active) {
            printf("%-10d %-20s %-15s $%-9.2f %-8s\n",
                   accounts[i].account_number,
                   accounts[i].name,
                   accounts[i].phone,
                   accounts[i].balance,
                   "Active");
        }
    }
}

void delete_account(void) {
    int acc_num;
    char confirm;

    printf("\n=== DELETE ACCOUNT ===\n");
    printf("Enter account number: ");
    if(scanf("%d", &acc_num) != 1) {
        printf("Invalid account number!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    int index = find_account_by_number(acc_num);
    if(index == -1) {
        printf("Account not found!\n");
        return;
    }
    if(!accounts[index].is_active) {
        printf("Account is already inactive!\n");
        return;
    }

    printf("\nAccount Details:\n");
    printf("Account Number: %d\n", accounts[index].account_number);
    printf("Account Holder: %s\n", accounts[index].name);
    printf("Current Balance: $%.2f\n", accounts[index].balance);

    printf("\nAre you sure you want to delete this account? (y/n): ");
    scanf("%c", &confirm);
    clear_input_buffer();

    if(confirm == 'y' || confirm == 'Y') {
        accounts[index].is_active = 0;
        printf("Account deleted successfully!\n");
        save_accounts_to_file();
    } else {
        printf("Account deletion cancelled.\n");
    }
}

void load_accounts_from_file(void) {
    FILE *file = fopen(ACCOUNTS_FILE, "r");
    if(file == NULL) {
        printf("No existing account data found. Starting fresh.\n");
        return;
    }

    total_accounts = 0;
    while(total_accounts < MAX_ACCOUNTS) {
        Account acc;
        int read = fscanf(file, "%d|%49[^|]|%14[^|]|%f|%d|%4s\n",
                          &acc.account_number,
                          acc.name,
                          acc.phone,
                          &acc.balance,
                          &acc.is_active,
                          acc.pin);
        if(read != 6) break;
        accounts[total_accounts++] = acc;
    }

    fclose(file);
    printf("Loaded %d accounts from file.\n", total_accounts);
}

void save_accounts_to_file(void) {
    FILE *file = fopen(ACCOUNTS_FILE, "w");
    if(file == NULL) {
        printf("Error: Unable to save account data!\n");
        return;
    }

    for(int i = 0; i < total_accounts; i++) {
        fprintf(file, "%d|%s|%s|%.2f|%d|%s\n",
            accounts[i].account_number,
            accounts[i].name,
            accounts[i].phone,
            accounts[i].balance,
            accounts[i].is_active,
            accounts[i].pin);
    }

    fclose(file);
}
int find_account_by_number(int acc_num) {
    for(int i = 0; i < total_accounts; i++) {
        if(accounts[i].account_number == acc_num && accounts[i].is_active) {
            return i;
        }
    }
    return -1;
}

int generate_account_number(void) {
    static int base_number = 10001;
    return base_number + total_accounts;
}

int authenticate_user(int acc_num){
    int index = find_account_by_number(acc_num);
    if(index == -1) {
        printf("Account not found!\n");
        return 0;
    }
    if(!accounts[index].is_active) {
        printf("Account is inactive!\n");
        return 0;
    }

    char pin[5];
    get_pin_input(pin);

    if(strcmp(pin, accounts[index].pin) == 0) {
        printf("Authentication successful!\n");
        return 1;
    } else {
        printf("Invalid PIN!\n");
        return 0;
    }
}

void get_pin_input(char *pin){
    printf("Enter your authentication PIN: ");
    scanf("%4s", pin);
    clear_input_buffer();
}

void clear_input_buffer(void) {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// END OF FILE
// made by med chlihi 