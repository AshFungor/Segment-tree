#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// ДО - дерево отрезков

// задача:
// дан массив, необходимо обработать k запросов. существует два типа запросов:
//  - изменить i элемент на значение a
//  - просуммировать элементы в диапозоне [i;j]
// выполнить с максимальной эффективностью



static vector<int> segment_tree;
static int size;

void set(int i, int a, int l = 0, int r = size - 1, int ind = 1);
int get(int i, int j, int l = 0, int r = size - 1, int ind = 1);
int base_set(const vector<int> *base, int l = 0, int r = size, int ind = 1);

int main(void) {

    cout << "enter array size: ";
    cin >> size;

    vector<int> array(size);
    segment_tree.reserve(size * 4);

    cout << "enter the array (" << size << " elements): ";

    for (int i = 0, a; i < size; ++i) {

        cin >> a;

        array[i] = a;

    }

    base_set(&array);

    cout << "commands: 1 - (i, a) place a at i; 2 - (i, j) get sum of [i;j] segment." << endl;
    cout << "please enter k: ";

    int k, i, j, a;
    char req;
    cin >> k;

    while (k--) {

        cout << "your command: ";

        cin >> req;

        if (req == '1') {

            cout << "enter i nad a: " << endl;

            cin >> i >> a;

            cout << "result is... element set!" << endl;
            set(i - 1, a);


        }

        else if (req == '2') {

            cout << "enter i and j: ";
            cin >> i >> j;


            cout << "result is: " << get(i - 1, j - 1) << endl;


        }

        else {

            cout << "command is unknown, skipping" << endl;
            k++;

        }


    }

    cout << "what kind of beauty a segment tree is!" << endl;

    return 0;
}



int base_set(const vector<int> *base, int l, int r, int ind) {

    if (r - l + 1 > 1) {

        segment_tree[ind] = base_set(base, l, r - (r - l + 1) / 2, ind * 2) + base_set(base, r - (r - l + 1) / 2 + 1, r, ind * 2 + 1);

    }

    else segment_tree[ind] = (*base)[r];

    return segment_tree[ind];


}

int get(int i, int j, int l, int r, int ind)  {

    if (i <= l && j >= r)

        return segment_tree[ind];

    else if (l > j || r < i)

        return 0;

    return get(i, j, l, r - (r - l + 1) / 2, ind * 2) + get(i, j, r - (r - l + 1) / 2 + 1, r, ind * 2 + 1);

}

void set(int i, int a, int l, int r, int ind) {

    if (r - l + 1 > 1) {

        set(i, a, l, r - (r - l + 1) / 2, ind * 2);
        set(i, a, r - (r - l + 1) / 2 + 1, l, ind * 2 + 1);

        segment_tree[ind] = segment_tree[ind * 2] + segment_tree[ind * 2 + 1];

    }

    else if (r == i && l == i) segment_tree[ind] = a;

    return;

}
