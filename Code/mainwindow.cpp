#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QRgb>
#include <QPixmap>
#include <QColor>
#include <QBitmap>
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   x=y=di=count=0;
    for(int i=0;i<1000;i++)myx[i]=myy[i]=mya[i]=0;
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{


    int r=ui->lineEdit->text().toInt();
    for(int i=count;i<100;i++)
    {
        myx[i]=-100+i;
        myy[i]=r;
        count++;

    }


    x=0,y=r;
    int del,deld;
    di=2-2*r;
    int limit=0;
    while(y>=limit)
    {
        if(x<=y)draw();

        if(di<0)
        {
            del=2*di+2*y-1;
            if(del<=0)
            {
                mh();
            }
            else
            {
                md();
            }
        }
        else if(di>0)
        {
            deld=2*di+2*x-1;
            if(deld<=0)
            {
                mv();
            }
            else
            {
                md();
            }
        }
        else
        {
            md();
        }
    }

     qDebug() << myx[count] << "," << myy[count] <<" ,count"<< count;
    for(float lol=0;lol<(float)(3*count)/2.0;lol++)
    {   int i=lol;
        myx[i+count]=myy[count-i];
        myy[i+count]=myx[count-i];
    }
    count*=2;
    int rem=count;
    for(int i=count;i<200;i++)
    {
        myx[i]=myx[count-1];
        myy[i]=myy[count-1]+(-i+count);
    }

    anticipation();
    int x1=300,y1=300;
       QImage image1(500,500,QImage::Format_ARGB32);
       QRgb colour1=qRgb(20,20,20);
       QRgb white=qRgb(255,255,255);
       QRgb black=qRgb(0,0,0);
        image1.fill(white);

    QString ans1="",ans2="",ans3="";
    for(int j=0;j<300;j++)
    {
        if(j<100)
        ans1+= "x:"+QString::number(myx[j])+" y:"+ QString::number(myy[j])+" anticipation"+QString::number(mya[j])+"\n";
        else if(myx[j]<r)
        ans2+= "x:"+QString::number(myx[j])+" y:"+ QString::number(myy[j])+" anticipation"+QString::number(mya[j])+"\n";
        else
        ans3+= "x:"+QString::number(myx[j])+" y:"+ QString::number(myy[j])+" anticipation"+QString::number(mya[j])+"\n";


        qDebug() << myx[j] << "," << myy[j] <<" ,anti"<< mya[j];
        image1.setPixel(x1+myx[j],y1+myy[j],black);
        ui->label->setPixmap(QBitmap::fromImage(image1));

    }
    for(int i=0;i<100;i++)
    {       image1.setPixel(x1,y1+i,black);
           image1.setPixel(x1+i,y1+i,black);
           image1.setPixel(x1+i,y1,black);
    }
     ui->label->setPixmap(QBitmap::fromImage(image1));
    ui->textEdit->setText(ans1);
    ui->textEdit_2->setText(ans2);
    ui->textEdit_3->setText(ans3);



}
void MainWindow::mh()
{
    x=x+1;
    di=di+2*x+1;
}
void MainWindow::mv()
{
    y=y-1;
    di=di+2*y+1;
}

void MainWindow::md()
{
    x=x+1;
    y=y-1;
    di=di+2*x-2*y+2;
}
void MainWindow::draw()
{   int x1=200,y1=200;
    QImage image(500,500,QImage::Format_ARGB32);
    QRgb colour=qRgb(255,255,255);
    myx[count]=x;
    myy[count]=y;
    qDebug() << x << "," << y <<" ,"<< di;
    //image.setPixel(x1+x,y1+y,colour);
    //image.setPixel(x1-x,y1+y,colour);
    //image.setPixel(x1+x,y1-y,colour);
    //image.setPixel(x1-x,y1-y,colour);
    //image.setPixel(x1+y,y1+x,colour);
    //image.setPixel(x1-y,y1+x,colour);
   // image.setPixel(x1+y,y1-x,colour);
  //  image.setPixel(x1-y,y1-x,colour);
    count++;
   // ui->label->setPixmap(QBitmap::fromImage(image));
}

void MainWindow::anticipation()
{   float anti=0;
    int off=1;
    for(int c=0;c<1000;c++)
    {
        if(myy[c]>0 && myy[c+off]>0)
        {
            anti= anti + (float)(myy[c+off]-myy[c])/1.6;
        }
        else if(myy[c]<0 && myy[c+off]<0)
        {
            anti= anti + (float)(myy[c]-myy[c+off])/1.6;
        }
        else if(myy[c]<0 && myy[c+off]>0)
        {
            if(-myy[c]>myy[c+off])
            {
                anti= anti + (float)(myy[c]-myy[c+off])/1.6;
            }
            else
            {
                anti= anti + (float)(myy[c+off]-myy[c])/1.6;
            }
        }
        else if(myy[c]>0 && myy[c+off]<0)
        {
            if(myy[c]>(-myy[c+off]))
            {
                anti= anti + (float)(myy[c+off]-myy[c])/1.6;
            }
            else
            {
                anti= anti + (float)(myy[c]-myy[c+off])/1.6;
            }
        }
        mya[c]=anti;

    }
}

