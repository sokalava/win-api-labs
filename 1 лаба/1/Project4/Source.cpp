#include <iostream>

using std::cin;
using std::cout;

struct element {

	int value;
	element* next;
	element* previos;

	element()
	{
		value = 0;
		next = nullptr;
		previos = nullptr;
	}
};

struct Queue
{
	element* start;
	element* last;

	Queue()
	{
		start = new element();
		last = start;
	}

	void addEll()
	{
		int num = 0;
		element* ne = new element();

		while (1)
		{
			cout << "Input value: \n";
			cin >> num;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
				continue;
			}
			ne->value = num;
			break;
		}

		ne->value = num;

		ne->next = nullptr;
		ne->previos = last;
		last->next = ne;

		last = ne;
	}

	void pop()
	{
		if (last == start) return;
		element* e = start->next->next;
		e->previos = start;
		delete start->next;
		start->next = e;
	}

	void clear()
	{
		while (last != start)
		{
			last = last->previos;
			delete last->next;
		}
	}

	void print()
	{
		if (last == start) return;
		element* iterator = start->next;
		do
		{
			std::cout << iterator->value << std::endl;
			iterator = iterator->next;
		} while (iterator);
	}

	void deleteLow()
	{
		if (last == start) return;

		element* iterator = start;
		int lv = iterator->next->value;
		while (iterator->next)
		{
			if (iterator->next->value < lv)
			{
				lv = iterator->next->value;
			}
			iterator = iterator->next;
		}

		iterator = start;
		while (iterator->next)
		{
			if (iterator->next->value == lv)
			{
				if (iterator->next == last) last = iterator;
				element* temp = iterator->next->next ? iterator->next->next : 0;
				if (temp)
					temp->previos = iterator;
				delete iterator->next;
				iterator->next = temp;
			}
			iterator = iterator->next;
			if (!iterator)break;
		}
	}
};



int main()
{
	int n = 0;

	while (1)
	{
		cout << "Input count of queues: \n";
		cin >> n;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			continue;
		}
		break;
	}

	Queue* qs = new Queue[n];

	for (int choose = 0, i = 0; i < n;)
	{
		while (1)
		{
			if (i + 1 < n)
				cout << "1.Add element to queue\n2.Pop queue\n3.Clear queue\n4.Print\n5.Delete low\n6.Previos queue\n0.Next queue\n";
			else
				cout << "1.Add element to queue\n2.Pop queue\n3.Clear queue\n4.Print\n5.Delete low\n6.Previos queue\n0.Exit\n";

			cin >> choose;
			system("cls");

			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
				continue;
			}
			break;
		}

		switch (choose)
		{
		case 0: i++; break;
		case 1: qs[i].addEll(); break;
		case 2: qs[i].pop(); break;
		case 3: qs[i].clear(); break;
		case 4: qs[i].print(); break;
		case 5: qs[i].deleteLow(); break;
		case 6: if (i > 0)i--; break;
		default: continue;
		}
	}
}
