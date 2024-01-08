#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include <QDir>

const QString pathToUIElements = QDir::currentPath() + "/resources/uielements/";
const QString pathToGamesImages = QDir::currentPath() + "/resources/gamesImages/";
const QString pathToProfilesImages = QDir::currentPath() + "/resources/profilesImages/";
const QString pathToPayments = QDir::currentPath() + "resources/payments/";
const QString backgroundColor = "rgb(18, 18, 18)";
const QString selectedBackgroundColor = "rgb(25, 25, 25)";
const QString mainTextColor = "rgb(200, 200, 200)";
const QString shadedTextColor = "rgb(150, 150, 150)";
const int sizeOfGameCard[] = {330, 270};
const int gamesGridNumberOfColumns = 3;

#endif // CONFIG_H
