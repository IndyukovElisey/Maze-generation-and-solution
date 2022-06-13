#include "Maze.h"
#include <Windows.h>
#include <cstdlib>
#include <cstdlib>
#include <QTime>
#include <QDateTime>


Maze::Maze(int a, int b, QWidget *parent) :
    QWidget(parent), height(a), width(b)
{
    timeGeneration = 0;
    timePathfind = 0;

    this->setMinimumSize(a*20+10, a*20+10);
    this->resize(a*20+10, a*20+10);

    this->setObjectName(QString::fromUtf8("widget_maze"));
    this->setObjectName(QString::fromUtf8("widget_maze"));
    this->setEnabled(true);
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy1);
    this->setMaximumWidth(300);

    path_found = -1;

    matrix = new bool*[2*height+1];
    for(int i=0;i<2*height+1;i++)
        matrix[i]=new bool[2*width+1];

    clearCells();
}

void Maze::clearCells()
{
    for(int i=0;i<2*height+1;i++)
    {
        for(int j=0; j<2*width+1;j++)
        {
            //matrix[i][j]=qrand()%2;
            if(i%2==1 && j%2==1)
                matrix[i][j]=0;
            else
                matrix[i][j]=1;
            if(i==0 || i==2*height)
                matrix[i][j]=1;
            if(j==0 || j==2*width)
                matrix[i][j]=1;

        }
    }
    path_found=-1;
}

void Maze::generate1()
{
    clearCells();
    path_found = 0;
    time.start();


    bool visit[height][width];
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            visit[i][j]=0;
        }
    int visit_count=1;
    visit[0][0]=1;
    bool direction[4];

    int cur_x=0,cur_y=0, rand_neighbour;

    QVector <pair> stack;

    stack.push_back({0,0});
    while(visit_count<height*width)
    {
        int count_neighbours=0;
        for(int i=0;i<4;i++)
        {
            direction[i]=0;
        }
        if(cur_x<width-1)
            if(visit[cur_y][cur_x+1]==0)
            {
                count_neighbours++;
                direction[0]=1;
            }
        if(cur_y<height-1)
            if(visit[cur_y+1][cur_x]==0)
            {
                count_neighbours++;
                direction[1]=1;
            }
        if(cur_x>0)
            if(visit[cur_y][cur_x-1]==0)
            {
                count_neighbours++;
                direction[2]=1;
            }
        if(cur_y>0)
            if(visit[cur_y-1][cur_x]==0)
            {
                count_neighbours++;
                direction[3]=1;
            }

        if(count_neighbours>0)
        {
            rand_neighbour=qrand()%count_neighbours;
            //rand_neighbour=0;
            int cur_direction;
            for(int i=0;i<4;i++)
            {
                if(direction[i]==1 && rand_neighbour==0)
                {
                    cur_direction=i;
                    break;
                }
                else if(direction[i]==1)
                    rand_neighbour--;
            }

            switch(cur_direction)
            {
            case 0:
            {
                matrix[cur_y*2+1][cur_x*2+2]=0;
                cur_x++;
                break;
            }
            case 1:
            {
                matrix[cur_y*2+2][cur_x*2+1]=0;
                cur_y++;
                break;
            }
            case 2:
            {
                matrix[cur_y*2+1][cur_x*2]=0;
                cur_x--;
                break;
            }
            case 3:
            {
                matrix[cur_y*2][cur_x*2+1]=0;
                cur_y--;
                break;
            }
            }
            visit[cur_y][cur_x]=1;
            stack.push_back({cur_y,cur_x});
            visit_count++;
        }
        else
        {
            stack.pop_back();
            cur_x=stack.last().x;
            cur_y=stack.last().y;
        }

    }
    matrix[1][0]=0;
    matrix[2*height][2*width-1]=0;

    timeGeneration = time.elapsed();
    this->repaint();
}

