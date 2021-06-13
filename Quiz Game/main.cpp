#include <bits/stdc++.h>
#define line ("\n")
#include <fstream>
using namespace std;
struct Questions
{
    string question;
    string answer[4];
};
int q_number = 0;
void INPUT(vector<Questions> &,int &);
void INPUT(vector<Questions> &data,int &counter,string);
void Printing (vector<Questions> &,const int);
int score = 0;
int counter = 0;
vector<int> Stats;

int main()
{
    srand(time(nullptr));
    vector<Questions> data;
    string USER = "USER";
    int choice;

    char Condition;
    //Main Menu
Main:
    cout<<"Welcome "<<USER<<", please choose from the following options:\n";
    cout<<"\t[1] Go to administration menu \n";
    cout<<"\t[2] Update your name \n";
    cout<<"\t[3] Start new quiz \n";
    cout<<"\t[4] Display your scores statistics \n";
    cout<<"\t[5] Display all your scores \n";
    cout<<"\t[6] Exit \n";
Valid_choice1:
    cout<<"Your choice: ";

    cin>>choice;
    if (choice>6 || choice<1)
    {
        cout<<"***Enter valid option***"<<line;
        goto Valid_choice1;
    }
    switch (choice)
    {
        int choice2;
    case 1:
Administration:
        cout<<"Welcome to the administration menu, please choose from the following options:\n";
        cout<<"\t[1] View all questions \n";
        cout<<"\t[2] Add new question \n";
        cout<<"\t[3] Load questions from a file \n";
        cout<<"\t[4] Go back to main menu \n";
Valid_choice2:
        cout<<"Your choice: ";
        cin>>choice2;
        if (choice2>4 || choice2<1)
        {
            cout<<"***Enter valid option***"<<line;
            goto Valid_choice2;
        }
        switch (choice2)
        {
        case 1:
            char option;
            cout<<"Number of questions available: "<<q_number<<line;
            cout<<"Questions list:"<<line;
            cout<<"---------------------------------"<<line;
Printing:
            Printing(data,q_number);
option:
            cout<<"Press D and the question ID, if you want to delete a question"<<line;
            cout<<"Press B, if you want to go back to the main menu"<<line;
            cin>>option;
            if (toupper(option) == 'B')
                goto Administration;
            else if (toupper(option) =='D')
            {
                if (q_number ==0)
                {
                    cout<<"There is no Question to delete"<<line;
                    goto Administration;
                }
                int num;
ValidID:
                cout<<"Enter Question ID: ";
                cin>>num;
                if (num>q_number)
                {
                    cout<<"***Enter valid ID***"<<line;
                    goto ValidID;
                }
                else
                {
                    num-=1;
                    data.erase(data.begin()+num);
                    q_number-=1;
                    counter--;
                    cout<<"New Questions list: "<<line;
                    cout<<"Number of questions available : "<<q_number<<line;
                    cout<<"---------------------------------"<<line;
                    goto Printing;
                }
            }
            else
            {
                cout<<"***Enter valid option***"<<line;
                goto option;
            }
            ///////////////////////////////////////////////////////////////////
            break;
        case 2:
        {
            bool Continue = true;
            do
            {
                INPUT(data,q_number);
Valid1:
                cout<<"Add Another Question ? "<<line;
                cin>>Condition;
                if (toupper(Condition)=='N')
                    Continue = false;
                else if (toupper(Condition)=='Y')
                {
                    counter++;
                    continue;
                }
                else
                {
                    cout<<"***Enter valid option***"<<line;
                    goto Valid1;
                }
            }
            while (Continue);

            goto Administration;
        }
        break;
        ///////////////////////////////////////////////////////////////////
        case 3:
        {
            string filepath;
            cout<<"Enter file path :"<<line;
            cin.ignore();
            getline(cin,filepath);
            INPUT(data,counter,filepath);

            goto Administration;
            break;
        }
        ///////////////////////////////////////////////////////////////////
        case 4:
            goto Main;
        }
        break;
    case 2:
        cout<<"Enter New user name: ";
        cin>>USER;
        cout<<"User name Edited."<<line;
        goto Main;
        break;
Quiz:
    case 3:
        if (q_number <5)
        {
            cout<<"There are not enough questions! please add more."<<line;
            goto Administration;
        }
        else
        {
            cout<<"Quiz Started"<<line;
            cout<<"---------------------------------------------"<<line;
            string PrintedQ;
            string PrintedA;
            cin.ignore();
            for (int i=0; i<5;)
            {
RandomQ:
                int RandomQ = rand()% q_number;
                size_t foundQ = PrintedQ.find(to_string(RandomQ));
                if (foundQ == string::npos)
                {
                    cout<<"["<<i+1<<"]"<<data.at(RandomQ).question<<line;
                    for (int j=0; j<4;)
                    {
RandomA:
                        int RandomA = rand()% 4;
                        size_t foundA = PrintedA.find(to_string(RandomA));
                        if (foundA == string::npos)
                        {
                            if (data.at(RandomQ).answer[RandomA].at(0)=='*')
                            {
                                cout<<"["<<char(j+65)<<"]"<<data.at(RandomQ).answer[RandomA].substr(1,data.at(RandomQ).answer[RandomA].length())<<"\t";
                                j++;
                                PrintedA += to_string(RandomA);
                            }
                            else
                            {
                                cout<<"["<<char(j+65)<<"]"<<data.at(RandomQ).answer[RandomA]<<"\t";
                                j++;
                                PrintedA += to_string(RandomA);
                            }
                        }
                        else
                        {
                            goto RandomA;
                        }

                    }
                    PrintedA.clear();
                    i++;
                    cout<<line;
                    PrintedQ += to_string(RandomQ);
                    string Answer;
                    string True_answer;
                    for (int i=0; i<4; i++)
                    {
                        size_t found = data.at(RandomQ).answer[i].find("*");
                        if (found != string::npos)
                        {
                            True_answer = data.at(RandomQ).answer[i].substr(1,data.at(RandomQ).answer[i].length());
                        }
                    }
                    cout<<"Enter the Answer : ";
                    getline(cin,Answer);
                    if (Answer == True_answer)
                        score++;
                }
                else
                {
                    goto RandomQ;
                }
            }
        }
        cout<<"Your score is: "<<score<<"/5"<<line;
        Stats.push_back(score);
        score = 0;
        goto Main;
        break;
    case 4:
    {
        if (Stats.size() == 0)
        {
            cout<<"No Stats available"<<line;
            goto Main;
        }
        sort(Stats.begin(),Stats.end());
        int Average = 0;
        for (int i=0; i<Stats.size(); i++)
            Average+=Stats.at(i);

        cout<<"-Highest score: "<<Stats.at(Stats.size()-1)<<"/5"<<line;
        cout<<"-Lowest score: "<<Stats.at(0)<<"/5"<<line;
        cout<<"-Average score: "<<Average<<"/5"<<line;
        cout<<"Press [B] if you want to go to Main menu or [E] for Exit"<<line;
Valid3:
        cout<<"Your Choice: ";
        cin>>Condition;
        if (toupper(Condition)=='B')
            goto Main;
        else if (toupper(Condition)=='E')
        {
            cout<<"Thank You :D"<<line;
            return 0;
        }
        else
        {
            cout<<"***Enter Valid option***"<<line;
            goto Valid3;
        }
    }
    break;
    case 5:
        cout<<"Number of Quizzes taken: "<<Stats.size()<<line;
        if (Stats.size()!= 0)
        {
            cout<<"Scores : "<<line;

            for (int i=0; i<Stats.size(); i++)
            {
                cout<<i+1<<"- Quiz score : "<<Stats.at(i)<<"/5"<<"\t";
                cout<<"Number of TRUE answers = "<<Stats.at(i)<<"\tNumber of FALSE answers = "<<5-Stats.at(i)<<line;
            }
        }
        goto Main;
        break;
    case 6:
        cout<<line;
        cout<<"Thank You :D"<<line;
        return 0;
        break;

    }

    return 0;
}
void INPUT(vector<Questions> &data,int &q_number)
{
    int local_counter = q_number;
    cout<<"Enter the question : "<<line;
    string q;
    string a;
    cin.ignore();
    getline(cin,q);
    data.push_back(Questions());
    data.at(local_counter).question = q;
    q_number++;
    counter++;
ReAnswers:
    for (int i=0; i<4; i++)
    {
        cout<<"Enter Answer "<<char(i+65);
        getline(cin,a);
        data.at(local_counter).answer[i] = a;
    }
    int condAns=0;
    for(int j=0; j<4; j++)
    {
        if (data.at(local_counter).answer[j].at(0)=='*')
            condAns++;
    }
    if (condAns!=1)
    {
        cout<<"ReEnter The Answers with the right format with one correct Answer:- \n";
        goto ReAnswers;
    }

}
void INPUT(vector<Questions> &data,int &counter,string file_path)
{
    ifstream input_file;
    input_file.open(file_path);
    if ( ! input_file.is_open() )
    {
        cout <<" Failed to open" << line;
        return;
    }
    else
    {
        cout <<"Opened OK" << line;
        string lines;
        while (!input_file.eof())
        {
            data.push_back(Questions());
            getline(input_file,lines);
            data.at(counter).question=lines;

            getline(input_file,lines);
            data.at(counter).answer[0] = "*" + lines;


            getline(input_file,lines);
            data.at(counter).answer[1] = lines;

            getline(input_file,lines);
            data.at(counter).answer[2] = lines;

            getline(input_file,lines);
            data.at(counter).answer[3] = lines;
            counter++;
            q_number++;
        }

        input_file.close();
        cout<<"Questions File Was Loaded Successfully"<<line;
    }
}

void Printing(vector<Questions> &data,const int q_number)
{
    for (int i=0; i<q_number; i++)
    {
        cout<<"["<<(i+1)<<"]"<<data.at(i).question<<line;
        for(int j=0; j<4; j++)
        {
            if (data.at(i).answer[j].at(0)=='*')
            {
                string x=data.at(i).answer[j];
            }
        }
        cout<<"\t[a]"<<data.at(i).answer[0]<<"\t[b]"<<data.at(i).answer[1]<<"\t[c]"<<
            data.at(i).answer[2]<<"\t[d]"<<data.at(i).answer[3]<<line;
    }
    cout<<"----------------------------------------------------------------------"<<line;
}
