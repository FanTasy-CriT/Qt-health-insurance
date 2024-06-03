#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlQueryModel>
#include <QMainWindow>
#include <QTableView>
#include <comptabilite_CURD.h>
#include <QGraphicsView>
#include "SMTPClient/email.h"
#include "SMTPClient/emailaddress.h"
#include <qstandarditemmodel.h>
#include "SMTPClient/smtpclient.h"
#include <QHeaderView>
#include <QFile>
namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    struct HistoryEntry {
        QString User;
        QString DateString;
        QString Type;
        QString PriceString;
        QString Description;
    };

    QVector<HistoryEntry> history;

    void addToHistory(const QString& user, const QString& dateString, const QString& type, const QString& priceString, const QString& description) {
        HistoryEntry entry;
        entry.User = user;
        entry.DateString = dateString;
        entry.Type = type;
        entry.PriceString = priceString;
        entry.Description = description;
        history.append(entry);
    }

    void saveHistoryToFile(const QString& fileName) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (const HistoryEntry& entry : history) {
                out << entry.User << "," << entry.DateString << "," << entry.Type << "," << entry.PriceString << "," << entry.Description << "\n";
            }
            file.close();
        }
    }

    void loadHistoryFromFile(const QString& fileName) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList fields = line.split(",");
                if (fields.size() == 5) {
                    HistoryEntry entry;
                    entry.User = fields.at(0);
                    entry.DateString = fields.at(1);
                    entry.Type = fields.at(2);
                    entry.PriceString = fields.at(3);
                    entry.Description = fields.at(4);
                    history.append(entry);
                }
            }
            file.close();
        }
    }

    void displayHistory(QTableView* tableView, const QString& textFile) {
        QStandardItemModel* model = new QStandardItemModel();
        model->setColumnCount(1);
        model->setHeaderData(0, Qt::Horizontal, "");
        loadHistoryFromFile(textFile);
        for (const HistoryEntry& entry : history) {
            QString phrase;
            // generate customized phrase based on the entry
            // for example:
            if(entry.Description=="deleted")
            phrase = QString("%1 a supprimer le collumn avec le id %3 :: %2").arg(entry.User).arg(entry.Description).arg(entry.PriceString);
            else
            phrase = QString("%1 a ajouté avec une prix de %4 dans le %3 :: %2").arg(entry.User).arg(entry.Description).arg(entry.DateString).arg(entry.PriceString);
            QList<QStandardItem*> rowItems;
            rowItems.append(new QStandardItem(phrase));
            model->appendRow(rowItems);
        }
        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
        tableView->setColumnWidth(0, 600);
        tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }


private slots:
    //related to comptabilite
    //TREAT WITH CAUTION
    QString control_saisie();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void intialize_comptabilite();

    //void on_pushButton_8_clicked();

    QSqlQueryModel* print_table(QString table);

    //NEXT TASK GOES HERE

    void on_delete_2_clicked();

    void on_Add_clicked();

    void on_Dropdown_currentTextChanged(const QString &arg1);

    void on_pushButton_7_clicked();


    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_Edit_clicked();

    void on_delete_3_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);
    
    void on_pushButton_2_clicked();

    void on_Add_2_clicked();

    void on_Edit_2_clicked();

    void on_pushButton_5_clicked();

    void on_Edit_3_clicked();

    void on_Add_3_clicked();

    void on_delete_4_clicked();

    void on_table_service_doubleClicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_add_don_clicked();

    void on_edit_don_clicked();

    void on_delte_don_clicked();

    void on_search_compt_clicked();

    QSqlQueryModel * search_table(QString table ,QString search);

    void on_pushButton_11_clicked();

    QSqlQueryModel * sortbyup(QString table);

    QSqlQueryModel * sortbydown(QString table);

    void on_pushButton_9_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_search_compt_2_clicked();

    void on_table_don_doubleClicked(const QModelIndex &index);

    void on_PDF_clicked();

    void on_pushButton_34_clicked();

    void on_metiers_clicked();

    void on_SWITCH_CRUD_clicked();

    void on_pdf_don_clicked();

    void generatePdfFile(QString table);

    void on_crud_don_clicked();

    void displaystatistiques(QGraphicsView* view,QString table,QString collumn);

    void on_crud_don_2_clicked();

    void on_pushButton_14_clicked();

    void on_triupservice_clicked();

    void on_tridownservice_clicked();

    void on_searchservice_clicked();

    void on_pushButton_15_clicked();

    void on_pdf_service_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_search_compt_3_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    Email createEmail();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_table_sdf_doubleClicked(const QModelIndex &index);

    void on_pushButton_25_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