void Maze::generate2()
{
    clearCells();
    path_found = 0;
    time.start();

    bool visit[height][width];
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            visit[i][j]=0;
        }
    int visit_count=1;
    visit[0][0]=1;
    bool direction[4];

    int cur_x=0,cur_y=0, rand_neighbour;

    while(visit_count<height*width)
    {
        int count_neighbours=0;
        for(int i=0;i<4;i++)
        {
            direction[i]=0;
        }
        if(cur_x<width-1)
            if(visit[cur_y][cur_x+1]==0)
            {
                count_neighbours++;
                direction[0]=1;
            }
        if(cur_y<height-1)
            if(visit[cur_y+1][cur_x]==0)
            {
                count_neighbours++;
                direction[1]=1;
            }
        if(cur_x>0)
            if(visit[cur_y][cur_x-1]==0)
            {
                count_neighbours++;
                direction[2]=1;
            }
        if(cur_y>0)
            if(visit[cur_y-1][cur_x]==0)
            {
                count_neighbours++;
                direction[3]=1;
            }

        if(count_neighbours>0)
        {
            rand_neighbour=qrand()%count_neighbours;
            //rand_neighbour=0;
            int cur_direction;
            for(int i=0;i<4;i++)
            {
                if(direction[i]==1 && rand_neighbour==0)
                {
                    cur_direction=i;
                    break;
                }
                else if(direction[i]==1)
                    rand_neighbour--;
            }

            switch(cur_direction)
            {
            case 0:
            {
                matrix[cur_y*2+1][cur_x*2+2]=0;
                cur_x++;
                break;
            }
            case 1:
            {
                matrix[cur_y*2+2][cur_x*2+1]=0;
                cur_y++;
                break;
            }
            case 2:
            {
                matrix[cur_y*2+1][cur_x*2]=0;
                cur_x--;
                break;
            }
            case 3:
            {
                matrix[cur_y*2][cur_x*2+1]=0;
                cur_y--;
                break;
            }
            }
            visit[cur_y][cur_x]=1;
            visit_count++;
        }
        else
        {
            bool flag=1;
            for(int i=0;i<height && flag==1;i++)
            {
                for(int j=0;j<width && flag==1;j++)
                {
                    if(visit[i][j]==0)
                    {
                        if(j<width-1 && visit[i][j+1]==1)
                        {
                            //if(visit[i][j+1]==1)
                            {
                                matrix[i*2+1][j*2+2]=0;
                                cur_x=j;
                                cur_y=i;
                                flag=0;
                                break;
                            }
                        }
                        else if(i<height-1 && visit[i+1][j]==1)
                        {
                            //if(visit[i+1][j]==1)
                            {
                                matrix[i*2+2][j*2+1]=0;
                                cur_x=j;
                                cur_y=i;
                                flag=0;
                                break;
                            }
                        }
                        else if(j>0 && visit[i][j-1]==1)
                        {
                            //if(visit[i][j-1]==1)
                            {
                                matrix[i*2+1][j*2]=0;
                                cur_x=j;
                                cur_y=i;
                                flag=0;
                                break;
                            }
                        }
                        else if(i>0 && visit[i-1][j]==1)
                            //if(visit[i-1][j]==1)
                            {
                                matrix[i*2][j*2+1]=0;
                                cur_x=j;
                                cur_y=i;
                                flag=0;
                                break;
                            }

                    }
                }
            }
            visit[cur_y][cur_x]=1;
            visit_count++;
        }

    }
    matrix[1][0]=0;
    matrix[2*height][2*width-1]=0;

    timeGeneration = time.elapsed();
    this->repaint();
}

void Maze::solve1()
{
    time.start();
    if(path_found==-1)
    {
        return;
    }
    bool visit[height][width];
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            visit[i][j]=0;
        }
    visit[0][0]=1;
    bool direction[4];

    int cur_x=0,cur_y=0, rand_neighbour;

    QVector <pair> stack;

    stack.push_back({0,0});
    while(cur_x!=width-1 || cur_y!=height-1)
    {
        int count_neighbours=0;
        for(int i=0;i<4;i++)
        {
            direction[i]=0;
        }
        if(cur_x<width-1)
            if(visit[cur_y][cur_x+1]==0 && matrix[cur_y*2+1][cur_x*2+2]==0)
            {
                count_neighbours++;
                direction[0]=1;
            }
        if(cur_y<height-1 && matrix[cur_y*2+2][cur_x*2+1]==0)
            if(visit[cur_y+1][cur_x]==0)
            {
                count_neighbours++;
                direction[1]=1;
            }
        if(cur_x>0 && matrix[cur_y*2+1][cur_x*2]==0)
            if(visit[cur_y][cur_x-1]==0)
            {
                count_neighbours++;
                direction[2]=1;
            }
        if(cur_y>0 && matrix[cur_y*2][cur_x*2+1]==0)
            if(visit[cur_y-1][cur_x]==0)
            {
                count_neighbours++;
                direction[3]=1;
            }

        if(count_neighbours>0)
        {
            rand_neighbour=qrand()%count_neighbours;
            //rand_neighbour=0;
            int cur_direction;
            for(int i=0;i<4;i++)
            {
                if(direction[i]==1 && rand_neighbour==0)
                {
                    cur_direction=i;
                    break;
                }
                else if(direction[i]==1)
                    rand_neighbour--;
            }

            switch(cur_direction)
            {
            case 0:
            {
                cur_x++;
                break;
            }
            case 1:
            {
                cur_y++;
                break;
            }
            case 2:
            {
                cur_x--;
                break;
            }
            case 3:
            {
                cur_y--;
                break;
            }
            }
            visit[cur_y][cur_x]=1;
            stack.push_back({cur_y,cur_x});
        }
        else
        {
            stack.pop_back();
            cur_x=stack.last().x;
            cur_y=stack.last().y;
        }

    }
    solution=stack;
    path_found=1;
    timePathfind = time.elapsed();
    this->repaint();
}

