// LR6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>

using namespace std;

struct Node
{
	int d;
	Node* father;
	Node* left;
	Node* right;
	Node()
	{
		father = right = left = NULL;
	}
};

Node* root = NULL;

void insertBTS(Node*& root, int val)
{
	Node* z = new Node;
	z->d = val;
	if (root == NULL)
	{
		root = z;
		return;
	}
	Node* y = NULL;
	Node* x = root;
	while (x)
	{
		y = x;
		if (z->d < x->d)
			x = x->left;
		else
			x = x->right;
	}
	z->father = y;
	if (y->d > z->d)
		y->left = z;
	else
		y->right = z;
}

void preorderedTree(Node* root) //прямой
{
	if (root == NULL)
		return;
	else
	{
		cout << root->d << " ";
		preorderedTree(root->left);
		preorderedTree(root->right);
	}
}

void inorderTree(Node* root) //симметричный
{
	if (root == NULL)
		return;
	else
	{
		inorderTree(root->left);
		cout << root->d << " ";
		inorderTree(root->right);
	}
}

void postorderTree(Node* root) //обратный
{
	if (root == NULL)
		return;
	else
	{
		postorderTree(root->left);
		postorderTree(root->right);
		cout << root->d << " ";
	}
}

Node* searchBTS(Node* p, int key)
{
	if (p == 0 || p->d == key)
		return p;
	if (key < p->d)
		return searchBTS(p->left, key);
	else
		return searchBTS(p->right, key);
}

Node* iterative_search(Node* p, int key)
{
	while (p != 0 && key != p->d)
	{
		if (key < p->d)
			p = p->left;
		else
			p = p->right;
	}
	return p;
}

Node* minBTS(Node* p)
{
	while (p->left != 0)
		p = p->left;
	return p;
}

Node* maxBTS(Node* p)
{
	while (p->right != 0)
		p = p->right;
	return p;
}

Node* succBTS(Node* p)
{
	if (p->right)
		return minBTS(p->right);
	Node* y = p->father;
	while (y != 0 && p == y->right)
	{
		p = y;
		y = y->father;
	}
	return y;
}

Node* predBST(Node* p)
{
	if (p->left)
		return maxBTS(p->left);
	Node* y = p->father;
	while (y != 0 && p == y->left)
	{
		p = y;
		y = y->father;
	}
	return y;
}

void deleteBTS(Node*& root, Node* p)
{
	Node* x = NULL;
	Node* y = NULL;
	if (root && p)
	{
		if (p->left == 0 || p->right == 0)
			y = p;
		else
			y = succBTS(p);

		if (y->left)
			x = y->left;
		else
			x = y->right;

		if (x)
			x->father = y->father;

		if (y->father == 0)
			root = x;
		else
		{
			if (y == y->father->left)
				y->father->left = x;
			else
				y->father->right = x;
			if (y != p)
				p->d = y->d;
			delete y;
		}
	}
}

void clear(Node*& root)
{
	if (root)
	{
		clear(root->left);
		clear(root->right);
		free(root);
		root = NULL;
	}
}

bool isEmpty(Node* root)
{
	return root == NULL;
}


//пирамида
const int MaxSize = 100;
int HeapSize = 0;

struct Heap
{
	int* BinaryHeap[MaxSize];
};

int father(int i)
{
	return(i - 1) / 2;
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

void buidHeap(int h[])
{
	int i = 0, k = 1;
	while (i < HeapSize)
	{
		while ((i < k) && (i < HeapSize))
		{
			cout << h[i] << " ";
			i++;
		}
		cout << endl;
		k = left(k);
	}
}

void pushHeap(int h[], int n)
{
	int i, parent;
	i = HeapSize;
	h[i] = n;
	parent = father(i);
	while (parent >= 0 && i > 0)
	{
		if (h[i] > h[parent])
		{
			int temp = h[i];
			h[i] = h[parent];
			h[parent] = temp;
		}
		i = parent;
		parent = father(i);
	}
	HeapSize++;
}

void input(int h[], int size)
{
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		cin >> k;
		pushHeap(h, k);
	}
}

