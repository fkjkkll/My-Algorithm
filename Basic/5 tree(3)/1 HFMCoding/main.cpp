#include <iostream>
#include <string>
#include "MyHeap.h"
using namespace std;
struct Item {
	Item(char a, int b) {
		word = a;
		freq = b;
		left = nullptr;
		right = nullptr;
	}
	Item() {
		word = '-';
		freq = 0;
		left = nullptr;
		right = nullptr;
	}
	char word;
	int freq;
	Item* left;
	Item* right;
	bool operator>(const Item& another) const {
		return this->freq > another.freq;
	}
	bool operator<(const Item& another) const {
		return this->freq < another.freq;
	}
};
void showHFMCode(Item*, string);

int main() {
	Item list[] = { {'a', 10}, {'e', 15}, {'i', 12}, {'s', 3}, {'t', 4}, {'p', 13}, {'l', 1} };
	MyHeap<Item> h(list, sizeof(list)/sizeof(Item));
	while (h.size() > 1) {
		Item* l = new Item();
		Item* r = new Item();
		Item* f = new Item();
		*l = h.pop();
		*r = h.pop();
		f->freq = l->freq + r->freq;
		f->left = l;
		f->right = r;
		h.push(*f);
	}
	Item tree = h.pop();
	showHFMCode(&tree, "");
	return 0;
}

void showHFMCode(Item* HFMTree, string s) {
	if (HFMTree) {
		showHFMCode(HFMTree->left, s+'0');
		showHFMCode(HFMTree->right, s+'1');
		if (HFMTree->word != '-')
			cout << HFMTree->word << ":" << s << endl;
	}
}

