//
// Created by ASUS on 2/10/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include<conio.h>

#define SIZE 10


struct user {
    char name[10];
    int score;
    char my_board[SIZE][SIZE];
    char opp_board[SIZE][SIZE];
    //struct user *next;
};

struct ships {
    char start[3];
    char end[3];
    int size;
    int tedad_keshti;
    //int id;
    int deleted;
    int kind;//0 for horizontal, 1 for vertical
    struct ships *next;
};

void save_linked_list(struct ships *head_Ship);

void
save_game(struct user *player1, struct user *player2, struct ships *head_ship1, struct ships *head_ship2, int *size1,
          int *size2);

void append_load(struct ships **head_ref, char start[], char end[], int deleted, int kind, int size);

void load_linked_list(struct ships **head_ship);

void load_game(struct user *player1, struct user *player2, struct ships **head_ship1, struct ships **head_ship2, int n);

void delete_ship(struct ships **head_ref, struct ships *ship);

int is_placeable(char start[], char end[], char board[SIZE][SIZE], int j) {

    int row_start = start[0] - 65;
    int col_start = start[1] - 48;

    int row_end = end[0] - 65;
    int col_end = end[1] - 48;

    int lowest_row, highest_row, lowest_col, highest_col;
    if (row_start > row_end) {
        lowest_row = row_end;
        highest_row = row_start;
    } else {
        lowest_row = row_start;
        highest_row = row_end;
    }

    if (col_start > col_end) {
        lowest_col = col_end;
        highest_col = col_start;
    } else {
        lowest_col = col_start;
        highest_col = col_end;
    }

    if (highest_row == lowest_row)
        if (highest_col - lowest_col + 1 != j)
            return 0;
    if (highest_col == lowest_col)
        if (highest_row - lowest_row + 1 != j)
            return 0;


    for (int row = lowest_row - 1; row < highest_row + 1; ++row) {
        if (row == -1)
            row = 0;
        if (row == 10)
            break;

        for (int col = lowest_col - 1; col < highest_col + 1; ++col) {

            if (col == -1)
                col = 0;
            if (col == 10)
                break;
            if (board[row][col] == '*')
                return 0;
        }
    }
    return 1;
}

void type_water(char start[], char end[], char board[SIZE][SIZE]) {

    int row_start = start[0] - 65;
    int col_start = start[1] - 48;

    int row_end = end[0] - 65;
    int col_end = end[1] - 48;

    int lowest_row, highest_row, lowest_col, highest_col;
    if (row_start > row_end) {
        lowest_row = row_end;
        highest_row = row_start;
    } else {
        lowest_row = row_start;
        highest_row = row_end;
    }

    if (col_start > col_end) {
        lowest_col = col_end;
        highest_col = col_start;
    } else {
        lowest_col = col_start;
        highest_col = col_end;
    }

    for (int row = lowest_row - 1; row <= highest_row + 1; ++row) {
        if (row == -1)
            row = 0;
        if (row == 10)
            break;

        for (int col = lowest_col - 1; col <= highest_col + 1; ++col) {

            if (col == -1)
                col = 0;
            if (col == 10)
                break;
            if (board[row][col] == ' ') {
                board[row][col] = 'W';
            }
        }

    }
}

void add_new_user(struct user *new_user) {
    printf("enter your name \n");
    //getchar();
    gets(new_user->name);
    new_user->score = 0;
    /*if (user_exist) {
        printf("user existed before");
        //load_data()
    }
    else {
        FILE *fp = fopen("D:\\Classes\\Mabani\\user.binary", "ab");
        new_user.score = 0;

    }*/
}

void initialize_map(struct user *users) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            users->my_board[i][j] = ' ';
            users->opp_board[i][j] = ' ';
        }
    }

}

void init_user(struct user *users, struct ships **head_ship1);

/*f\
void turn_map(char board[SIZE][SIZE]) {
    printf("   ");
    // row names display
    for (int i = 0; i < SIZE; ++i) {
        printf(" %i ", i);
    }
    printf("\n");

    // board display
    for (int i = 0; i < SIZE; i++) {

        // column names display
        printf(" %c ", i + 65);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);//opp board should print
        }

        printf("\n");
    }

}
*/

