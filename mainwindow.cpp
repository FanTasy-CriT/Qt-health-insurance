#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comptabilite_CURD.h"
#include <QSqlDatabase>
#include <QString>
#include <QDebug>
#include <QTableWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "SMTPClient/email.h"
#include <QAxObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("mybase");
    db.setUserName("haroun");//inserer nom de l'utilisateur
    db.setPassword("123");//inserer mot de passe de cet utilisateur
    db.open();
    intialize_comptabilite();
    ui->table_service->setModel(print_table("services"));
    ui->table_sdf->setModel(print_table("SDF"));
    ui->tableView->setModel(print_table("COMPTABILITE"));
    ui->tableView->setColumnWidth(0, 50);
    ui->lineEdit->hide();
    ui->IDline->hide();
    ui->id_dons->hide();
    ui->label_5->hide();
    loadHistoryFromFile("history.txt");
    displayHistory(ui->history,"history.txt");
   // ui->history->setColumnWidth(0,ui->history->width());
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_metiers_clicked()
{
    ui->comptabilite_2->setCurrentIndex(1);
}

void MainWindow::on_SWITCH_CRUD_clicked()
{
    ui->comptabilite_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_34_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_crud_don_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_crud_don_2_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
    displaystatistiques(ui->graphicsView_services,"SERVICES","type");
}

void MainWindow::on_triupservice_clicked()
{
    ui->table_service->setModel(sortbyup("SERVICES"));
}

void MainWindow::on_tridownservice_clicked()
{
    ui->table_service->setModel(sortbydown("SERVICES"));
}

void MainWindow::on_searchservice_clicked()
{
    ui->table_service->setModel(search_table("SERVICES",ui->searchlineedit->text()));
}


void MainWindow::on_pushButton_15_clicked()
{
    if(ui->stackedWidget_4->currentIndex()==0)ui->stackedWidget_4->setCurrentIndex(1);
    displaystatistiques(ui->graphicsView_3,"SDF","etat");
}

void MainWindow::on_pdf_service_clicked()
{
    generatePdfFile("SERVICES");
}

void MainWindow::on_pushButton_16_clicked()
{
    generatePdfFile("SDF");
}

void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}

void MainWindow::on_search_compt_3_clicked()
{
    ui->table_sdf->setModel(search_table("sdf",ui->searchsdf->text()));
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->table_sdf->setModel(sortbyup("SDF"));
}

void MainWindow::on_pushButton_19_clicked()
{
    ui->table_sdf->setModel(sortbydown("SDF"));
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM services WHERE dater = ?");
    query.addBindValue(date);

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError();
    }
int i=0;
qDebug() << "entered";
    while (query.next()) {
        qDebug()<< "found";
        if(query.value(1).toString()=="Alimentation"){ui->label_14->setText("Alimentation disponible a " + query.value(3).toString());}
        if(query.value(1).toString()=="Sante"){ui->label_14->setText("Medecin disponible a " + query.value(3).toString());}
        // Load the image file
        QImage image("C:\\Users\\FanTasy CriT\\Desktop\\projet\\images\\"+query.value(3).toString()+".png");
        // Scale the image to fit the label
        QImage scaledImage = image.scaled(ui->label_15->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        // Set the image on the label
        ui->label_15->setPixmap(QPixmap::fromImage(image));
        i++;
        // process the row data as needed
    }
    if(i==0){qDebug() << "not found";
    ui->label_15->setPixmap(QPixmap());
    ui->label_14->setText("Aucun alimentation ou medecin trouvee");}

}

void MainWindow::on_pushButton_21_clicked()
{
    generatePdfFile("SERVICES");
}

void MainWindow::on_pushButton_22_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(2);
}

void MainWindow::on_pushButton_23_clicked()
{
    // Create the email object
    Email email = createEmail();

    // Create the SMTPClient
    SMTPClient* client = new SMTPClient("smtp.gmail.com",
                             465);

    // Try to send the email
    client->sendEmail(email);

    QMessageBox::information(this, "Information", "message envoyée");
}

