#include<bits/stdc++.h>
using namespace std;

struct question
{
    int parent_id=-1;
    int sender_id;
    int receiver_id;
    bool anonymous=0;
    string answer="-1";
    string question_text="-1";
};

struct user
{
    int id;
    string user_name;
    string password;
};

class askManager{
    vector<string> user_names_vec , passwords_vec;
    map<string,bool>repeated_map;
    vector<question>questions;
public:
    askManager(){
        copy_files();
    }
    ~askManager(){
        Upload_files();
    }
    void copy_files(){// must be called when start to load data  useres
        ifstream fin,pin,kin;
        fin.open("Xuser.txt");
        pin.open("Xpass.txt");
        kin.open("question.txt");
        int sz;
        fin>>sz;
        pin>>sz;
        user_names_vec.resize(sz);
        passwords_vec.resize(sz);
        for(int i=0;i<sz;i++)
        {
            string x;
            fin>>x;
            repeated_map[x]=1;
            user_names_vec[i]=x;
            pin>>x;
            repeated_map[x]=1;
            passwords_vec[i]=x;
        }
        fin.close();
        pin.close();
        kin>>sz;
        questions.resize(sz);
        for(int i=0;i<sz;i++)
        {
            kin>>questions[i].anonymous;
            kin>>questions[i].parent_id;
            kin>>questions[i].sender_id;
            kin>>questions[i].receiver_id;
            kin>>questions[i].answer;
            kin>>questions[i].question_text;
        }
        kin.close();
    }
    void Upload_files(){// called when log out to restore the new data users to files
        ofstream fot,pot,kot;
        fot.open("Xuser.txt");
        pot.open("Xpass.txt");
        kot.open("question.txt");
        fot<<user_names_vec.size()<<endl;
        pot<<passwords_vec.size()<<endl;
        for(int i=0;i<passwords_vec.size();i++)
        {
            fot<<user_names_vec[i]<<endl;
            pot<<passwords_vec[i]<<endl;
        }
        fot.close();
        pot.close();
        kot<<questions.size()<<endl;
        for(int i=0;i<questions.size();i++)
        {
            kot<<questions[i].anonymous<<endl;
            kot<<questions[i].parent_id<<endl;
            kot<<questions[i].sender_id<<endl;
            kot<<questions[i].receiver_id<<endl;
            kot<<questions[i].answer<<endl;
            kot<<questions[i].question_text<<endl;
        }
        kot.close();
    }
    void print_questions_to_me(int index){// operation 1
        int c=0;
        for(auto i:questions)
        {
            if(i.receiver_id==index)
            {
                if(i.parent_id!=-1)
                {
                    cout<<"Thread: ";
                }
                cout<<"Question id ("<<c<<")";
                if(i.anonymous==0)cout<<"from user id("<<i.sender_id<<") ";
                cout<<"question: "<<i.question_text<<endl;
                if(i.answer!="-1") { if(i.parent_id!=-1){cout<<"Thread:  ";}
                    cout << " Answer: " << i.answer << endl; }
            }
            c++;
        }
    }
    void print_question_from_me(int index)
    {
        int c=0;
        for(auto i:questions)
        {
            if(i.sender_id==index)
            {

                cout<<"Question id ("<<c<<")";
                if(i.anonymous==0)cout<<" !AQ ";
                cout<<"to user id("<<i.receiver_id<<") ";
                cout<<"question: "<<i.question_text<<endl;
                if(i.answer!="-1") {
                    cout << " Answer: " << i.answer << endl; }
            }
            c++;
        }
    }
    void answer_question(int index)
    {
        cout<<"enter question id or -1 to cancel: ";
        int n;  cin>>n;
        if(n==-1)return;
        if(questions[n].receiver_id==index and n<questions.size())
        {
            cout<<"Question id ("<<n<<") ";
            if(questions[n].anonymous==0)
                cout<<"from user id("<<questions[n].sender_id<<") ";
            cout<<"Question: "<<questions[n].question_text<<endl;
            if(questions[n].answer!="-1") { cout << "Answer: " << questions[n].answer << endl;
                cout<<"Warning: Already answered. answer will be updated\n";
            }
            cout<<"Enter answer: ";
            getline(cin,questions[n].answer);
            getline(cin,questions[n].answer);

        }
        else
        {
            cout<<"can't be answered\n";
        }
    }
    void delete_question(int index)
    {
        cout<<"Enter the question id or -1 to cancel"<<endl;
        int n;  cin>>n;
        if(n==-1)return;
        if(questions[n].sender_id==index and n<questions.size())
        {
            questions.erase(questions.begin()+n);
            cout<<"deleted successfully...\n"
                  "questions ides will be changed. please revise your data before next operations.";
        }
        else
        {
            cout<<"question can't be reached."<<endl;
        }
    }
    void ask_question( int index)
    {
        cout<<"Enter user id or -1 to cancel"<<endl;
        int n;  cin>>n;
        if(n==-1) {cout<<endl; return; }
        // noting anonymous if user allow
        cout<<"for thread question: Enter question id or -1 for new question"<<endl;
        int q_id;   cin>>q_id;
        if(q_id==-1)
        {
            cout<<"Enter question text\n";

            question q;
            string xx;
            getline(cin,xx);
            getline(cin,xx);
            q.question_text=xx;
            q.sender_id=index;
            q.receiver_id=n;
            questions.push_back(q);
            cout<<"Question is sent successfully...\n";
        }
        else{
            cout<<"Enter question text\n";

            question q;
            getline(cin,q.question_text);
            getline(cin,q.question_text);
            q.sender_id=index;
            q.receiver_id=n;
            q.parent_id=q_id;
            questions.push_back(q);
            cout<<"Question is sent successfully...\n";
        }
        cout<<endl;
    }
    void list_system_users()
    {
        int c=0;
        cout<<"     ------------"<<endl;
        for(auto i:user_names_vec)
        {
            cout<<"ID: "<<c<<"      Name: "<<i<<endl;
            c++;
            cout<<"     ------------"<<endl;

        }
    }
    void feed()
    {
        int c=0;
        for(auto i:questions)
        {
            if(i.parent_id!=-1)cout<<"Thread ";
            cout<<"question id ( "<<c<<" ) from user ( "<<i.sender_id<<" ) to user ( "<<i.receiver_id<<" ) \n";
            cout<<"Question: "<<i.question_text<<endl;
            if(i.answer!="-1")
                cout<<"Answer: "<<i.answer<<endl;
            c++;
            cout<<"     -----------------"<<endl;
        }
    }
    void Dashboard(user xuser)
    {
        while (true)
        {
            cout<<"\nMenue:\n";
            cout<<"  1: Print Questions To Me" // done
                  "\n  2: Print Questions From Me"  //done
                  "\n  3: Answer Question" // done
                  "\n  4: Delete Question" // done
                  "\n  5: Ask Question" // done
                  "\n  6: List System Users" // done
                  "\n  7: Feed" // done
                  "\n  8: Logout"<<endl;
            cout<<"Enter number in range 1 - 8: ";
            int n;
            cin>>n;
            if(n==1)
            {
                print_questions_to_me(xuser.id);
            }
            else if(n==2)
            {
                print_question_from_me(xuser.id);
            }
            else if(n==3)
            {
                answer_question(xuser.id);
            }
            else if(n==4)
            {
                delete_question(xuser.id);
            }
            else if(n==5)
            {
                ask_question(xuser.id);
            }
            else if(n==6)
            {
                list_system_users();
            }
            else if(n==7)
            {
                feed();
            }
            else if(n== 8)
            {
                break;
            }

        }
    }
    void login(){
        cout<<"Enter your username & password\n";
        string usern,pass;    cin>>usern>>pass;
        int index=-1;
        for(int i=0;i<user_names_vec.size();i++)
        {
            if(user_names_vec[i]==usern)
            {
                if(passwords_vec[i]==pass)
                {
                    cout<<"Wellcome "<<usern<<endl;
                    index=i;
                    break;
                }
                else
                {
                    index=-2;
                    break;
                }
            }
        }
        if(index==-1)
        {
            cout<<"Not valid username"<<endl;
        }
        else
        if(index==-2)
        {
            cout<<"Not a correct password"<<endl;
        }
        else
        {

            // user_management:
            user x;
            x.id = index;
            x.user_name = usern;
            x.password = passwords_vec[index];

            // calling Dashboard when it is ready
            Dashboard(x);
        }

    }
    void sign_up()
    {
        string name ,password;
        cout<<"Enter your username & password"<<endl;
        cin>>name>>password;
        if(repeated_map[name]==1)
        {
            cout<<"Invalid user name"<<endl;
        }
        else if(repeated_map[password]==1 and repeated_map[name])
        {
            cout<<"the account already exist"<<endl;
        }
        else
        {
            user_names_vec.push_back(name);
            passwords_vec.push_back(password);
            repeated_map[name]=1;
            repeated_map[password]=1;
            cout<<"Signed up seccessfuly."<<endl;
        }
    }
    void start()
    {
        copy_files();
        cout<<"\n-----ASK.ME-----"<<endl;
        while (true)
        {
            int x;
            cout<<endl;
            cout<<"1: Log In"<<endl;
            cout<<"2: Sign Up"<<endl;
            cout<<"3: Exit"<<endl;
            cout << "\nEnter number from 1 - 3: ";
            cin >> x;
            if (x == 1) {
                // login func
                login();
                Upload_files();
            } else if(x == 2){
                // sign up func
                sign_up();
                continue;
            } else if(x==3){

                cout<<"See Y later."<<endl;
                break;
            } else {
                cout << "Wrong choice , please try again\n";
            }
        }


    }
};
int main() {
    askManager starter;
    starter.start();
    return 0;
}