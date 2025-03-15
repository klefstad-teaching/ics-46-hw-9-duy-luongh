#include "ladder.h"

int main()
{
    // verify shortest path
    verify_word_ladder();

    // verify correct path
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    print_word_ladder(generate_word_ladder("cat", "dog", word_list));
    cout << endl;
    print_word_ladder(generate_word_ladder("marty", "curls", word_list));
    cout << endl;
    print_word_ladder(generate_word_ladder("sleep", "awake", word_list));
    cout << endl;

    return 0;
}