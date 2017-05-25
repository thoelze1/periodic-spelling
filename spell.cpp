#include <vector>
#include <iostream>

#include <string.h>
#include <stdio.h>

const char *elements[2][104] = { { "B","C","F","H","I","K","N","O","P","S","U","V","W","Y" },
                         { "Ac","Ag","Al","Am","Ar","As","At","Au","Ba","Be","Bh",
                           "Bi","Bk","Br","Ca","Cd","Ce","Cf","Cl","Cm","Cn","Co",
                           "Cr","Cs","Cu","Db","Ds","Dy","Er","Es","Eu","Fe","Fl",
                           "Fm","Fr","Ga","Gd","Ge","He","Hf","Hg","Ho","Hs","In",
                           "Ir","Kr","La","Li","Lr","Lu","Lv","Mc","Md","Mg","Mn",
                           "Mo","Mt","Na","Nb","Nd","Ne","Nh","Ni","No","Np","Og",
                           "Os","Pa","Pb","Pd","Pm","Po","Pr","Pt","Pu","Ra","Rb",
                           "Re","Rf","Rg","Rh","Rn","Ru","Sb","Sc","Se","Sg","Si",
                           "Sm","Sn","Sr","Ta","Tb","Tc","Te","Th","Ti","Tl","Tm",
                           "Ts","Xe","Yb","Zn","Zr"                                }};

int stringCompare(char *a, const char *b, int n) {

    int addA;
    int addB;

    int identical = 1;

    for(int i = 0; i < n; i++) {

        addA = 0;
        addB = 0;

        if((a[i] >= 'A') && (a[i] <= 'Z')) addA = 32;
        if((b[i] >= 'A') && (b[i] <= 'Z')) addB = 32;

        if((a[i] == '\0')||(b[i] == '\0')||((a[i]+addA) != (b[i]+addB))) {
            identical = 0;
            break;
        }

    }

   return identical;

}

void printTable(std::vector< std::vector<int> > &table) {

    for(int i = 0; i < table.size(); i++) {
        for(int j = 0; j < table.size(); j++) {
            if(j < i) {
                std::cout << "  ";
            } else {
                std::cout << " " << table[i][j];
            }
        }
        std::cout << std::endl;
    }

}
int spell(char *word, int wordLength) {

    // Fill dynamic programming table
    std::vector< std::vector<int> > table(wordLength, std::vector<int>(wordLength, 0));
    std::vector< std::vector<int> > best(wordLength, std::vector<int>(wordLength, 0));

    // A subseq that will temporarily store each of the (n+1) choose 2 subsequences 
    char *subseq;

    int currentSum;

    for(int i = 0; i < wordLength; i++) {
        for(int j = i; j < wordLength; j++) {

            // subseq starts at word+j-i and has length i+1
            subseq = word + j - i;

            // printf ("%.*s\n", i+1, subseq);

            if(i == 0) {
                for(int k = 0; k < 14; k++) {
                    if(stringCompare(subseq,elements[i][k],(i+1))==1) {
                         table[i][j] = i+1;
                         break;
                    }
                }
            } else if (i == 1) {
                for(int k = 0; k < 104; k++) {
                    if(stringCompare(subseq,elements[i][k],(i+1))==1) {
                         table[i][j] = i+1;
                         break;
                    }
                }
                // table[i][j] = table[i-1][j-1] + table[i-1][j]; // find subproblems
            }

            if(i > 0) {

                for(int left = 1; left < i+1; left++) {
                    currentSum = table[(left)-1][j-(i+1-left)] + table[(i+1-left)-1][j];
                    if(currentSum > table[i][j]) {
                        table[i][j] = currentSum;
                    }
                }

            }
        }
    }

    printTable(table);

    return table.back().back();
}

int main(int argc, char *argv[]) {

    // A string of characters with a length
    char *word;
    int wordLength;

    // A spelling of the word with elements
    char **elementalWord;
    int lettersReplaced;

    // Get word and spelling
    word = argv[1];
    wordLength = strlen(word);
    lettersReplaced = spell(word, wordLength);

    return 0;
}
