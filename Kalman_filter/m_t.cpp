#include<iostream>
#include<stdlib.h>
#include<Eigen/Dense>
#include<fstream>
// /mnt/c/users/omen/desktop/courses/AI/assignment/eigen-3.3.9
using namespace std;
using namespace Eigen;
class test_class
{
public:
    MatrixXd m;
    void init()
    {
        m=MatrixXd(1,2);
        m(0,1)=1;
        m(0,0)=2;
    }
    void change()
    {
        MatrixXd t(1,2);
        t(0,0)=-1;
        t(0,1)=-2;
        m=t;
    }
    
};
int main()
{
    test_class ob;
    ob.init();
    cout<<ob.m<<'\n';
    ob.change();
    
    cout<<ob.m<<'\n';
}