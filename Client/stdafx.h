#include <vector>
#include <deque>
#include <queue>
#include <optional>

#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QThread>
#include <QTimer>

#include <QStackedLayout>
#include <QMessageBox>
#include <QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QAbstractListModel>
#include <QtWebSockets/QWebSocket>

#include <QUrl>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QtQml/QQmlContext>

#if defined(_DEBUG)

#define ASSERT(X) _ASSERT(X)
#define VERIFY(X) _ASSERT(X)

#else

#define ASSERT(X)
#define VERIFY(X) (X)

#endif