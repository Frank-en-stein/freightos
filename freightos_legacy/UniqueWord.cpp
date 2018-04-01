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

Queue<string> q;

void read(int num_files) {
    for(int i=0; i<num_files; i++) {
        if(q.size()>=4000) this_thread::sleep_for (std::chrono::seconds(1));
        char filename[20];
        sprintf(filename, "sample/textfile%d.txt", i);

        ifstream infile;
        infile.open(filename);


        stringstream buff;
        buff<<infile.rdbuf();
        q.push(buff.str());
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for(int i=0; i<ALPHABET_SIZE; i++) temp[i] = NULL;

    int num_files = 100000;
    struct TrieNode *root = getNode();

    std::clock_t start;
    double duration;
    long long ii = 178956970;
    start = std::clock();

    std::thread readerThread(read, num_files);

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"file read: "<< duration <<'\n';
    //start = std::clock();
    for(int i=0; i<num_files; i+=2) {
        std::thread insertThread1(insert_line, root, q.pop());
        insertThread1.join();
        //cout<<i<<endl;
    }

    readerThread.join();

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"process: "<< duration <<'\n';
    cout<<"unique words: "<<trie_words<<endl;


    return 0;
}