void append(struct ships **head_ref, char start[], char end[]) {

    //1.allocate the memory
    struct ships *new_ship = (struct ships *) malloc(sizeof(struct ships));


    //2.pt the data in node and put the next node NULL
    strcpy(new_ship->start, start);
    strcpy(new_ship->end, end);
    new_ship->deleted = 0;

    int row_start = start[0] - 65;
    int col_start = start[1] - 48;

    int row_end = end[0] - 65;
    int col_end = end[1] - 48;

    if (row_start == row_end) {
        new_ship->kind = 0;
        new_ship->size = fabs(col_end - col_start) + 1;
    } else if (col_start == col_end) {
        new_ship->kind = 1;
        new_ship->size = fabs(row_end - row_start) + 1;
    }

    new_ship->next = NULL;

    //3.checking if there is nothing in the list  ar first
    if (*head_ref == NULL) {
        *head_ref = new_ship;
        (*head_ref)->tedad_keshti = 1;
        return;
    }
    (*head_ref)->tedad_keshti++;

    struct ships *curr = *head_ref;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = new_ship;
    return;
}

void put_ships(struct user *player, struct ships **head_ship2, char start[], char end[]) {
    //struct ships *curr = *head_ship2;
    int row_start = start[0] - 65;
    int col_start = start[1] - 48;

    int row_end = end[0] - 65;
    int col_end = end[1] - 48;

/*
    row_start = row_start + 48;
    col_start = col_start + 65;

    row_end = row_end + 48;
    col_end = col_end + 65;
*/
    //int i, j;
    append(head_ship2, start, end);
    /*
    bot->board[row_start - 48][col_start - 65] = '*';
    bot->board[row_end - 48][col_end - 65] = '*';
     */
    if (row_start == row_end) {

        for (int k = col_start; k <= col_end; ++k) {
            player->my_board[row_start][k] = '*';
        }

    } else if (col_start == col_end) {

        for (int k = row_start; k <= row_end; ++k) {
            player->my_board[k][col_start] = '*';

        }
    }
    return;

}

void print_my_map(char board[SIZE][SIZE]) {
    printf("   ");
    // row names display
    for (int i = 0; i < SIZE; ++i) {
        printf(" %i ", i);
    }
    printf("\n");

    // board display
    for (int i = 0; i < SIZE; i++) {

        // column names display
        printf(" %c ", i + 65);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);//opp board should print
        }

        printf("\n");
    }

}

void print_turn_map(char board[SIZE][SIZE]) {
    printf("   ");
    // row names display
    for (int i = 0; i < SIZE; ++i) {
        printf(" %i ", i);
    }
    printf("\n");

    // board display
    for (int i = 0; i < SIZE; i++) {

        // column names display
        printf(" %c ", i + 65);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);//opp board should print
        }

        printf("\n");
    }

}

void show_file() {
    struct user users;
    FILE *fp = fopen("D:\\Classes\\test2.bin", "rb");
    while (!feof(fp)) {
        fread(&users, sizeof(users), 1, fp);
        printf("%s \n", users.name);
        //printf("%d \n", users.score);
        //print_turn_map(users.opp_board);
        //print_my_map(users.my_board);
    }

    fclose(fp);

}

int main_menu() {
    int selected;
    printf("1. play with a friend \n"
           "2. play with a bot \n"
           "3. load game \n"
           "4. load last game \n"
           "5.score board \n"
           "7. exit \n");
    scanf("%d", &selected);
    getchar();
    return selected;

}

