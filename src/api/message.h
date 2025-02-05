#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(bool isUser READ isUser WRITE setIsUser NOTIFY isUserChanged)

public:
    explicit Message(const QString &text, bool isUser, QObject *parent = nullptr);

    QString text() const;
    void setText(const QString &text);

    bool isUser() const;
    void setIsUser(bool isUser);

signals:
    void textChanged();
    void isUserChanged();

private:
    QString m_text;
    bool m_isUser;
};

#endif // MESSAGE_H