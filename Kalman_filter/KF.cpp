#include<iostream>
#include<stdlib.h>
#include<Eigen/Dense>
#include<fstream>
// /mnt/c/users/omen/desktop/courses/AI/assignment/eigen-3.3.9
using namespace std;
using namespace Eigen;
class KF
{
private:
    /* data */
public:
    KF(/* args */);
    ~KF();
    MatrixXd F,G,H;
    int x_D,z_D,u_D;
    MatrixXd KG,X,U,Z;
    MatrixXd Q,P,R;
    MatrixXd *Z_D;
    MatrixXd *U_D;
    MatrixXd *result;
    int N;
    KF(int x,int u,int z)
    {
        x_D=x;
        u_D=u;
        z_D=z;

        F=MatrixXd(x_D,x_D);
        G=MatrixXd(x_D,u_D);
        H=MatrixXd(z_D,x_D);

        KG=MatrixXd(x_D,z_D);
        X=MatrixXd(x_D,1);
        U=MatrixXd(u_D,1);
        Z=MatrixXd(z_D,1);

        P=MatrixXd(x_D,x_D);
        Q=MatrixXd(x_D,x_D);
        R=MatrixXd(z_D,z_D);
    }
    
    void get_KG()
    {
        MatrixXd denom=H*P*(H.transpose())+R;
        denom=denom.inverse();
        MatrixXd nume=P*(H.transpose());
        KG=nume*denom;
    }
    void predict()
    {
        X=F*X+G*U;
        P=F*P*(F.transpose())+Q;
    }
    void update()
    {
        get_KG();
        X=X+KG*(Z-H*X);
        MatrixXd I=MatrixXd:: Identity(x_D,x_D);
        P=(I-KG*H)*P*((I-KG*H).transpose())+KG*R*(KG.transpose());
    }
    // void print_X()
    // {
    //     cout<<X<<'\n';
    // }
    void read_F(ifstream &fp)
    {
        int n=x_D;
        for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            double x;
            fp>>x;
            F(i,j)=x;
        
        }
    }
    void read_H(ifstream &fp)
    {
        int m=z_D;
        int n=x_D;
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<n;++j)
            {
                double x;
                fp>>x;
                H(i,j)=x;
            }
        }
    }
    void read_G(ifstream &fp)
    {
        int m =u_D;
        int n =x_D;
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<m;++j)
            {
                double x;
                fp>>x;
                G(i,j)=x;
            }
        }
    }
    void read_P(ifstream &fp)
    {
        int n=x_D;
        for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            double x;
            fp>>x;
            P(i,j)=x;
        
        }
    }
    void read_Q(ifstream &fp)
    {
        int n=x_D;
        for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            double x;
            fp>>x;
            Q(i,j)=x;
        
        }
    }
    void read_R(ifstream &fp)
    {
        int n=z_D;
        for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            double x;
            fp>>x;
            R(i,j)=x;
        
        }
    }
    void read_mats(ifstream &fp)
    {
        read_F(fp);

        if(u_D!=0)
        read_G(fp);
        //cout<<G<<'\n';
        read_H(fp);
        read_P(fp);
        read_Q(fp);
        read_R(fp);
    }
    void init_x_U(ifstream &fp)
    {
        for(int i=0;i<x_D;++i)
        {   double x;
            fp>>x;
            X(i,0)=x;
        }
        if(u_D==0)
        return;
        
        for(int i=0;i<u_D;++i)
        {   double x;
            fp>>x;
            U(i,0)=x;
        }
    }
    void read_DATA(ifstream &fp)
    {   
        
        fp>>N;
        Z_D=(MatrixXd*)malloc(sizeof(MatrixXd)*N);
        if(u_D!=0)
        U_D=(MatrixXd*)malloc(sizeof(MatrixXd)*N);
        for(int i=0;i<N;++i)
        {   Z_D[i]=MatrixXd(z_D,1);
            for(int j=0;j<z_D;++j)
            {
                double D;
                fp>>D;
                Z_D[i](j,0)=D;
            }
            if(u_D==0)
            continue;
            U_D[i]=MatrixXd(u_D,1);
            for(int j=0;j<u_D;++j)
            {
                double D;
                fp>>D;
                U_D[i](j,0)=D;
            }
        }
    }
    void solve()
    {   result=(MatrixXd *)malloc(sizeof(MatrixXd)*N);
        predict();
        cout<<X<<"\n\n";
        cout<<P<<"\n\n";
        int i=0;
        while(i<N)
        {
            Z=Z_D[i];
            //cout<<Z<<"yes\n";
            if(u_D!=0)
            U=U_D[i];
            U(0,0)=U(0,0)-9.8;
            //cout<<U<<"yes\n";
            update();
            //cout<<P<<"\n\n";
            predict();
            
            result[i]=X;
            ++i;
        }

    }
    void print_result()
    {
       for(int i=0;i<N;++i)
       cout<<result[i]<<"\n\n";
    }
};

KF::KF(/* args */)
{
}

KF::~KF()
{
}
int main(int argc, char *argv[])
{
    ifstream mat(argv[1]);
    ifstream data(argv[2]);
    int x,u,z;
    mat>>x;
    mat>>u;
    mat>>z;
    KF K(x,u,z);       
    //cout<<K.x_D<<' '<<K.y_D<<' '<<K.u_D<<'\n';
    
    
    
    K.read_mats(mat);
    K.init_x_U(data);
    K.read_DATA(data);
    // K.predict();
    // K.Z(0,0)=-32.4;
    // K.update();
    K.solve();
    K.print_result();
    
    
}
/*
yd X xd * xdX1
*/
