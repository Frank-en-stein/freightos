/*
ID: agileCoder
LANG: C++
*/

#include <bits/stdc++.h>
#include <ctime>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "threaded_queue.cpp"
#include "threaded_trie.cpp"
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for(int i=0; i<ALPHABET_SIZE; i++) temp[i] = NULL;

    int num_files = 100000;
    int num_thread = 16;
    struct TrieNode *root = getNode();

    std::clock_t start;
    double duration;
    start = std::clock();

    std::thread* insertThread[num_thread];
    for(int i=0; i<num_thread; i++) {
        insertThread[i] = new thread(insert_line, root, num_files, i, num_thread);
        //cout<<i<<endl;
    }

    for(int i=0; i<num_thread; i++) insertThread[i]->join();

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"process: "<< duration <<'\n';
    cout<<"unique words: "<<trie_words<<endl;


    return 0;
}
