#include <iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include <fstream>
#include<string>
using namespace std;
double vector_dot(vector<double> a, vector<double> b);
class MDP
{ 
private:
    /* data */
public:
    unordered_map<int,string> state_map;
    unordered_map<int,string> action_map;
    vector<vector<vector<double>>> action_matrix;
    vector<vector<double>> reward_matrix;
    int state_size;
    int actions;
    vector<double> state_vector;
    vector<int> policy;
    double Gamma;
    MDP(/* args */);
    ~MDP();
    
    void populate_state_map(string file_name)
    {
        ifstream state_file(file_name);
        string line;

        while(getline(state_file,line))
        {
            int col_pos=line.find(':');
            string num_string=line.substr(0,col_pos);
            int num=stoi(num_string);
            string state_name=line.substr(col_pos+1);
            //cout<<num_string<<' '<<state_name<<'\n';
            state_map[num]=state_name;
        }
        printf("file traversed state map populated\n");
        state_file.close();
        state_size=state_map.size();
        vector<double> temp(state_size);
        state_vector=temp;
        vector<int>t(state_size);
        policy=t;
    }

    
    void populate_actions(string file_name)
    {   string line;
        ifstream action_file(file_name);
        getline(action_file,line);
        actions=stoi(line);
        
        for(int i=0;i<actions;++i)
        {
            getline(action_file,line);
            int col_pos=line.find(':');
            int num=stoi(line.substr(0,col_pos));
            string action_name=line.substr(col_pos+1);
            action_map[num]=action_name;
            //cout<<num<<' '<<action_name<<'\n';
        }
            
        vector<vector<vector<double>>> temp_action_matrix(actions,vector<vector<double>>(state_size,vector<double>(state_size,0)));
        action_matrix=temp_action_matrix;

        for(int i=0;i<actions;++i)
        {
            for(int j=0;j<state_size;++j)
            {
                for(int k=0;k<state_size;++k)
                {
                    double num;
                    action_file >> num;
                    action_matrix[i][j][k]=num;
                }
                
        
            }
    
        }
       printf("action map and action matrix populated\n");
        
    }
    void populate_reward_matrix(string file_name)
    {   vector<vector<double>> temp (state_size,vector<double>(actions));
        reward_matrix=temp;
        ifstream action_file(file_name);

        for(int i=0;i<state_size;++i)
        {
            for(int j=0;j<actions;++j)
            {
                double num;
                action_file >> num;
                reward_matrix[i][j]=num;
            }
        }

    }
    
    void init_state(int seed)
    {
        for(int i=0;i<state_size;++i)
         state_vector[i]=0;
    }
    // void init_policy(int seed)
    // {
    //     srand(seed);
    //     for(int i=0;i<state_size;++i)
    //     {
    //         policy[i]=rand()%actions;
    //     }
    // }
    // void solve_policy_itr(int itr)
    // {
    //     init_policy(0);
    //     init_state(0);
    //     vector<double> temp(state_size);
    //     for(int i=0;i<state_size;++i)
    //     {   int act=policy[i];
    //         temp[i]=reward_matrix[i][act]+Gamma*vector_dot(action_matrix[act][i],state_vector);
    //     }
    //     state_vector=temp;
    //     while(itr)
    //     {
    //         itr--;
    //         for(int i=0;i<state_size;++i)
    //         {   double val;
    //             int act;
    //             for(int j=0;j<actions;++j)
    //             {
    //                 double v=reward_matrix[i][j];
    //             }
    //         }
    //     }
    // }
    void solve_value_itr(int itr)
    {
        double g=Gamma;
        printf("starting iterations\n");
        while(itr>0)
        {  --itr;
            vector<double> temp_state(state_size);
            for(int i=0;i<state_size;++i)
            {   double val;
                int act=-1;
                for(int j=0;j<actions;++j)
                {
                    double t=reward_matrix[i][j]+g*vector_dot(action_matrix[j][i],state_vector);
                    if(j==0)
                    {
                        val=t;
                        act=0;
                    }
                    else
                    {
                        if(t>val)
                        {
                            val=t;
                            act=j;
                        }
                    }

                }
                temp_state[i]=val;
                
                policy[i]=act+1;
            }
            state_vector=temp_state;
        }
    } 
};
double vector_dot(vector<double> a, vector<double> b)
{
    int l=a.size();
    double ret=0;
    for(int i=0;i<l;++i)
    ret=ret+a[i]*b[i];

    return ret;
}
MDP::MDP(/* args */)
{
}

MDP::~MDP()
{
}

int main(int argc , char *argv[])
{
 
 string state_file(argv[1]);
 string action_file(argv[2]);
 string reward_file(argv[3]);
 
 MDP M;
 M.populate_state_map(state_file);
 M.populate_actions(action_file);
 M.populate_reward_matrix(reward_file);
 M.init_state(0);

 printf("Please enter the number of iterations\n");
 int itr;
 scanf("%d",&itr);
 printf("please enter Gamma\n");
 scanf("%lf",&M.Gamma);
 M.solve_value_itr(itr);

for(int i=0;i<9;++i)
{    string a,b;
    a=M.state_map[i+1];
    b=M.action_map[M.policy[i]];
    cout<<a<<'\n'<<b<<"\n\n";   
    

}
 
}
