#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;
long long trie_words = 0;

std::mutex mutex_trie;
std::condition_variable cond_trie;

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

struct TrieNode * temp[ALPHABET_SIZE];

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;

    pNode->isEndOfWord = false;

//    for (int i = 0; i < ALPHABET_SIZE; i++)
//        pNode->children[i] = NULL;
    memcpy(pNode->children, temp, ALPHABET_SIZE * sizeof(struct TrieNode *) );

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insertn(struct TrieNode *root, string key)
{
    std::unique_lock<std::mutex> mlock(mutex_trie);

    struct TrieNode *pCrawl = root;
    int ll  = key.length();

    for (int i = 0; i < ll; i++)
    {
        int index = tolower(key[i]) - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    if(!pCrawl->isEndOfWord) {
        pCrawl->isEndOfWord = true;
        trie_words++;
    }

    mlock.unlock();
    cond_trie.notify_one();
}

void insert_line2(struct TrieNode *root, Queue<string>& q, bool& file_left)
{
    while(file_left) {
        string key = q.pop();

        struct TrieNode *pCrawl = root;
        int ll = key.length();
        bool inserted = false;

        //std::unique_lock<std::mutex> mlock(mutex_trie);
        for(int i=0; i<ll; i++) {
            if(key[i]>='a' && key[i]<='z' || key[i]>='A' && key[i]<='Z') {

                int index = (key[i]>='A' && key[i]<='Z' ? key[i]+32-'a' : key[i]-'a');
                if (pCrawl->children[index] == NULL) {
                    std::unique_lock<std::mutex> mlock(mutex_trie);
                    pCrawl->children[index] = getNode();
                    mlock.unlock();
                    cond_trie.notify_all();
                }

                pCrawl = pCrawl->children[index];
                inserted = true;
            }
            else if(inserted) {
                inserted = false;

                if(!pCrawl->isEndOfWord) {
                    std::unique_lock<std::mutex> mlock(mutex_trie);
                    pCrawl->isEndOfWord = true;
                    trie_words++;
                    mlock.unlock();
                    cond_trie.notify_all();
                }
                pCrawl = root;//cout<<i<<" "<<trie_words<<endl;
            }
        }
        if(inserted) {
            inserted = false;

            if(!pCrawl->isEndOfWord) {
                pCrawl->isEndOfWord = true;
                trie_words++;
            }
            pCrawl = root;//cout<<i<<" "<<trie_words<<endl;
        }

//        mlock.unlock();
//        cond_trie.notify_all();
    }
}

std::mutex mtx;

void insert_line(struct TrieNode *root, int num_files, int idx, int num_threads)
{
    root = getNode();
    do {
        char filename[20];
        ////mtx.lock();
        sprintf(filename, "sample/textfile%d.txt", idx);
        idx+=num_threads;
        //cout<<filename<<endl;
        ifstream infile;
        infile.open(filename);


        stringstream buff;
        buff<<infile.rdbuf();
        ////mtx.unlock();
        ////cond_trie.notify_all();
        string key = buff.str();

        struct TrieNode *pCrawl = root;
        int ll = key.length();
        bool inserted = false;

        //std::unique_lock<std::mutex> mlock(mutex_trie);
        for(int i=0; i<ll; i++) {
            if(key[i]>='a' && key[i]<='z' || key[i]>='A' && key[i]<='Z') {

                int index = (key[i]>='A' && key[i]<='Z' ? key[i]+32-'a' : key[i]-'a');
                if (pCrawl->children[index] == NULL) {
                    /////std::unique_lock<std::mutex> mlock(mutex_trie);
                    pCrawl->children[index] = getNode();
                    /////mlock.unlock();
                    /////cond_trie.notify_all();
                }

                pCrawl = pCrawl->children[index];
                inserted = true;
            }
            else if(inserted) {
                inserted = false;

                if(!pCrawl->isEndOfWord) {
                    //////std::unique_lock<std::mutex> mlock(mutex_trie);
                    pCrawl->isEndOfWord = true;
                    trie_words++;
                    /////mlock.unlock();
                    /////cond_trie.notify_all();
                }
                pCrawl = root;//cout<<i<<" "<<trie_words<<endl;
            }
        }
        if(inserted) {
            inserted = false;

            if(!pCrawl->isEndOfWord) {
                pCrawl->isEndOfWord = true;
                trie_words++;
            }
            pCrawl = root;//cout<<i<<" "<<trie_words<<endl;
        }
    }while(idx<num_files);
}
