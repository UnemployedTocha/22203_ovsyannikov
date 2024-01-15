#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QWidget>
#include <QFile>
#include <QString>

namespace Ui {
class LeaderBoard;
}

class LeaderBoard : public QWidget
{
    Q_OBJECT

public:
    explicit LeaderBoard(QWidget *parent = nullptr);
    void Update();
    ~LeaderBoard();

private:
    Ui::LeaderBoard *ui;
    unsigned row = 0;
    unsigned column = 3;
    QString path;

    void ProcessLine(const QString& line);
};

#endif // LEADERBOARD_H