void Maze::solve2()
{
    time.start();
    if(path_found==-1)
    {
        return;
    }
    bool visit[height][width];
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            visit[i][j]=0;
        }
    visit[0][0]=1;

    bool direction[4];
    int cur_direction=0;
    int cur_x=0,cur_y=0;
    QVector <pair> stack;
    stack.push_back({0,0});

    while(cur_x!=width-1 || cur_y!=height-1)
    {
        for(int i=0;i<4;i++)
        {
            direction[i]=0;
        }

        if(cur_x<width-1)
            if(matrix[cur_y*2+1][cur_x*2+2]==0)
            {
                direction[0]=1;
            }
        if(cur_y<height-1 && matrix[cur_y*2+2][cur_x*2+1]==0)
            {
                direction[1]=1;
            }
        if(cur_x>0 && matrix[cur_y*2+1][cur_x*2]==0)
            {
                direction[2]=1;
            }
        if(cur_y>0 && matrix[cur_y*2][cur_x*2+1]==0)
            {
                direction[3]=1;
            }

        if(direction[(cur_direction+1)%4]==1)
            cur_direction=(cur_direction+1)%4;
        else
            if(direction[cur_direction]==1)
                cur_direction=cur_direction;
        else
                if(direction[(cur_direction+3)%4]==1)
                    cur_direction=(cur_direction+3)%4;
        else
                    cur_direction=(cur_direction+2)%4;

        switch(cur_direction)
        {
        case 0:
        {
            cur_x++;
            break;
        }
        case 1:
        {
            cur_y++;
            break;
        }
        case 2:
        {
            cur_x--;
            break;
        }
        case 3:
        {
            cur_y--;
            break;
        }
        }

        bool ok=1;

        for(int i=0; i<stack.size();i++)
        {
            if(stack[i].x==cur_x && stack[i].y==cur_y)
                ok=0;
        }
        if(ok==1)
        {
            stack.push_back({cur_y,cur_x});
        }
        else
        {
            while(stack.last().x!=cur_x || stack.last().y!=cur_y)
                stack.pop_back();
        }
    }
    solution=stack;
    path_found=1;

    timePathfind = time.elapsed();
    this->repaint();
}



void Maze::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPen pen;
    pen.setWidth(0);
    pen.setColor(Qt::white);
    painter.setPen(pen);

    int x=0,y=0;
    for(int i=0;i<2*height+1;i++)
    {
        for(int j=0; j<2*width+1;j++)
        {
            if(matrix[i][j]==true)
            {
                painter.setBrush(Qt::black);
                pen.setColor(Qt::black);
                painter.setPen(pen);
            }
            else
            {
                painter.setBrush(Qt::white);
                pen.setColor(Qt::white);
                painter.setPen(pen);
            }
            painter.drawRect(QRect(x,y,10,10));
            x+=10;
        }
        y+=10;
        x=0;
    }
    if(path_found==1)
    {
        int k=solution.size();

        painter.setBrush(Qt::red);
        pen.setColor(Qt::red);
        painter.setPen(pen);

        int temp_x=2*10*(width)-10;
        int temp_y=2*10*(height)-10;
        painter.drawRect(QRect(0,10,10,10));
        painter.drawRect(QRect(2*10*width-10,2*10*height,10,10));

        for(int i=0;i<k;i++)
        {
            x=2*10*solution[k-i-1].x+10;
            y=2*10*solution[k-i-1].y+10;
            painter.drawRect(QRect(x,y,10,10));
            if(i!=0)
            {
                temp_x=(x+temp_x)/2;
                temp_y=(y+temp_y)/2;
                painter.drawRect(QRect(temp_x,temp_y,10,10));
                temp_x=x;
                temp_y=y;
            }
        }
    }
}


