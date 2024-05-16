#include <ios>
#include <bitset>
#include <algorithm>

#include "HuffmanTree.h"
#include "Node.h"

HuffmanTree::HuffmanTree() {
	m_root = nullptr;
}

HuffmanTree::HuffmanTree(const std::string& filePath) {
	build(filePath);
}

HuffmanTree::~HuffmanTree() {
	clear();
}

void HuffmanTree::clear()
{
	clear(m_root);
	m_root = nullptr;
}

void HuffmanTree::clear(Node* root)
{
	if (root == nullptr) {
		return;
	}

	clear(root->left());
	clear(root->right());
	delete root;
}

std::string HuffmanTree::stringFromFile(const std::string& fileName) const{
	std::fstream file;
	file.open(fileName.c_str(), std::ios::in|std::ios::binary);
	std::string result;
	while (file) {
		file >> result;
		result += ' ';
	}
	file.close();
	return result;
}


void HuffmanTree::build(const std::string& fileName) {
	if (m_root != nullptr) {
		return;
	}
	std::vector<Node*> list = getList(fileName);

	while (list.size() > 1) { // MAKING TREE
		Node* first = list.back();
		list.pop_back();
		Node* second = list.back();
		list.pop_back();

		Node* summ = new Node();
		symbol temp;
		temp.code = (first->get().code | second->get().code);
		temp.repeat = (first->get().repeat + second->get().repeat);
		summ->set(temp);
		summ->setLeft(first);
		summ->setRight(second);
		list.push_back(summ);
		sort(list);
	}

	m_root = list.back();
	list.pop_back();
	return;
} 

void HuffmanTree::save(const std::string& fileName) {
	return;
}

void HuffmanTree::load(const std::string & fileName) {
	std::fstream file(fileName, std::ios::in);
	if (!file) {
		return;
	}

	if (m_root == nullptr) {
		return;
	}

	_export(file, m_root);

	file.close();
}

void HuffmanTree::_export(std::fstream& file, Node* root) {
	if (!root->left() && !root->right()) {
		BoolVector temp = root->get().code;
		for (int i = 0; i < 256; ++i) {
			if (temp[i] == true) {
				if (i < 33) {
					file << i;
				}
				else {
					file << static_cast<char>(i);
				}
				i = 257;
			}
		}

		file << " | " << root->get().repeat << "\n";
		return;
	}
	if (root->left()) {
		_export(file, root->left());
	}
	if (root->right()) {
		_export(file, root->right());
	}
}

std::string HuffmanTree::binary(unsigned x) const
{
	std::string s;
	do
	{
		s.push_back('0' + (x & 1));
	} while (x >>= 1);
	std::reverse(s.begin(), s.end());
	return s;
}

char HuffmanTree::charFromBool(BoolVector vector) const {
	int code = 0;
	int pow = 1;
	for (int i = 0; i < 8; ++i) {
		code += vector[i] * pow;
		pow *= 2;
	}
	return static_cast<char>(code);
}

 
std::vector<HuffmanTree::Node*> HuffmanTree::getList(const std::string& fileName) const  {
	std::vector<Node*> result;
	std::ifstream text(fileName);
	int* TAB = new int [256];
	for (int i = 0; i < 256; ++i) {
		TAB[i] = 0;
	}

	while (text.good()) {
		char C = text.get();
		TAB[static_cast<int>(C)] += 1;
	}

	for (int i = 0; i < 256; ++i) {
		if (TAB[i] != 0) {
			symbol symbol;
			symbol.repeat = TAB[i];
			symbol.code = BoolVector(256, false);
			symbol.code[i] = true;
			Node* temp = new Node();
			temp->set(symbol);
			result.push_back(temp);
		}
	}
	sort(result);

	return result;
}

void HuffmanTree::sort(std::vector<Node*>& result) const {
	if (result.empty()) {
		return;
	}  for (size_t i = 1; i < result.size(); i++) {
		Node* key = result[i];
		size_t j = i - 1;  
		while (j < result.size()-1 && result[j]->get().repeat < key->get().repeat) {
			result[j + 1] = result[j];
			j--;
		}  
		result[j + 1] = key;
	}

}
