#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QAbstractListModel>
#include "message.h"

class MessageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        TextRole = Qt::UserRole + 1,
        IsUserRole
    };

    explicit MessageModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addMessage(const QString &text, bool isUser);
    Q_INVOKABLE void appendToLastMessage(const QString &text);

private:
    QList<Message*> m_messages;
};

#endif // MESSAGEMODEL_H