void sub_menu_1(struct user *user1, struct user *user2, struct ships **head_ship1, struct ships **head_ship2) {
    int selected;
    int n;
    printf("*** first player *** : \n");
    printf("1. choose user \n"
           "2. put ships \n");
    scanf("%d", &selected);
    getchar();
    switch (selected) {
        case 1:
            printf("1. choose from available users \n"
                   "2. new user \n");
            scanf("%d", &selected);
            getchar();

            switch (selected) {
                case 1:

                    show_file();//just their names
                    printf("enter the student number \n");
                    scanf("%d", &n);
                    getchar();
                    load_game(user1, user2, head_ship1, head_ship2, n - 1);
                    print_my_map(user1->my_board);
                    print_turn_map(user1->opp_board);

                    print_my_map(user2->my_board);
                    print_turn_map(user2->opp_board);
                    break;

                    //choose

                case 2:
                    add_new_user(user1);
                    //initialize_map(user1);
                    //add_new_user();
                    //search
                    // add a new user
                    break;
            }


        case 2:
            init_user(user1, head_ship1);
            //put ships
            break;

    }

    printf("*** second player *** : \n");
    printf("1. choose user \n"
           "2. put ships \n");
    scanf("%d", &selected);
    getchar();
    switch (selected) {
        case 1:
            printf("1. choose from available users \n"
                   "2. new user \n");
            scanf("%d", &selected);
            getchar();

            switch (selected) {
                case 1:
                    //choose
                    show_file();//just their names
                    printf("enter the student number");
                    scanf("%d", &n);
                    getchar();
                    load_game(user1, user2, head_ship1, head_ship2, n - 1);
                    break;

                case 2:
                    add_new_user(user2);
                    //initialize_map(user1);

                    //search
                    // add a new user
                    break;
            }


        case 2:
            init_user(user2, head_ship2);
            //put ships
            break;

    }


}

void user_ships_places(struct user *player, struct ships **head_ship1) {
    char start[3];
    char end[3];
    int j = 5;
    int i;

    for (i = 0; i < 10; ++i) {
        if (i == 1)
            j = 3;
        if (i == 3)
            j = 2;
        if (i == 6)
            j = 1;

        printf("enter the start place of the ship with size = %d : ", j);
        gets(start);
        printf("\n");

        printf("enter the end place of the ship with size = %d : ", j);
        gets(end);
        printf("\n");


        if (is_placeable(start, end, player->my_board, j)) {
            put_ships(player, head_ship1, start, end);
            print_my_map(player->my_board);
        } else {
            printf("error while replacing UNVALID DATA\n");
            j = 5;
            i = -1;

            initialize_map(player);
            print_my_map(player->my_board);
            //user_ships_places(player, head_ship1);
        }


        //printf("error \n");
    }

}

void bot_ships_places(struct user *bot, struct ships **head_ship2) {

    //ships with size = 1
    put_ships(bot, head_ship2, "A6", "A6");
    put_ships(bot, head_ship2, "H3", "H3");
    put_ships(bot, head_ship2, "I1", "I1");
    put_ships(bot, head_ship2, "J5", "J5");

    //ships with size = 2
    put_ships(bot, head_ship2, "A0", "B0");
    put_ships(bot, head_ship2, "F6", "G6");
    put_ships(bot, head_ship2, "H8", "I8");

    //ships with size = 3
    put_ships(bot, head_ship2, "C3", "C5");
    put_ships(bot, head_ship2, "F0", "F2");

    //ships with size = 5
    put_ships(bot, head_ship2, "B9", "F9");

}

