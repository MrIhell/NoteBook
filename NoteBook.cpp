

/*


1. Включить новый элемент в конец списка.
2. Включить новый элемент на заданное пользователем место списка.
3. Включить новый элемент после элемента с заданной информационной частью.
4. Включить новый элемент перед элементом с заданной информационной частью.
5. Включить новый элемент в середину списка.
6. Исключить элемент из середины списка.
7. Исключить элемент с заданной информационной частью.
8. Исключить элемент из конца списка.
9. Исключить элемент из заданного пользователем места списка.
10. Исключить элемент из головы списка.

Ежедневник - деловой блокнот

*/


#include<iostream>
#include<string>

using namespace std;

int N_List; // К-во элементов списка

//узел (звено) списка	
struct Node
{
    //Информационный элемент звена списка 
    string Date, Name, Time;
    // Указатель на предыдущее звено списка 
    struct Node* prev;
    // Указатель на следующее звено списка 
    struct Node* next;
};

//внутренний код программы
class List
{
    //корневой узел
    Node* RootNode;
public:
    //конструктор класса без параметров
    List()
    {

        RootNode = NULL;
    }

    //добавление в конец списка
    void AddEnd(string Date, string Name, string Time)
    {
        //создаем новый узел (временный)
        Node* nr = new Node;
        //заносим данные в узел
        nr->Date = Date;
        nr->Name = Name;
        nr->Time = Time;
        //последний указатель из узла устанавливается как NULL
        nr->next = NULL;

        //создаем первый узел
        if (RootNode == NULL)
            RootNode = nr;
        //добовляем узлы
        else
        {
            Node* new_node = RootNode;
            //ищем в цикле предшествующий последнему узел
            while (new_node->next != NULL)
                new_node = new_node->next;

            //предшествующий указывает на последний
            new_node->next = nr;

            //считаем кол-во узлов
            N_List++;
        }
    }

    //добавление в указанное место списка
    void AddLoc(string Date, string Name, string Time, int Pointed_Location)
    {
        
        Node* temp = new Node;
        Node* a = this->RootNode;

        if (Pointed_Location > N_List)
        {
            AddEnd(Date, Name, Time);
            return;
        }
        else if (Pointed_Location == 0)
        {
            temp->Date = a->Date;
            temp->Name = a->Name;
            temp->Time = a->Time;
            a->Date = Date;
            a->Name = Name;
            a->Time = Time;
            temp->next = a->next;
            a->next = temp;
            N_List++;
            return;

        }
        for (int i = 1; i < Pointed_Location /* && a->next */; i++)
            a = a->next;

        //задаем узлу данные
        temp->Date = Date;
        temp->Name = Name;
        temp->Time = Time;
        temp->next = a->next;
        a->next = temp;

        N_List++;
    }

    // Добавление после заданного элемента.
    void AddLocAfter(string DateBef, string NameBef, string TimeBef, string Date, string Name, string Time)
    {
        Node* p = this->RootNode;
        //счетчик, для поиска номера узла в списке
        int Counter = 0;

        if (p != NULL && p->Name == NameBef && p->Date == DateBef && p->Time == TimeBef)
        {
            AddLoc(Date, Name, Time, Counter + 1);
            return;
        }

        while (p != NULL)
        {
            
            if (p != NULL && p->Name == NameBef && p->Date == DateBef && p->Time == TimeBef)
            {
                
                AddLoc(Date, Name, Time, Counter + 1);
                break;
            }
            p = p->next;
            Counter++;

        }
    }

    // Добавление перед заданным элементом.
    void AddLocBefore(string DateAft, string NameAft, string TimeAft, string Date, string Name, string Time)
    {
        Node* p = this->RootNode;

        int Counter = 0;
        if (p != NULL && p->Name == NameAft && p->Date == DateAft && p->Time == TimeAft)
        {
            AddLoc(Date, Name, Time, Counter);
            return;
        }
        while (p != NULL)

        {
            if (p != NULL && p->Name == NameAft && p->Date == DateAft && p->Time == TimeAft)
            {
                AddLoc(Date, Name, Time, Counter);
                break;
            }
            p = p->next;
            Counter++;

        }
    }

