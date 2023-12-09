#ifndef GAMECARDWIDGET_H
#define GAMECARDWIDGET_H

#include <QWidget>
#include "game.h"

class GameCardWidget : public QWidget {
    Q_OBJECT

public:
    GameCardWidget(Game game, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override {
        Q_UNUSED(event);
        emit widgetClicked();
    }

signals:
    void widgetClicked();
};

#endif // GAMECARDWIDGET_H