bool find_ship(struct ships **head_ship, int ROW, int COL, char turn_board[SIZE][SIZE], struct user *player) {
    struct ships *curr = *head_ship;

    int row_start, col_start, row_end, col_end;

    while (curr != NULL) {

        row_start = curr->start[0] - 65;
        col_start = curr->start[1] - 48;
        row_end = curr->end[0] - 65;
        col_end = curr->end[1] - 48;


        int lowest_row, highest_row, lowest_col, highest_col;


        //horizontal ship
        if (curr->kind == 0) {

            if (col_start > col_end) {
                lowest_col = col_end;
                highest_col = col_start;
            } else {
                lowest_col = col_start;
                highest_col = col_end;
            }
            if ((lowest_col <= COL && highest_col >= COL) && row_start == ROW) {
                curr->deleted++;
            }
            if (curr->size == curr->deleted && lowest_col >= 0 && highest_col <= 9) {
                //update_map;
                if (curr->size == 5)
                    player->score = player->score + 5;
                if (curr->size == 3)
                    player->score = player->score + 8;
                if (curr->size == 2)
                    player->score = player->score + 12;
                if (curr->size == 1)
                    player->score = player->score + 25;


                for (int i = lowest_col; i <= highest_col; ++i) {
                    turn_board[ROW][i] = 'C';
                }
                //delete_ship;
                type_water(curr->start, curr->end, turn_board);
                delete_ship(head_ship, curr);
                return true;

            }

        }
        //vertical ship
        if (curr->kind == 1) {
            if (row_start > row_end) {
                lowest_row = row_end;
                highest_row = row_start;
            } else {
                lowest_row = row_start;
                highest_row = row_end;
            }

            if ((lowest_row <= ROW && highest_row >= ROW) && col_start == COL) {
                curr->deleted++;
            }
            if (curr->size == curr->deleted && lowest_row >= 0 && highest_row <= 9) {
                //update_map;
                for (int i = lowest_row; i <= highest_row; ++i) {
                    turn_board[i][COL] = 'C';
                }
                //delete_ship;
                type_water(curr->start, curr->end, turn_board);
                delete_ship(head_ship, curr);
                return true;

            }
        }


        curr = curr->next;
    }
    return false;

}

void shooting(char turn_board[SIZE][SIZE], char board[SIZE][SIZE], struct ships **head_ship, struct user *player) {
    char s[3];
    printf("enter the cell that you want to shoot :\n");
    gets(s);
    int row = s[0] - 65;
    int col = s[1] - 48;
    if (turn_board[row][col] == ' ') {
        if (board[row][col] == ' ')
            turn_board[row][col] = 'W';
        else if (board[row][col] == '*') {
            if (!find_ship(head_ship, row, col, turn_board, player)) {
                turn_board[row][col] = 'E';
                player->score++;
            }

        }


    }

}

int random_int(int min, int max) {
    return min + rand() % (max + 1 - min);
}

void shooting_bot(char turn_board[SIZE][SIZE], char board[SIZE][SIZE], struct ships **head_ship, struct user *player) {
    //char s[3];
    int row = random_int(0, 9);
    int col = random_int(0, 9);
/*
    int row = row - 65;
    int col = col - 48;
*/
    while (turn_board[row][col] == 'W' || turn_board[row][col] == 'E' || turn_board[row][col] == 'C') {
        row = random_int(0, 9);
        col = random_int(0, 9);
        /*row = row - 65;
        col = col - 48;
*/
    }
    /* row = row - 65;
     col = col - 48;
 */
    if (turn_board[row][col] == ' ') {
        if (board[row][col] == ' ')
            turn_board[row][col] = 'W';
        else if (board[row][col] == '*') {
            if (!find_ship(head_ship, row, col, turn_board, player)) {
                turn_board[row][col] = 'E';
                player->score++;
            }

        }


    }

}

/*
void save_linked_list(struct ships *head_Ship) {
    FILE *fp = fopen("D:\\Classes\\test2.bin", "ab");
    struct ships *curr = head_Ship;
    while (curr != NULL) {
        fwrite(curr->start, sizeof(char), 3, fp);
        fwrite(curr->end, sizeof(char), 3, fp);
        fwrite(&curr->size, sizeof(curr->size), 1, fp);
        fwrite(&curr->deleted, sizeof(curr->deleted), 1, fp);
        fwrite(&curr->kind, sizeof(curr->kind), 1, fp);
        curr = curr->next;
    }

    fclose(fp);

}
*/


void copy_array() {

}


