#include <iostream>

using std::cin;
using std::cout;

struct element { // cруктура элемента

	int value; //значение элемента
	element* next; // следующий элемент
	element* previos; // предыдущй элемент

	element() // конструктор по умолчанию для элемента
	{
		value = 0;
		next = nullptr;
		previos = nullptr;
	}
};

struct Stack //структура стэка
{
	element* start;//Точка старта, по сути элемент, но мы его используем просто как точку старта
	element* last; //последний, текущий элемент

	Stack() //конструктор стэка
	{
		start = new element();
		last = start;
	}

	void addEll() // функция добавления нового элемента
	{
		int num = 0;
		element* ne = new element();

		while (1) //проверка ввели ли мы число 
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

		ne->value = num; //линковка сосдених элементов, т.е. связываем их

		ne->next = nullptr;
		ne->previos = last;
		last->next = ne;

		last = ne;
	}

	void addEll(int el) // функция добавления нового элемента
	{
		element* ne = new element();

		ne->value = el; //линковка сосдених элементов, т.е. связываем их

		ne->next = nullptr;
		ne->previos = last;
		last->next = ne;

		last = ne;
	}

	void pop() //функция для удаления элемента, в стэке удаляется всегда верхний элемент
	{
		if (last == start) return;
		last = last->previos;
		delete last->next;
	}

	void clear() //очистка стэка
	{
		while (last != start)
		{
			last = last->previos;
			delete last->next;
		}
	}

	void print() //печать стэка
	{
		if (last == start) return;
		element* iterator = last;
		do
		{
			std::cout << iterator->value << std::endl;
			iterator = iterator->previos;
		} while (iterator != start);
	}

	Stack operator +(Stack& ad) //перегрузка оператора +, для структры стека
	{
		element* it = 0;
		Stack ns = Stack();
		if (start == last)
		{
			it = ad.start->next;
			while (it)
			{
				ns.addEll(it->value);
				it = it->next;
			}
			return ns;
		}
		else if (ad.start == ad.last)
		{
			it = start->next;
			while (it)
			{
				ns.addEll(it->value);
				it = it->next;
			}
			return ns;
		}

		it = ad.start->next;
		while (it)
		{
			ns.addEll(it->value);
			it = it->next;
		}
		it = start->next;
		while (it)
		{
			ns.addEll(it->value);
			it = it->next;
		}
		return ns;
	}
};



int main()
{
	int n = 0;

	while (1)
	{
		cout << "Input count of stacks: \n";
		cin >> n;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			continue;
		}
		break;
	}

	Stack* stacks = new Stack[n];

	for (int choose = 0, i = 0; i < n;)
	{
		while (1)
		{
			if (i + 1 < n)
				cout << "1.Add element to stack\n2.Pop stack\n3.Clear stack\n4.Print\n5.Add stack\n6.Previos stack\n0.Next stack\n";
			else
				cout << "1.Add element to stack\n2.Pop stack\n3.Clear stack\n4.Print\n5.Add stack\n6.Previos stack\n0.Exit\n";

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
		case 0: i++; break; //выходи или переход на лседующий стэк
		case 1: stacks[i].addEll(); break; //добавление
		case 2: stacks[i].pop(); break;//удаление
		case 3: stacks[i].clear(); break;//очищение
		case 4: stacks[i].print(); break;//печать
		case 5:
			if (n < 3) break;
			while (1) //проверка ввели ли мы число 
			{
				cout << "Input ids operating stacks: \n";
				int id1 = n, id2 = n;
				cin >> id1 >> id2;

				if (cin.fail() || id1 < 0 || id2 < 0 ||
					id1 >= n || id2 >= n || id1 == id2 ||
					id1 == i || id2 == i)
				{
					cin.clear();
					cin.ignore();
					continue;
				}
				stacks[i] = stacks[id1] + stacks[id2];
				break;
			}
			break;//удаление самых мелких
		case 6:
			if (i > 0)i--;
			break;
		default: continue;
		}
	}
}
