#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct letter {
    letter* ptr0 = nullptr;
    letter* ptr1 = nullptr;
    char ch;
    int cnt;
};

void getLetter(char ch, letter* ptr, string* code, string t = "")
{
    if (ptr != nullptr) {
        if (ch == ptr->ch) {
            *code = t;
        }
            
        if (ptr->ptr0 != nullptr && ptr->ptr1 != nullptr) {
            getLetter(ch, ptr->ptr0, code, t + '0');
            getLetter(ch, ptr->ptr1, code, t + '1');
        }
    }
}

int getMinIndex(vector<letter>* ar)
{
    int res_ind;
    int value = 10000;
    int len = ar->size();
    for (int i = 0; i < len; ++i) {
        if ((*ar)[i].cnt < value) {
            value = (*ar)[i].cnt;
            res_ind = i;
        }
    }
    return res_ind;
}

void remove(int index, vector<letter>* ar)
{
    int len = ar->size();
    for (int i = index; i < len-1; ++i)
        (*ar)[i] = (*ar)[i+1];
    ar->pop_back();
}

void codeHaffmana(vector<letter>* ar)
{
    while (ar->size() != 1) {
        auto* i = new letter [sizeof(letter)];
        auto* j = new letter [sizeof(letter)];
        auto* k = new letter [sizeof(letter)];
        

        int iInd = getMinIndex(ar);
        memcpy(i, &((*ar)[iInd]), sizeof(letter));
        remove(iInd, ar);

        int jInd = getMinIndex(ar);
        memcpy(j, &((*ar)[jInd]), sizeof(letter));
        remove(jInd, ar);

        k->ptr0 = i;
        k->ptr1 = j;
        k->ch = ' ';
        k->cnt = i->cnt + j->cnt;
        ar->push_back(*k);
    }
}



int main(void)
{
    /*
    input:
    >> "string"

    output:
    >> "count of encoding letter" "count of bits for encoding string"
    >> "letter": "code"
    >> ...
    
    */
    string s, result;
    cin >> s; cin.ignore();
    vector<letter> tree;
    int lenS = s.size();

    for (int i = 0; i < lenS; ++i) {
        bool existInArr = false;
        int len = tree.size();
        for (int j = 0; j < len; ++j) {
            if (s[i] == tree[j].ch) {
                existInArr = true;
                tree[j].cnt += 1;
                break;
            }
                
        }
        if (!existInArr) {
            letter newLetter {nullptr, nullptr, s[i], 1};
            tree.push_back(newLetter);
        }
    }

    vector<char> arr;
    for (int i = 0; i < tree.size(); ++i)
        arr.push_back(tree[i].ch);

    codeHaffmana(&tree);

    for (int i = 0; i < lenS; ++i) {
        string code;
        if (tree[0].ptr0 == nullptr && tree[0].ptr1 == nullptr) 
            getLetter(s[i], &tree[0], &code, "0");

        else
            getLetter(s[i], &tree[0], &code);
            
        result += code;
    }

    cout << arr.size() << ' ' << result.size() << endl;

    for (int i = 0; i < arr.size(); ++i) {
        string code;
        if (tree[0].ptr0 == nullptr && tree[0].ptr1 == nullptr) 
            getLetter(arr[i], &tree[0], &code, "0");
        else
            getLetter(arr[i], &tree[0], &code);
        cout << arr[i] << ": " << code << endl;
    }

    cout << result << endl;

    return 0;
}