void heapify(int H[], int i)
{
	int temp;
	int lft = left(i);
	int rght = right(i);
	if (lft < HeapSize)
	{
		if (H[i] < H[lft])
		{
			temp = H[i];
			H[i] = H[lft];
			H[lft] = temp;
			heapify(H, lft);
		}
	}
	if (rght < HeapSize)
	{
		if (H[i] < H[rght])
		{
			temp = H[i];
			H[i] = H[rght];
			H[rght] = temp;
			heapify(H, rght);
		}
	}
}

int popHeap(int h[])
{
	int x;
	x = h[0];
	h[0] = h[HeapSize - 1];
	HeapSize--;
	heapify(h, 0);
	return x;
}

void outHeap(int h[])
{
	int i = 0;
	int k = 1;
	while (i < HeapSize)
	{
		while ((i < k) && (i < HeapSize))
		{
			cout << h[i] << " ";
			i++;
		}
		cout << endl;
		k = left(k);
	}
}

int peekHeap(int h[])
{
	return h[0];
}

void heapSort(int H[])
{
	for (int i = HeapSize / 2 - 1; i >= 0; i--)
		heapify(H, i);

	for (int i = HeapSize - 1; i >= 0; i--)
	{
		swap(H[0], H[i]);
		heapify(H, 0);
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");

	Node* root = NULL;
	insertBTS(root, 1);
	insertBTS(root, 7);
	insertBTS(root, 4);
	insertBTS(root, 10);
	insertBTS(root, 2);
	insertBTS(root, 8);

	cout << "Прямой порядок обхода дерева:" << endl;
	preorderedTree(root);
	cout << endl;

	cout << "Симметричный порядок обхода дерева:" << endl;
	inorderTree(root);
	cout << endl;

	cout << "Обратный порядок обхода дерева:" << endl;
	postorderTree(root);
	cout << endl;

	cout << "Поиск элемента со значением 7: " << searchBTS(root, 7) << endl;
	cout << "Поиск элемента со значением 5: " << iterative_search(root, 5) << endl;

	cout << "Минимальный элемент дерева: " << minBTS(root) << endl;
	cout << "Максимальный элемент дерева: " << maxBTS(root) << endl;

	cout << "Удаление корня дерева: " << endl;
	deleteBTS(root, root);
	preorderedTree(root);
	cout << endl;

	cout << "Адрес следующего по значению после корня элемента: " << succBTS(root) << endl;
	cout << "Адрес предыдущего по значению после корня элемента: " << predBST(root) << endl;

	clear(root);
	if (isEmpty(root))
		cout << "Дерево очищено" << endl;
	cout << endl << endl;


	//пирамида 
	int BinaryHeap[MaxSize];
	int size, k;

	cout << "Введите размер пирамиды: " << endl;
	cin >> size;
	cout << "Введите элементы пирамиды:" << endl;
	input(BinaryHeap, size);

	cout << "Создание пирамиды:" << endl;
	buidHeap(BinaryHeap);

	cout << "Упорядочивание пирамиды:" << endl;
	heapify(BinaryHeap, 0);
	outHeap(BinaryHeap);

	cout << "Добавление элемента со значением 1:" << endl;
	pushHeap(BinaryHeap, 1);
	outHeap(BinaryHeap);

	cout << "Удаление корневого элемента пирамиды со значением " << popHeap(BinaryHeap) << endl;
	outHeap(BinaryHeap);

	cout << "Значение корневого элемента пирамиды = " << peekHeap(BinaryHeap) << endl;

	cout << "Пирамидальная сортировка двоичной кучи: " << endl;
	heapSort(BinaryHeap);
	outHeap(BinaryHeap);
}
