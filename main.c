//Stephen Muharsky, smuharsk, 250846203

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//max number of accounts.
#define MAX 9
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

 struct account{
    char account_number[3];
    char type;
    int balance;
    int transaction_limit;
    int transaction_fee;
    int deposit_fee;
    int withdrawal_fee;
    int transfer_fee;
    char overdraft;
    int overdraft_fee;
    int current_number_of_transactions;
};

void* deposit(void* arg){
    char* line = arg;
    printf("thread ID: %d \n",  pthread_self());
    printf("From thread:  %s \n",line);

    //tokenizing the line
    char skip[4];
    char skip2[1];
}

int main() {
    //array containing the accounts
    struct account accounts[MAX];

    int current_accounts = 0;

    //Defining an account.
    FILE *ptr_file;
    char buf[200];

    //Opening input file.
    ptr_file = fopen("input.txt", "r");

    if (ptr_file == NULL) {
        printf("Cannot open file \n");
        exit(0);
    }

    else {
        printf("The input file is now opened. \n");

        while (fgets(buf, 200, ptr_file) != NULL) {
            //printf("%s", buf);
            //if the first character in the line is an 'a' we are creating a new account.
            if (buf[0] == 'a')
            {
                //new account is being created.
                struct account new_account;

                char line_account_number[2];
                //skipping the word 'type'
                char skip1[4];
                char line_type[9];
                char line_transaction_limit[1];
                char line_transaction_fee[3];
                //skipping 'd'
                char skip2[1];
                char line_deposit_fee[3];
                char skip3[1];
                char line_withdrawal_fee[3];
                char skip4[1];
                char line_transfer_fee[3];
                //to skip over the word 'transactions'
                char skip5[12];
                //to skip over the word 'overdraft'
                char skip6[9];
                char line_overdraft[1];
                char line_overdraft_fee[3];
                int balance = 0;


                //Reading all info from line and saving it, creating new account
                //saving account number
                strcpy(line_account_number, (strtok(buf, " ")));
                int account_number_as_int = line_account_number[1] - '0';
                strcpy(new_account.account_number, line_account_number);

                //skipping over the word 'type'
                strcpy(skip1, (strtok(NULL, " ")));

                //saving the account type
                strcpy(line_type, (strtok(NULL, " ")));
                if ((strcmp("business", line_type)) == 0) {
                    new_account.type = 'B';
                } else {
                    new_account.type = 'P';
                }

                //skipping the char 'd'
                strcpy(skip2, (strtok(NULL, " ")));

                //saving deposit fee
                strcpy(line_deposit_fee, (strtok(NULL, " ")));
                int deposit_fee = atoi(line_deposit_fee);
                new_account.deposit_fee = deposit_fee;

                //skipping the char 'w'
                strcpy(skip3, (strtok(NULL, " ")));
                //printf("%s \n", skip3);

                //saving withdrawal fee
                strcpy(line_withdrawal_fee, (strtok(NULL, " ")));
                //printf("%s \n", line_withdrawal_fee);
                int withdrawal_fee = atoi(line_withdrawal_fee);
                new_account.withdrawal_fee = withdrawal_fee;

                //skipping the char 't'
                strcpy(skip4, (strtok(NULL, " ")));
                //printf("%s \n", skip4);

                //saving transfer fee;
                strcpy(line_transfer_fee, (strtok(NULL, " ")));
                //printf("%s \n", line_transfer_fee );
                int transfer_fee = atoi(line_transfer_fee);
                new_account.transfer_fee = transfer_fee;

                //skipping the word 'transactions'
                strcpy(skip5, (strtok(NULL, " ")));
                //printf("%s \n", skip5);

                //saving transaction limit
                strcpy(line_transaction_limit, (strtok(NULL, " ")));
                //printf("%s \n", line_transaction_limit);
                int transaction_limit = atoi(line_transaction_limit);
                new_account.transaction_limit = transaction_limit;

                //saving transaction fee
                strcpy(line_transaction_fee, (strtok(NULL, " ")));
                //printf("%s \n", line_transaction_fee);
                int transaction_fee = atoi(line_transaction_fee);
                new_account.transaction_fee = transaction_fee;

                //skipping the word overdraft
                strcpy(skip6, (strtok(NULL, " ")));
                //printf("%s \n", skip6);

                //saving whether there is overdraft enabled or not
                strcpy(line_overdraft, (strtok(NULL, " ")));
                //printf("%s \n", line_overdraft);
                char overdraft;

                //if overdraft is enabled, overdraft fee is saved.
                int overdraft_fee;
                if ((strcmp("Y", line_overdraft)) == 0) {
                    overdraft = 'Y';
                    new_account.overdraft = 'Y';
                    strcpy(line_overdraft_fee, (strtok(NULL, " ")));
                    overdraft_fee = atoi(line_overdraft_fee);
                    new_account.overdraft_fee = overdraft_fee;
                } else {
                    overdraft = 'N';
                    new_account.overdraft = 'N';
                    overdraft_fee = 0;
                    new_account.overdraft_fee = 0;
                }

                //setting number of transactions.
                new_account.current_number_of_transactions = 0;

                accounts[account_number_as_int] = new_account;
                current_accounts++;
            }

            //depositing.
            if(buf[0] == 'd')
            {
                pthread_t new_thread;
                //printf("from before thread: %s \n", buf );
                pthread_create(&new_thread, NULL, deposit, &buf);
            }
        }

        fclose(ptr_file);
        printf("The file is now closed. \n");
        /*/
        printf("Contents of accounts: \n");
        int x = 1;
        while (x <= current_accounts) {
            printf("New account:%s Type: %c Deposit Fee: %d Withdrawal Fee: %d Transfer Fee: %d Transaction Limit: %d Transaction Fee: %d Overdraft:%c  Overdraft Fee:%d \n",
                   accounts[x].account_number, accounts[x].type, accounts[x].deposit_fee, accounts[x].withdrawal_fee,
                   accounts[x].transfer_fee, accounts[x].transaction_limit, accounts[x].transaction_fee,
                   accounts[x].overdraft, accounts[x].overdraft_fee);
                    x++;}

                    /*/

        return 0;
    }
}
