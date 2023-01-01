/*

    Multi-threaded chess engine that uses minimax algorithm.

 */

#include "MtEngine.h"

int main() {
    mte::Engine eng;
    printf("Current depth: %d\n", eng.depth);
    // Initial evaluation is 0.00
    double currVal = eng.evaluateBoard(&eng.cr);
    printf("Beginning: %f\n", currVal);

    // Game loop
    while (true) {
        // User inputted move:
        char s[20];
        printf("Enter move: ");
        scanf("%s", s);

        if (!eng.makeMove(s)) {
            // printf("ERROR\n");
            continue;
        }

        // Computer generated move:

        thc::Move mv;
        mv = eng.getBestMove(eng.cr);
        std::string mv_txt = mv.NaturalOut(&eng.cr);
        printf("Computer's move: %s\n", mv_txt.c_str());
        eng.cr.PlayMove(mv);

        //
        eng.display_position(eng.cr, "");
        currVal = eng.evaluateBoard(&eng.cr);
        printf("Eval: %f\n", currVal);
    }

    return 1;
}