    // Добавление в середину списка.
    void AddMiddle(string Date, string Name, string Time)
    {
        Node* p = this->RootNode;

        int Counter = 0;
        while (p != NULL)
        {
            p = p->next;
            Counter++;
        }

        if (Counter <= 1)
        {
            AddEnd(Date, Name, Time);
            return;
        }

        Counter = Counter / 2;
        AddLoc(Date, Name, Time, Counter);
    }

    // Исключение элемента с заданным индексом.
    void RemoveLoc(int position)
    {
        Node* p = this->RootNode;
        int count = 0;
        while (p != NULL)
        {
            p = p->next;
            count++;
        }

        if ((this->RootNode != NULL) && (position < count) && (position >= 0)) // если по этому номеру что-то лежит и этот элемент внутри списка
        {
            Node* temp = this->RootNode;
            Node* helping = this->RootNode;

            for (int i = 0; i < position; i++)
            {
                helping = temp; // предыдущее значение temp
                temp = temp->next;
            }

            if (temp == RootNode) // если элемент который надо удалить первый
                RootNode = temp->next;
            else
                helping->next = temp->next;

            free(temp);
            N_List--; // уменьшаем размер списка
        }
    }

    // Исключение элемента с заданной информационной частью.
    void remove(string Date, string Name, string Time)
    {
        Node* p = this->RootNode;
        int position = 0;

        while (p != NULL)
        {
            if (p != NULL && p->Name == Name && p->Date == Date && p->Time == Time)
                break;
            p = p->next;
            position++;
        }
        RemoveLoc(position);
    }

    // Удаление из середины.
    void RemoveMiddle()
    {
        Node* p = this->RootNode;
        int position = 0;
        while (p != NULL)
        {
            p = p->next;
            position++;
        }

        if (position <= 1)
        {
            RemoveLoc(position);
            return;
        }

        position = position / 2;
        RemoveLoc(position);
    }

    // Исключение элемента из конца списка. 
    void RemoveLast() { RemoveLoc(N_List); }

    // Исключение элемента из начала списка. 
    void RemoveFirst() { RemoveLoc(0); }

    // Вывод списка.
    void PrintList()
    {
        Node* current = RootNode;
        while (current != NULL)
        {
            cout << current->Date << " " << current->Name << " " << current->Time << endl;
            current = current->next;
        }
    }
};

//переодресация
List myList;

//информация выведенная на консоль
void Information()
{
    system("chcp 1251> nul");

    cout << "\nКоманды:\n "
        << "\n0.Список с данными."
        << "\n1.Включить новый элемент в конец списка."
        << "\n2.Включить новый элемент на заданное пользователем место списка."
        << "\n3.Включить новый элемент после элемента с заданной информационной частью."
        << "\n4.Включить новый элемент перед элементом с заданнойинформационной частью."
        << "\n5.Включить новый элемент в середину списка."
        << "\n6.Исключить элемент из середины списка."
        << "\n7.Исключить элемент с заданной информационной частью."
        << "\n8.Исключить элемент из конца списка."
        << "\n9.Исключить элемент из заданного пользователем места списка."
        << "\n10.Исключить элемент из головы списка.\n";

    /*cout << "\n0.List with data."
        << "\n1.Add new element at the end of list."
        << "\n2.Add new element on place of list that user chose."
        << "\n3.Add new element after the element with chosen informational part."
        << "\n4.Add new element before the element with chosen informational part."
        << "\n5.Add new element in the middle of list."
        << "\n6.Delete element from middle of list."
        << "\n7.Delete element with chosen informational part."
        << "\n8.Delete element at the end of list."
        << "\n9.Delete element from the place of list that user chose."
        << "\n10.Delete element from the head of list.\n";*/
}

