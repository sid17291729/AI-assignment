#include<iostream>
#include<bits/stdc++.h>
#include<Eigen/Dense>
#include<fstream>
// /mnt/c/users/omen/desktop/courses/AI/assignment/eigen-3.3.9
using namespace std;
using namespace Eigen;
class test_class
{
public:
    MatrixXd *m;
    void init()
    {
        m=(MatrixXd *)malloc(sizeof(MatrixXd)*5);
        m[0]=MatrixXd(2,2);
        m[1]=MatrixXd(3,4);
        cout<<m[0]<<'\n'<<'\n'<<m[1];
    }
    
    
};
int main()
{
    test_class ob;
    ob.init();
}