//solution by Wsl_F
#include <bits/stdc++.h>

using namespace std;
#pragma comment(linker, "/STACK:1024000000,1024000000")


typedef long long LL;
typedef unsigned long long uLL;
typedef double dbl;
typedef vector<int> vi;
typedef vector<LL> vL;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef pair<LL,LL> pLL;

#define mp(x,y)  make_pair((x),(y))
#define pb(x)  push_back(x)
#define sqr(x) ((x)*(x))

class Point
{
private:
public:
    dbl x,y,z,v;
 const dbl eps= 1e-6;

public:
    Point(dbl x1, dbl y1, dbl z1, dbl v1) : x(x1), y(y1), z(z1), v(v1) { }

    Point() : x(0), y(0), z(0), v(0) { }

    dbl dist(Point &p2)
    {
        dbl d= 0;
        d+= sqr(x-p2.x);
        d+= sqr(y-p2.y);
        d+= sqr(z-p2.z);
        d+= sqr(v-p2.v);
        d= sqrt(d);
        return d;
    }

    friend ostream& operator<<(ostream& out, Point &p)
    {
        out << p.x << " " << p.y << " " << p.z << " " << p.v << endl;
        return out;
    }

    friend istream& operator>>(istream &input, Point &p)
    {
        input >> p.x >> p.y >> p.z >> p.v;
        return input;
    }

    void addPoint(Point p)
    {
        x+= p.x;
        y+= p.y;
        z+= p.z;
        v+= p.v;
    }

    void div(double k)
    {
        x/= k;
        y/= k;
        z/= k;
        v/= k;
    }

    bool equals(Point p)
    {
        dbl diff= max(abs(x-p.x), abs(y-p.y));
        diff= max(diff,abs(z-p.z));
        diff= max(diff,abs(v-p.v));
        return diff < eps;
    }

    Point& operator= (const Point &p)
    {
        x= p.x;
        y= p.y;
        z= p.z;
        v= p.v;

        return *this;
    }
};

const int MaxN= 1000;
vector<Point> centres;
int claster[MaxN+10];
Point p[MaxN+10];


int read()
{
    ifstream in("input.txt");

    int i= 0;
    while (in>>p[++i]);
    in.close();

    return i-1;
}

vector<vi> getClasters(int n)
{
    vector<vi> clasters;
    clasters.resize(centres.size());
    for (int i= 1; i<=n; i++)
        clasters[ claster[i] ].pb(i);

    return clasters;
}

void print(int n)
{
    freopen("output.txt","w",stdout);


    vector<vi> clasters= getClasters(n);
    {
        for (int j= 0; j<centres.size(); j++)
        {
            cout<<"Claster "<<j<<":"<<endl;
            cout<<"center : "<<centres[j]<<endl;
            for (int i : clasters[j])
                cout<<p[i]<<endl;
            cout<<endl;
        }
    }
}

bool updateCentres(int n)
{
 bool f= 0;
 vector<vi> clasters= getClasters(n);
 for (int i= 0; i<clasters.size(); i++)
 {
     Point newCenter;
     for (int pN : clasters[i])
        newCenter.addPoint(p[pN]);
    newCenter.div(clasters[i].size());
    if (!newCenter.equals(centres[i]))
    {
        centres[i]= newCenter;
        f= 1;
    }
 }

 return f;
}

void classifyAll(int n)
{
    for (int i= 1; i<=n; i++)
    {
        int j0= 0;
        int d= centres[0].dist(p[i]);
        for (int j= 1; j<centres.size(); j++)
            if (centres[j].dist(p[i]) < d)
            {
                d= centres[j].dist(p[i]);
                j0= j;
            }
        claster[i]= j0;
    }
}

// n - number of points, k - number of clasters
void getClasters(int n, int k)
{
    centres.clear();
    for (int i= 1; i<=k; i++)
        centres.pb(p[rand()%n+1]);

    classifyAll(n);
    int i= 0;
    while (updateCentres(n))
    {
        classifyAll(n);
        i++;
    }
    cout<<"Classification takes " << i << " cycles!"<<endl;
}

int main()
{
    int n= read();
    cout<<"Enter number of clasters: ";
    int k;
    cin>>k;

    getClasters(n, k);

    print(n);

    return 0;
}
