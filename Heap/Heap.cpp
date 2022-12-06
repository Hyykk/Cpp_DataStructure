// 2020741067 홍윤교 HW5
// VisualStudio 2022

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#define MAX_SIZE 30     // H-tree size

using namespace std;

void rotated_form(const vector<char>& heap, int depth, int i);
void not_rotated_form(const vector<char>& heap);
void init_H_tree();
void get_H_tree(const vector<char>& heap, int index, int depth, int i, int j, int u, int d, int r, int l);
void print_H_tree();
void H_tree_form(const vector<char>& heap);
int center(size_t n);
int depth(size_t n);

char H_tree[MAX_SIZE][MAX_SIZE];    // H-tree

int main(void)
{
    vector<char> heap;
    char inchar;
    make_heap(heap.begin(), heap.end());
    while (1) {
        cin;
        if (cin.peek() == 'I') {
            cin.ignore();
            if (cin.peek() == 'N') {
                cin.ignore();
                if (cin.peek() == 'S') {
                    cin.ignore();
                    // push character at heap
                    cin >> inchar;
                    heap.push_back(inchar);
                    push_heap(heap.begin(), heap.end());
                }
            }
        }
        else if (cin.peek() == 'D') {
            cin.ignore();
            if (cin.peek() == 'E') {
                cin.ignore();
                if (cin.peek() == 'L') {
                    cin.ignore();
                    // delete root character from heap
                    pop_heap(heap.begin(), heap.end());
                }
            }
        }
        else if (cin.peek() == 'E') {
            cin.ignore();
            if (cin.peek() == 'O') {
                cin.ignore();
                if (cin.peek() == 'I') {
                    cin.ignore();
                    // Show 3 forms
                    cout << "1. rotated form" << endl;
                    rotated_form(heap, 0, 0);
                    cout << "2. not-rotated form" << endl;
                    not_rotated_form(heap);
                    cout << "3. H-tree form" << endl;
                    H_tree_form(heap);
                }
            }
        }
        // if wrong input, ignore
        cin.ignore();
    }
    return 0;
}

// index center
int center(size_t n) {
    return n <= 1 ? 0 : 2 * center(n / 4) + 1;
}

//H-tree depth
int depth(size_t n) {
    return n <= 7 ? 1 : 2 * depth(n / 4);
}

// heap -> rotated form
void rotated_form(const vector<char>& heap, int depth, int i) {
    // if no child print you
    // if have child reculsive function(&child)
    assert(!heap.empty());
    if (i < heap.size()) {
        rotated_form(heap, depth + 1, 2 * i + 2);   //left child
        cout.width(depth * 2);
        cout << heap[i] << endl;
        rotated_form(heap, depth + 1, 2 * i + 1);    //right child
    }
}

// heap -> not rotated form
void not_rotated_form(const vector<char>& heap) {
    // iterator index 0-> vec.size()
    // use int depth of b-tree ex) index [0] -> depth 1, index[2],index[3] --> depth 2 => cout.width(pow(2*depth))

    //if index 0
    // if (depth)
    assert(!heap.empty());
    int j = 1;
    // get tree depth
    int depth = 1;
    for (int i = 1; i < heap.size(); i++) {
        if (i == pow(2, depth) - 1) {
            depth++;
        }
    }

    for (int i = 0; i < heap.size(); i++) {
        if (i == 0) {
            cout.width(pow(2, depth));
            cout << heap[0] << endl;
            depth--;
        }
        else if (i == pow(2, j) - 1) {
            cout.width(pow(2, depth));
            cout << heap[i];
        }
        else {
            cout.width(pow(2, depth + 1));
            cout << heap[i];
            if (i == pow(2, j + 1) - 2) {
                cout << endl;
                j++;
                depth--;
            }
        }
    }
    cout << endl;
}

// heap -> H-tree
void get_H_tree(const vector<char>& heap, int index, int depth, int i, int j, int U, int D, int R, int L) {
    assert(!heap.empty());
    if (index >= heap.size()) {
        return;
    }
    int V[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

    H_tree[i][j] = heap[index - 1];

    if (2 * index <= heap.size()) {
        H_tree[i + depth * V[L][1]][j + depth * V[L][0]] = heap[(2 * index) - 1];
        get_H_tree(heap, 4 * index, depth / 2, i + depth * (V[L][0] + V[U][0]), j + depth * (V[L][1] + V[U][1]), D, U, L, R);
        get_H_tree(heap, 4 * index + 1, depth / 2, i + depth * (V[R][0] + V[D][0]), j + depth * (V[L][1] + V[U][1]), U, D, R, L);
    }
    if (2 * index + 1 <= heap.size()) {
        H_tree[i + depth * V[R][1]][j + depth * V[R][0]] = heap[2 * index];
        get_H_tree(heap, 4 * index + 2, depth / 2, i + depth * (V[R][0] + V[D][0]), j + depth * (V[R][1] + V[D][1]), U, D, R, L);
        get_H_tree(heap, 4 * index + 3, depth / 2, i + depth * (V[L][0] + V[U][0]), j + depth * (V[R][1] + V[D][1]), D, U, L, R);
    }
}

// show H-tree
void print_H_tree() {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            cout << H_tree[i][j];
        }
        cout << endl;
    }
}

// feel blank at H-tree
void init_H_tree() {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            H_tree[i][j] = ' ';
        }
    }
}

// do H-tree form
void H_tree_form(const vector<char>& heap) {
    init_H_tree();
    get_H_tree(heap, 1, depth(heap.size()), center(heap.size()), center(heap.size()), 3, 2, 1, 0);
    print_H_tree();
}