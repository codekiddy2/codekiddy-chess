#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

struct BOOK {
    unsigned char   move_from;
    unsigned char   move_to;
    unsigned char   move_promo;
    unsigned char   priority;
    unsigned int    games;
    unsigned int    won_games;
    unsigned int    lost_games;
    unsigned int    hz;
    int             first_child;
    int             next_sibling;
}   *book;

FILE           *ft;
int             linelength = 0;

void            print_head()
{
    fprintf(ft, "*\n\n");
    fprintf(ft, "[Event \"?\"]\n");
    fprintf(ft, "[Site \"?\"]\n");
    fprintf(ft, "[Date \"????.??.??\"]\n");
    fprintf(ft, "[Round \"?\"]\n");
    fprintf(ft, "[Result \"*\"]\n");
    fprintf(ft, "[White \"?\"]\n");
    fprintf(ft, "[Black \"?\"]\n\n");
}

void print_move(unsigned char move_from, unsigned char move_to, unsigned char move_promo, int ply)
{
    if ((move_from >> 3) + 1 == 32 && (move_to >> 3) + 1 == 32) return;
    if (linelength > 80) {
        fprintf(ft, "\n");
        linelength = 0;
    }
    if ((ply & 1) == 0) {
        fprintf(ft, "%d.", ply / 2 + 1);
        linelength += 3;
    }
    fprintf(ft, "%c%d%c%d",
            (move_from & 7) + 'a', (move_from >> 3) + 1,
            (move_to & 7) + 'a', (move_to >> 3) + 1);
  
    if (move_promo) {
        static const char prm[] = "RNBQ";
        fprintf(ft, "%c", prm[abs(move_promo)-1]);
    } 
    fprintf(ft, " ");
    linelength += 5;
}

int main(int argc, char *argv[])
{
    int             i,
                    ply;
    size_t          filesize;
    int             node[1000];
    struct MOVE {
        unsigned char   move_from;
        unsigned char   move_to;
        unsigned char   move_promo;
    }   moves[1000];

    if (argc < 2) {
        printf("Simple command-line converter from ABK to PGN\n");
        printf("Usage: abk.exe <abk_file>\n");
        printf("Result PGN-file: out.pgn\n");
        exit(0);
    }
    ft = fopen(argv[1], "rb");
    if (ft == NULL) {
        printf("Can't open file %s\n", argv[1]);
        exit(0);
    }
    filesize = filelength(fileno(ft));
    book = malloc(filesize);
    fread(book, filesize / sizeof(struct BOOK), sizeof(struct BOOK), ft);
    fclose(ft);
    ft = fopen("out.pgn", "w");
    print_head();
    ply = 0;
    node[0] = 900;  // offset to first node in abk-file

    for (;;) {
        print_move(book[node[ply]].move_from, book[node[ply]].move_to,
                   book[node[ply]].move_promo, ply);
        if (book[node[ply]].first_child > 0) {  // current game

            moves[ply].move_from = book[node[ply]].move_from;
            moves[ply].move_to = book[node[ply]].move_to;
            moves[ply].move_promo = book[node[ply]].move_promo;
            node[ply + 1] = book[node[ply]].first_child;
            ply++;
        } else { // new game
            fprintf(ft, "\n");
            node[ply] = book[node[ply]].next_sibling;
            while (node[ply] < 0) {
                ply--;
                if (ply < 0) {
                    fclose(ft);
                    exit(0);
                }
                node[ply] = book[node[ply]].next_sibling;
            }
            print_head();
            linelength = 0;
            for (i = 0; i < ply; i++) {
                print_move(moves[i].move_from, moves[i].move_to, moves[i].move_promo, i);
            }
        }
        if (node[ply] >= filesize / (int) sizeof(struct BOOK)) {
            printf("Error: out of file\n");
            fclose(ft);
            exit(0);
        }
    }
    return 0;
} 
