#include <iostream>
#include <vector>

using namespace std;

struct letter
{
    char ch;
    string code;
};

int main(void)
{
    /*
    input:
    >> "count of encoding letter" "count of bits for encoding string"
    >> "letter": "code"
    >> ...

    output:
    >> "string"
    
    */
    int n, len;
    vector<letter> arr;

    cin >> n >> len; cin.ignore();

    for (int i = 0; i < n; ++i) {
        char let;
        string cd;
        cin.get(let); cin.ignore();
        cin >> cd; cin.ignore();
        arr.push_back({let, cd});
    }

    string let;
    for (int i = 0; i < len; ++i) {
        let += cin.get();
        int cnt = 0, ind;
        for (int j = 0; j < arr.size(); ++j) {
            if (let == arr[j].code) {
                cout << arr[j].ch;
                let = "";
                break;
            }
        }
    }

    return 0;
}