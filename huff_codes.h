#include<bits/stdc++.h>
using namespace std;
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};
class huff_man{
public:
	string encoded = "";
	string decoded = "";
	vector<pair<char, string> > codes;
	unordered_map<char, string> huffmanCode;
huff_man(string text)
	{
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}
	priority_queue<Node*, vector<Node*>, comp> pq;
	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}
	while (pq.size() != 1)
	{
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}
	Node* root = pq.top();
	encode(root, "", huffmanCode);

	
	for (auto pair: huffmanCode) {
		char a =  pair.first;
		string b = pair.second;
		codes.push_back(make_pair(a,b));
	}

	for (char ch: text) {
		encoded += huffmanCode[ch];
	}
	int index = -1;
	while (index < (int)encoded.size() - 2) {
		decode(root, index, encoded, decoded);
	}
}

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();
	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;
	return node;
}
void encode(Node* root, string str,unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}
	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}
void decode(Node* root, int &index, string str,string &ans)
{
	if (root == nullptr) {
		return;
	}
	if (!root->left && !root->right)
	{
		ans+= root->ch;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->left, index, str, ans);
	else
		decode(root->right, index, str,ans);
}

string get_encoded(string str)
{
	return encoded;
}
vector<pair<char,string> > get_codes(string str)	
{
	return codes;
}
};
