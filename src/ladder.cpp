#include <algorithm>
#include "ladder.h"

void error(string word1, string word2, string msg)
{
    cerr << msg << word1 << " " << word2 << endl;
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d)
{
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d)
        return false;

    // for all i and j, a[i,j] will hold the Levenshtein distance between
    // the first i characters of str1 and the first j characters of str2
    vector<vector<int>> a(len1 + 1, vector<int>(len2 + 1));
    // source prefixes can be transformed into empty string by
    // dropping all characters
    for (int i = 0; i <= len1; ++i)
        a[i][0] = i;
    // target prefixes can be reached from empty source prefix
    // by inserting every character
    for (int j = 0; j <= len2; ++j)
        a[0][j] = j;

    for (int j = 1; j <= len2; ++j)
        for (int i = 1; j <= len1; ++i)
        {
            int substitution_cost = 0;
            if (str1[i - 1] != str2[j - 1])
                substitution_cost = 1;

            a[i][j] = min({a[i - 1][j] + 1,                       // deletion
                           a[i][j - 1] + 1,                       // insertion
                           a[i - 1][j - 1] + substitution_cost}); // substitution
        }

    return a[len1][len2] <= d;
}

bool is_adjacent(const string &word1, const string &word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list)
{
    if (begin_word == end_word)
    {
        error(begin_word, end_word, "Error: begin and end words are the same!");
        return vector<string>();
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front(); ladder_queue.pop();
        string last_word = ladder.back();

        for (string word : word_list)
        {
            if (is_adjacent(last_word, word))
                if (visited.find(word) == visited.end())
                {
                    visited.insert(word);
                    vector<string> new_ladder(ladder);
                    new_ladder.push_back(word);

                    if (word == end_word)
                        return new_ladder;

                    ladder_queue.push(new_ladder);
                }
        }
    }

    return vector<string>();
}

void load_words(set<string> &word_list, const string &file_name)
{
    ifstream in(file_name);

    for (string word; (in >> word);)
        word_list.insert(word);

    in.close();
}

void print_word_ladder(const vector<string> &ladder)
{
    if (ladder.empty())
    {
        cout << "No word ladder found." << endl;
        return;
    }
    else
        cout << "Word ladder found: ";

    for (size_t i = 0; i < ladder.size(); ++i)
        cout << ladder[i] << " ";
    cout << endl;
}

#define my_assert(e) { cout << #e << ((e) ? " passed" : " failed") << endl; }
void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