void MainWindow::on_table_sdf_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
        {
                QVariant data = ui->table_sdf->model()->data(index);
                QString id = ui->table_sdf->model()->data(ui->table_sdf->model()->index(index.row(), 0)).toString();
                QString nom = ui->table_sdf->model()->data(ui->table_sdf->model()->index(index.row(), 1)).toString();
                QString prenom = ui->table_sdf->model()->data(ui->table_sdf->model()->index(index.row(), 2)).toString();
                QString date = ui->table_sdf->model()->data(ui->table_sdf->model()->index(index.row(), 3)).toString().left(10);
                QString etat = ui->table_sdf->model()->data(ui->table_sdf->model()->index(index.row(), 4)).toString();
                QString besoin = ui->table_sdf->model()->data(ui->table_sdf->model()->index(index.row(), 5)).toString();
                    //materiel
                    ui->ID_3->setText(id);
                    ui->nom->setText(nom);
                    ui->preno->setText(prenom);
                    QDate dater = QDate::fromString(date, "dd/MM/yyyy");
                    ui->datedenaissance->setDate(dater);
                    if(etat=="Marie")
                    ui->dropdownetat->setCurrentIndex(0);
                    else
                    ui->dropdownetat->setCurrentIndex(1);
                    ui->dropdowsante->setCurrentText(besoin);
        }
}

void MainWindow::on_pushButton_25_clicked()
{
    // Create a new Excel instance
        QAxObject* excel = new QAxObject("Excel.Application");

        // Make Excel visible
        excel->setProperty("Visible", true);

        // Get a pointer to the active workbook
        QAxObject* workbooks = excel->querySubObject("Workbooks");
        QAxObject* workbook = workbooks->querySubObject("Add");

        // Get a pointer to the active worksheet
        QAxObject* sheets = workbook->querySubObject("Sheets");
        QAxObject* worksheet = sheets->querySubObject("Item(int)", 1);

        // Write the data to the worksheet
        QSqlQuery query;
               query.prepare("SELECT * FROM comptabilite");
               query.exec();
               // Write the data to the worksheet
               worksheet->querySubObject("Cells(int,int)", 1, 1)->setProperty("Value", "ID");
               worksheet->querySubObject("Cells(int,int)", 2, 1)->setProperty("Value","Type");
               worksheet->querySubObject("Cells(int,int)", 3, 1)->setProperty("Value", "Price");
               worksheet->querySubObject("Cells(int,int)", 4, 1)->setProperty("Value", "Date");
               worksheet->querySubObject("Cells(int,int)", 6, 1)->setProperty("Value", "Montant Totale Donation");
               worksheet->querySubObject("Cells(int,int)", 7, 1)->setProperty("Value", "Montant Totale Depensée");
               worksheet->querySubObject("Cells(int,int)", 9, 1)->setProperty("Value", "Montant Disponible(sans TVA)");
               worksheet->querySubObject("Cells(int,int)", 10, 1)->setProperty("Value", "Montant Disponible(avec TVA)");
               int row = 2; // Start at row 2 to skip the column headers
               QAxObject* range = worksheet->querySubObject("Columns(int)", 1);
               range->setProperty("ColumnWidth", 3.5 * range->property("ColumnWidth").toDouble());
               QMap<QString, int> totalPrices;
               while (query.next()) {
                   QString type = query.value(1).toString();
                       int price = query.value(2).toInt();

                       if (totalPrices.contains(type)) {
                           totalPrices[type] += price;
                       } else {
                           totalPrices[type] = price;
                       }
                       QString data1 = query.value(0).toString();
                       QString data2 = query.value(1).toString();
                       QString data3 = query.value(2).toString();
                       QDate date = query.value(3).toDate();
                       QString data4 = date.toString("dd/MM/yyyy");
                        worksheet->querySubObject("Cells(int,int)", 1, row)->setProperty("Value", data1);
                        worksheet->querySubObject("Cells(int,int)", 2, row)->setProperty("Value",data2);
                        worksheet->querySubObject("Cells(int,int)", 3, row)->setProperty("Value", data3);
                        worksheet->querySubObject("Cells(int,int)", 4, row)->setProperty("Value", data4);
                        worksheet->querySubObject("Cells(int,int)", 6, 2)->setProperty("Value", totalPrices["recu"]);
                        worksheet->querySubObject("Cells(int,int)", 7, 2)->setProperty("Value",  totalPrices["depenser"]);
                        worksheet->querySubObject("Cells(int,int)", 9, 2)->setProperty("Value", totalPrices["recu"]-totalPrices["depenser"]);
                        worksheet->querySubObject("Cells(int,int)", 10, 2)->setProperty("Value", (totalPrices["recu"]-totalPrices["depenser"]) - (totalPrices["recu"]-totalPrices["depenser"])*7/100 );


                   row++;
               }

        // Save and close the workbook
        workbook->dynamicCall("SaveAs(const QString&)", "C:\\Users\\FanTasy CriT\\Desktop\\projet\\file.xlsx");
        //workbook->dynamicCall("Close()");

        // Quit Excel
        //excel->dynamicCall("Quit()");
}
