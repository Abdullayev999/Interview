#include <iostream>
#include <string>

/*
        Задание 1:
        + Реализуйте класс Poll (title: строка, variants: массив вариантов)
        + Реализуйте класс Variant (text: строка, count: количество голосов)
        + Реализуйте оператор вывода для типа Poll который печатает данные
          опроса (заголовок, варианты ответов и количество голосов)
        + При выводе информации пользователь должен выбрать как отобразить
          результаты опроса (количество голосов за каждый вариант или процент
          от общего количества голосов для каждого варианта)
     */

class Poll;

class Variant
{
public:
    void counterUp()
    {
        m_count++;
    }

    int getCount()const
    {
        return m_count;
    }

    void setAnswer(const std::string& data)
    {
        m_answer = data;
    }

    std::string getAnswer()const
    {
        return m_answer;
    }

private:
    friend std::ostream& operator<<(std::ostream& os, Poll& n);
    friend class Poll;
    std::string m_answer;
    size_t m_count = 0;
};


const size_t m_size = 5;

class Poll
{
public:

    int getCount(const int num)
    {
        return m_arr[num].m_count;
    }

    int getSize()const
    {
        return m_size;
    }

    void setQuestion(const std::string& data)
    {
        m_question = data;
    }

    int percent(const int num)const
    {
        int count = 0;

        for (int i = 1; i < m_size; ++i)
            count += m_arr[i].m_count;


        if (count)
            return num * 100 / count;
        else
            return num * 100 / 1;

    }

    std::string getQuestion()const
    {
        return m_question;
    }

    void Counter(const int num)
    {
        m_arr[num].counterUp();
    }

private:
    friend std::istream& operator>>(std::istream& is, Poll& n)
    {
        std::string data;
        std::cout << "Please enter a question : \n";
        std::getline(std::cin, n.m_question);
        std::cout << "\nPlease enter options : \n";
        for (int i = 1; i < m_size; ++i)
        {
            std::getline(std::cin, data);
            n.m_arr[i].setAnswer(data);
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, Poll& n)
    {
        os << "Question : " << n.getQuestion() << '\n' << "Options\n";
        for (int i = 1; i < m_size; ++i)
        {
            os << i << ") " << n.m_arr[i].getAnswer() << "  Voted : (" << n.m_arr[i].getCount()
                << ") Percent : " << n.percent(n.getCount(i)) << " % \n";

        }
        return os;
    }
    friend class Variant;
    std::string m_question;
    Variant m_arr[m_size];
};






int main()
{
    const int ZERO = 0;
    const int ONE = 1;
    const int FIVE = 5;
    Poll poll;
    std::cin >> poll;
    int act;
    system("cls");
    do
    {

        std::cout << "\t\tOnline voting\n0 - Stop voting\nSelect option : \n";
        std::cout << '\n' << poll << '\n';
        std::cin >> act;
        if (act >= ONE && act < FIVE)
        {
            poll.Counter(act);
        }
        else if (act == ZERO)
        {
            system("cls");
            break;
        }
        else
        {
            std::cout << "Wrong choice please repeat\n";
        }
        system("cls");
    } while (act);
    std::cout << "\nVoting stoped ,  result :\n" << poll << '\n';


}