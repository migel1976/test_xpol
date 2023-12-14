#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <unistd.h>
#include <QThread>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>



#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
// #include <QTcpSocket>
// #include <QtNetwork>


#define SOCKET_ERROR (-1)
#define INVALID_SOCKET (-1)

typedef int SOCKET;

#include <unistd.h>
#define COMMAND_ERROR (1)
#define NO_CMD_ERROR (0)

#define SCPI_PORT 5025
#define INPUT_BUF_SIZE (64*601*2)


QString host="localhost";
QString dbname="xpol";
QString pass="";
QString username="postgres";
DbManager dbM(host, dbname, pass, username);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plot=ui->qwtPlot;
    defaultChart=new DefaultChart(plot);
    QwtPlot* chart=defaultChart->getPlot();
    zoomer = new Zoomer(chart->canvas());

    ConnectReport();
}

void MainWindow::ConnectReport(){
    model=new QSqlTableModel(this);
    model->setTable("report");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::RefreshReportModel(){
    model->select();
}
void MainWindow::InsertData(QString name, int cf){

    QString val;
    QFile file;
    // file.setFileName("/home/mike/copol.json");
    file.setFileName("/home/mike/trace.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val=file.readAll();
    file.close();
    // qWarning()<<val;

    QJsonDocument copol=QJsonDocument::fromJson(val.toUtf8());
    // dbM.addReport(name, cf, copol);
    dbM.addReport(name, cf, glJsonDoc);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAddReport_clicked()
{

    // qWarning()<<"WARNING: add button";
    // insertreport *newT=new insertreport(this);
    // newT->setAttribute(Qt::WA_DeleteOnClose);
    // connect(newT,SIGNAL(destroyed(QObject*)), SLOT(RefreshReportModel()));
    // newT->show();
}

void MainWindow::on_btnDeleteReport_clicked()
{
    dbM.removeReport(glRow);
    model->select();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int rowId=index.row();
    QModelIndex idx=model->index(rowId,0);
    glRow =idx.data().toString();
    qWarning()<<glRow;
    QModelIndex idxCopol=model->index(rowId,3);
    QString val=idxCopol.data().toString();
    qWarning()<<"val is "<<val;
    int lend=8190;
    double *dcopol=ReadJSONDB(val, lend);
    double cf=11200;
    double span=10;
    double startFreq=cf-span/2;
    double freq[lend];

    for(int i=0; i<lend;i++){
        // double f=freq[i]=startFreq+i*span/lend-1;
        double f=startFreq+i*span/lend-1;
        freq[i]=f;
    }

    defaultChart=new DefaultChart(plot);
    QwtPlot* chart=defaultChart->getPlot();
    chartXpol=new ChartXpol(chart);
    chartXpol->showData(freq, dcopol, dcopol, lend);
    delete []dcopol;
    SetZoomer(chart);
}

void MainWindow::SetZoomer(QwtPlot *chart){
    if(zoomer!=0){
            delete zoomer;
    }
    zoomer = new Zoomer(chart->canvas());
    // zoomer->setAxes(QwtPlot::xBottom, QwtPlot::yLeft);
}

double* MainWindow::ReadJSONDB(QString val, int &lend){
        QJsonDocument d=QJsonDocument::fromJson(val.toUtf8());
        QJsonObject sett2=d.object();
        QJsonValue value=sett2.value("amp");
        QJsonObject obj=value.toObject();
        QJsonArray arr=value.toArray();
        int len=arr.size();
        lend=len;
        double *copol=new double[len];
        for(int count=0;count<len; count++){
                QString itemStr=arr[count].toString();
                double item=itemStr.toDouble();
                copol[count]=item;
                // qWarning<<copol[count]<<"\n";
        }
        return copol;
}

void MainWindow::on_btnLoadJSON_clicked()
{

    QString val;
    QFile file;
    // file.setFileName("/home/mike/copol_correct.json");
    file.setFileName("/home/mike/trace.json");
    // file.setFileName("~/trace.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val=file.readAll();
    file.close();
    // qWarning()<<val;

    QJsonDocument d=QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2=d.object();
    QJsonValue value=sett2.value("amp");
    QJsonObject obj=value.toObject();
    QJsonArray arr=value.toArray();
    qWarning()<<"arr "<<arr;
    int len=arr.size();
    double copol[len];
    for(int count=0;count<len; count++){
        // double item=arr[count].toDouble();
        QString item=arr[count].toString();
        qWarning()<<"item "<<item;
        // double item=item.toDouble();
        // copol[count]=item;
        copol[count]=item.toDouble();
    }
    double cf=12200;
    double span=1;
    double startFreq=cf-span/2;
    double freq[len];

    for(int i=0; i<len;i++){
            // double f=freq[i]=startFreq+i*span/len-1;
            double f=startFreq+i*span/len-1;
            freq[i]=f;
            qWarning()<<"freq["<<i<<"]"<<freq[i];
            qWarning()<<"amp["<<i<<"]"<<copol[i];
    }

    // defaultChart=new DefaultChart(plot);
    // QwtPlot* chart=defaultChart->getPlot();
    // chartXpol=new ChartXpol(chart);
    // chartXpol->showData(freq, copol, copol, len);
    // SetZoomer(chart);

}

char* recv_line(SOCKET sock, char* result, int maxLength){
    QMessageBox msg;
    FILE *instFile;
    instFile=fdopen(sock,"r+");
    if(instFile==NULL){
       msg.setText("unable to create FILE * structure :");
       exit(2);
    }
    return fgets(result, maxLength, instFile);
}

// int MainWindow::commandInstrument(SOCKET sock, const char *command){
int commandInstrument(SOCKET sock, const char *command){
    int count;
    if(strchr(command,'\n')==NULL){
            fprintf(stderr,"Warning: missing newline on command %s\n",
               command);
    }
    count= send(sock, command, strlen(command), 0);
    if(count==SOCKET_ERROR){
        return COMMAND_ERROR;
    }
    return NO_CMD_ERROR;
}

long queryInstrument(SOCKET sock, const char *command, char *result, size_t maxLength){
// long MainWindow::queryInstrument(SOCKET sock, const char *command, char *result, size_t maxLength){
   long ch;
   // char tmp_buf[8];
   char tmp_buf[128];
   long resultBytes=0;
   int command_err;
   int count;

   command_err=commandInstrument(sock, command);
   if(command_err) return COMMAND_ERROR;

   count = recv(sock, tmp_buf, 1, 0);
   ch=tmp_buf[0];
   // if((count<1)||(ch==EOF) || (ch='\n')){
       // *result ='\0';
       // return 0;
   // }
   do{
       if(ch=='#')
       {
           long numDigits;
           long numBytes=0;
           count=recv(sock, tmp_buf, 1, 0);
           ch=tmp_buf[0];
           if((count<1)||(ch==EOF)) break;
           if(ch<'0' || ch >'9') break;
           numDigits=ch-'0';

           if(numDigits){
               count=recv(sock, result, (int)numDigits, 0);
               result[count]=0;
               numBytes=atoi(result);
           }
           if(numBytes)
           {
                   resultBytes=0;
                   do{
                           int rcount;
                           rcount=recv(sock, result, (int)numBytes, 0);
                           resultBytes+=rcount;
                           result+=rcount;
                   }while(resultBytes<numBytes);
                   if(resultBytes==numBytes)
                   {
                           char junk;
                           count = recv(sock, &junk, 1, 0);
                   }
           }
           else{
               do{
                           if(recv_line(sock, result, maxLength)==NULL) break;
                           if(strlen(result)==1 && *result == '\n') break;
                           resultBytes+=strlen(result);
                           result+=strlen(result);
               }while(1);
                   // QMessageBox msg;
                   // msg.setText("get line response");
           }
       }
       else{
               *result = (char)ch;
              if(recv_line(sock, result+1, maxLength-1)==NULL) return 0;
              resultBytes=strlen(result);
              if(result[resultBytes-1]=='n') resultBytes -=1;
              result[resultBytes]='\0';
       }
   }while(0);
return resultBytes;
}


SOCKET openSocket(const char *hostname, int portNumber){

   struct hostent *hostPtr;
   struct sockaddr_in peeraddr_in;
   SOCKET s;

   memset(&peeraddr_in, 0, sizeof(struct sockaddr_in));

   hostPtr=gethostbyname(hostname);
   if(hostPtr==NULL){
      fprintf(stderr,"unable to connect '%s'", hostname);
      return INVALID_SOCKET;
   }

   s=socket(AF_INET, SOCK_STREAM,0);
   if(s==INVALID_SOCKET){
       fprintf(stderr,"unable to create socket to '%s': %s\n",
               hostname, strerror(errno));
       return INVALID_SOCKET;
   }
   memcpy(&peeraddr_in.sin_addr, hostPtr->h_addr, hostPtr->h_length);
   peeraddr_in.sin_family=AF_INET;
   peeraddr_in.sin_port=htons((unsigned short)portNumber);

   if(connect(s, (const struct sockaddr*) &peeraddr_in,
              sizeof(struct sockaddr_in))==SOCKET_ERROR)
   {
       fprintf(stderr,"unable to create socket to '%s': %s\n",
               hostname, strerror(errno));
       return INVALID_SOCKET;
   }
   return s;
}

void MainWindow::on_btnGetSpectr_clicked()
{

    // QTcpSocket instSock=openSocket("10.5.129.42", SCPI_PORT);
    SOCKET instSock=openSocket("10.5.129.42", SCPI_PORT);
    // instSock=openSocket("10.5.129.42", SCPI_PORT);
    if(instSock==INVALID_SOCKET){
        msgBox.setText("Unable open socket");
        msgBox.exec();
    }else{
        // QString strSpan=ui->txtSpan->text();
        std::string span="";
        const char* charSpan=span.c_str();
        // span=":INIT:CONT 0;\n";
        // charSpan=span.c_str();
        // commandInstrument(instSock, charSpan );
        // span=":FORM REAL,64;\n";
        // charSpan=span.c_str();
        // commandInstrument(instSock, charSpan );
        // span=":FORM:BORD SWAP\n";
        // charSpan=span.c_str();
        // commandInstrument(instSock, charSpan );
        span=":TRAC:DATA? TRACE1\n";
        charSpan=span.c_str();
        char *charBuf=(char*)malloc(INPUT_BUF_SIZE);
        long bufBytes;
        bufBytes=queryInstrument(instSock, charSpan, charBuf, INPUT_BUF_SIZE);
        int len=bufBytes;
        double result[len];
        memcpy(&result, charBuf, len);
        int trueLen=len/8;
        int count=0;
        double res[trueLen];
        // glCopol=malloc(sizeof(double)*trueLen);
        // double *glCopol=new double[trueLen];
        glCopol=new double[trueLen];
        // glCopol[trueLen];
        do{
                res[count]=result[count];
                double tmp=result[count];
                glCopol[count]=tmp;
                count++;
        }while(count<trueLen);
        span=":INIT:CONT 1;\n";
        commandInstrument(instSock, charSpan );
        // memcpy(glCopol, res, trueLen);


        double cf=11200;
        double sp=10;
        double startFreq=cf-sp/2;
        double freq[trueLen];

        // double *glFreq=new double[trueLen];
        glFreq=new double[trueLen];
        for(int i=0; i<trueLen;i++){
            double f=freq[i]=startFreq+i*sp/len-1;
            freq[i]=f;
            glFreq[i]=f;

            // printf("freq d = %f count %d\n",freq[i], i);
        }
        // memcpy(glFreq, freq, trueLen);

        // chartXpol->showData(freq, res, res, trueLen);
        glLen=trueLen;
        glCF=cf;
        chartXpol->showData(glFreq, glCopol, glCopol, trueLen);
        SetZoomer(chartXpol);
        // QTcpSocket.close();

        // closesocket(instSock);
        // fclose(instSock);
        }
}


void MainWindow::on_btnSaveTrace_clicked()
{

    WriteJSONDB();
    // qWarning()<<"WARNING: add button";
    insertreport *newT=new insertreport(this);
    newT->setAttribute(Qt::WA_DeleteOnClose);
    connect(newT,SIGNAL(destroyed(QObject*)), SLOT(RefreshReportModel()));
    newT->show();
}

void MainWindow::WriteJSONDB(){
        QJsonArray arr;
        int i=0;
        while(i<glLen){
                arr.append(QString::number(glCopol[i]));
                i++;
        }
        QJsonObject obj;
        obj["amp"]=arr;
        glJsonDoc=QJsonDocument(obj);
        // QJsonDocument d=QJsonDocument(obj);
        // PGresult *res=NULL;
        // const char conninfo[]= "postgresql://postgres@localhost?port=5432&dbname=xpol";
        // PGconn *conn=PQconnectdb(conninfo);
        // if(PQstatus(conn)==CONNECTION_OK){
                // const char sql[]="insert into report (copol) values ($1);";
                // int nParams=1;
                // QByteArray val=d.toJson();
                // const char *const paramValues[]={val};
                // const int paramLengths[]={val.size()};
                // const int paramFormats[]={0};
                // int resultFormat=0;
                // res=PQexecParams(conn, sql, nParams, NULL,
                                 // paramValues, NULL,
                                 // NULL, resultFormat);
                // if(PQresultStatus(res)!=PGRES_COMMAND_OK){
                        // QMessageBox msg;
                        // msg.setText("add json trace failed");
                        // msg.exec();
                // }else{
                        // QMessageBox msg;
                        // msg.setText("Add json trace success" );
                        // msg.exec();
                        // SelectXpol();
                // }
        // }
}