void
save_game(struct user *player1, struct user *player2, struct ships *head_ship1, struct ships *head_ship2, int *size1,
          int *size2) {
    /* char test[50];
     sprintf(test, "D:\\Classes\\%s.bin", "shalgham");
     FILE *fp = fopen(test,"wb");*/
    FILE *fp = fopen("D:\\Classes\\test2.bin", "wb");
    if (fwrite(player1, sizeof(*player1), 1, fp) < 1)
        printf("error");

    //save_linked_list(head_ship1);
    struct ships *curr1 = head_ship1;
    *size1 = sizeof(head_ship1);
    *size2 = sizeof(head_ship2);
    struct ships *curr2 = head_ship2;
    fwrite(player1, sizeof(*player1), 1, fp);

    while (curr1 != NULL) {

        fwrite(curr1->start, sizeof(char), 3, fp);
        fwrite(curr1->end, sizeof(char), 3, fp);
        fwrite(&curr1->size, sizeof(curr1->size), 1, fp);
        fwrite(&curr1->deleted, sizeof(curr1->deleted), 1, fp);
        fwrite(&curr1->kind, sizeof(curr1->kind), 1, fp);
        curr1 = curr1->next;
    }
    fwrite(player2, sizeof(*player2), 1, fp);
    while (curr2 != NULL) {

        fwrite(curr2->start, sizeof(char), 3, fp);
        fwrite(curr2->end, sizeof(char), 3, fp);
        fwrite(&curr2->size, sizeof(curr1->size), 1, fp);
        fwrite(&curr2->deleted, sizeof(curr1->deleted), 1, fp);
        fwrite(&curr2->kind, sizeof(curr1->kind), 1, fp);
        curr2 = curr2->next;
    }
    fclose(fp);
}

//save_linked_list(head_ship2);



void append_load(struct ships **head_ref, char start[], char end[], int deleted, int kind, int size) {
    struct ships *new_ship = (struct ships *) malloc(sizeof(struct ships));


    //2.pt the data in node and put the next node NULL
    strcpy(new_ship->start, start);
    strcpy(new_ship->end, end);
    new_ship->deleted = deleted;

    int row_start = start[0] - 65;
    int col_start = start[1] - 48;

    int row_end = end[0] - 65;
    int col_end = end[1] - 48;

    if (row_start == row_end) {
        new_ship->kind = kind;
        new_ship->size = size;
    } else if (col_start == col_end) {
        new_ship->kind = kind;
        new_ship->size = size;
    }

    new_ship->next = NULL;

    //3.checking if there is nothing in the list  ar first
    if (*head_ref == NULL) {
        *head_ref = new_ship;
        return;
    }

    struct ships *curr = *head_ref;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = new_ship;
    return;
}

/*
void load_linked_list(struct ships **head_ship) {
    //char test[50];

    char start[3];
    char end[3];
    int deleted, size, kind;

    sprintf(test, "D:\\Classes\\%s.bin", "shalgham");
    FILE *fp = fopen(test,"rb");

    FILE *fp = fopen("D:\\Classes\\test2.bin", "rb");
    while (!feof(fp)) {
        fread(start, sizeof(char), 3, fp);
        fread(end, sizeof(char), 3, fp);
        fread(&size, sizeof(size), 1, fp);
        fread(&deleted, sizeof(deleted), 1, fp);
        fread(&kind, sizeof(kind), 1, fp);
        append_load(head_ship, start, end, deleted, kind, size);

    }


    fclose(fp);


}*/

void
load_game(struct user *player1, struct user *player2, struct ships **head_ship1, struct ships **head_ship2, int n) {
    //char test[50];
    //sprintf(test, "D:\\Classes\\%s.bin", "shalgham");
    //FILE *fp = fopen(test,"wb");
    char start[3];
    char end[3];
    int deleted, size, kind;

    FILE *fp = fopen("D:\\Classes\\test2.bin", "rb");
    fseek(fp, sizeof(n), SEEK_SET);
    fread(player1, sizeof(*player1), 1, fp);

    for (int i = 0; i < (*head_ship1)->tedad_keshti; ++i) {

        //load_linked_list(head_ship1);

        fread(start, sizeof(char), 3, fp);
        fread(end, sizeof(char), 3, fp);
        fread(&size, sizeof(size), 1, fp);
        fread(&deleted, sizeof(deleted), 1, fp);
        fread(&kind, sizeof(kind), 1, fp);
        append_load(head_ship1, start, end, deleted, kind, size);
    }
    fread(player2, sizeof(*player2), 1, fp);
    for (int i = 0; i < (*head_ship2)->tedad_keshti; ++i) {

        //load_linked_list(head_ship2);
        fread(start, sizeof(char), 3, fp);
        fread(end, sizeof(char), 3, fp);
        fread(&size, sizeof(size), 1, fp);
        fread(&deleted, sizeof(deleted), 1, fp);
        fread(&kind, sizeof(kind), 1, fp);
        append_load(head_ship2, start, end, deleted, kind, size);
    }

    fclose(fp);

}