//заполненный список
void complet()
{
    myList.AddEnd("27.03.23", "Grag", "14:30");
    myList.AddEnd("28.03.23", "Phoenix", "13:00");
    myList.AddEnd("29.03.23", "Savannah", "19:45");
    myList.AddEnd("30.03.23", "Chloe", "16:15");
    myList.AddEnd("31.03.23", "Bob", "10:10");
    myList.AddEnd("1.04.23", "John", "17:20");
    myList.AddEnd("2.04.23", "Rick", "15:00");
    myList.AddEnd("3.04.23", "Morty", "12:45");
    myList.AddEnd("4.04.23", "Kim", "11:45");
    myList.AddEnd("5.04.23", "zdzislaw", "21:45");
}

void List_Editing()
{
    cout << "\nEnter code of cammand: ";
    cout << "\nВведите код команды: ";


    string Entered_Date, Entered_Name, Entered_New_Date, Entered_New_Name, Entered_Time, Entered_New_Time;
    int Entered_Operator, Entered_Place_In_List;
    cin >> Entered_Operator;

    switch (Entered_Operator)
    {
    case 0:
        complet();
        break;

    case 1:
        cout << "\nВведите через пробел дату, имя и время :\n";
        cin >> Entered_Date >> Entered_Name >> Entered_Time;
        myList.AddEnd(Entered_Date, Entered_Name, Entered_Time);
        break;

    case 2:
        cout << "\nВведите через пробел дату, имя и время; а затем через enter место в списке для добавления:\n";
        cin >> Entered_Date >> Entered_Name >> Entered_Time;
        cin >> Entered_Place_In_List;
        myList.AddLoc(Entered_Date, Entered_Name, Entered_Time, Entered_Place_In_List - 1);
        break;

    case 3:
        cout << "\nВведите через пробел дату, имя и время после которых хотите добавить элемент,\nпосле чего нажмите enter и опять через пробел запишите новые данные:\n";
        cin >> Entered_Date >> Entered_Name >> Entered_Time >> Entered_New_Date >> Entered_New_Name >> Entered_New_Time;
        myList.AddLocAfter(Entered_Date, Entered_Name, Entered_Time, Entered_New_Date, Entered_New_Name, Entered_New_Time);
        break;

    case 4:
        cout << "\nВведите через пробел дату, имя и время перед которыми хотите добавить элемент,\nпосле чего нажмите enter и опять через пробел запишите новые данные:\n";
        cin >> Entered_Date >> Entered_Name >> Entered_Time >> Entered_New_Date >> Entered_New_Name >> Entered_New_Time;
        myList.AddLocBefore(Entered_Date, Entered_Name, Entered_Time, Entered_New_Date, Entered_New_Name, Entered_New_Time);
        break;

    case 5:
        cout << "\nВведите через пробел дату, имя и время:\n";
        cin >> Entered_Date >> Entered_Name >> Entered_Time;
        myList.AddMiddle(Entered_Date, Entered_Name, Entered_Time);
        break;

    case 6:
        myList.RemoveMiddle();
        break;

    case 7:
        cout << "\nВведите через пробел дату, имя и время:\n";
        cin >> Entered_Date >> Entered_Name >> Entered_Time;
        myList.remove(Entered_Date, Entered_Name, Entered_Time);
        break;

    case 8:
        myList.RemoveLast();
        break;

    case 9:
        cout << "\nВведите номер объекта в списке: ";
        cin >> Entered_Place_In_List;
        myList.RemoveLoc(Entered_Place_In_List-1);
        break;

    case 10:
        myList.RemoveFirst();
        break;

    default:
        cout << "Ошибка ввода - повторите попытку.\n\n";
        List_Editing();
    }

    cout << endl << "Вывод:\n\n";
    myList.PrintList();
    List_Editing();
}

int main()
{
    system("chcp 1251> nul");

    Information();
    List_Editing();

    return 0;
}