void do_turn(struct user *player1, struct user *player2, struct ships **head_ship2, struct ships **head_ship1) {

    print_turn_map(player1->opp_board);
    shooting(player1->opp_board, player2->my_board, head_ship2, player1);
    printf("player_score = %d \n", player1->score);
    print_turn_map(player1->opp_board);
    /* printf("enter 0 to clear the screen \n");
     scanf("%d", &n);
     if (n == 0) {
         system("cls");
     }*/
}

void do_turn_bot(struct user *player1, struct user *player2, struct ships **head_ship) {

    print_turn_map(player1->opp_board);
    shooting_bot(player1->opp_board, player2->my_board, head_ship, player1);
    printf("player_score = %d \n", player1->score);
    print_turn_map(player1->opp_board);

}

void init_bot(struct user *bot, struct ships **head_ship2) {
    strcpy(bot->name, "bot");
    bot->score = 0;
    initialize_map(bot);
    print_my_map(bot->my_board);
    bot_ships_places(bot, head_ship2);
    print_my_map(bot->my_board);


}

void init_user(struct user *users, struct ships **head_ship1) {
    //add_new_user(users);
    initialize_map(users);
    print_my_map(users->my_board);
    user_ships_places(users, head_ship1);
    print_my_map(users->my_board);

}

/*
void zero(struct ships *head_ship) {
    struct ships *curr = head_ship;
    while (curr != NULL) {
        curr->deleted = 0;
        curr = curr->next;

    }

}
*/

//void save_game(struct user *user1, struct user *user2,);

void delete_ship(struct ships **head_ref, struct ships *ship) {
    // Store head node
    struct ships *temp = *head_ref, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp == ship) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp != ship) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL)
        return;

    // Unlink the node from linked list
    prev->next = temp->next;
    temp->tedad_keshti--;
    free(temp); // Free memory
}


void game_loop() {

    int n, size1, size2;
    struct user user1, user2;
    user1.score = 0;
    user2.score = 0;
    struct ships *head_ship1 = NULL, *head_ship2 = NULL;

    //zero(head_ship1);
    //zero(head_ship2);

    int i = 0;
    while (1) {

        switch (main_menu()) {

            case 1:
                //multi_player
                sub_menu_1(&user1, &user2, &head_ship1, &head_ship2);
                while (head_ship1 != NULL || head_ship2 != NULL) {
                    printf("player turn \n");
                    do_turn(&user1, &user2, &head_ship2, &head_ship1);
                    //show_result ();
                    printf("bot turn \n");
                    do_turn_bot(&user2, &user1, &head_ship1);
                    //show_result ();
                }

                break;

            case 2 :
                // play with bot
                init_bot(&user2, &head_ship2);
                add_new_user(&user1);
                init_user(&user1, &head_ship1);
                while (head_ship1 != NULL || head_ship2 != NULL) {
                    printf("player turn \n");
/*
                    int n;
                    printf("press -1 and then enter to save \n");
                    scanf("%d", &n);
                    if (n == -1) {
                        save_game(&user1, &user2, head_ship1, head_ship2);

                    }*/
                    do_turn(&user1, &user2, &head_ship2, &head_ship1);
                    //show_result ();
                    printf("bot turn \n");
                    do_turn_bot(&user2, &user1, &head_ship1);
                    printf("press -1 and then enter to save and any number to continue\n");
                    scanf("%d", &n);
                    getchar();
                    if (n == -1) {
                        save_game(&user1, &user2, head_ship1, head_ship2, &size1, &size2);
                    }
                    //show_result ();
                }
                break;

            case 3:
                //load game
                break;

            case 4:
                //load last game
                break;

            case 6:
                //score board
                break;

            case 7:
                return;


        }

    }

}

int main() {
    setbuf(stdout, 0);
    game_loop();
    return 0;
}
