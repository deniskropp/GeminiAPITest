#include "messagemodel.h"

MessageModel::MessageModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int MessageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_messages.size();
}

QVariant MessageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_messages.size())
        return QVariant();

    const Message *message = m_messages.at(index.row());

    switch (role) {
    case TextRole:
        return message->text();
    case IsUserRole:
        return message->isUser();
    default:
        return QVariant();
    }
}

bool MessageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= m_messages.size())
        return false;

    Message *message = m_messages.at(index.row());
    bool changed = false;

    switch (role) {
    case TextRole:
        if (message->text() != value.toString()) {
            message->setText(value.toString());
            changed = true;
        }
        break;
    case IsUserRole:
        if (message->isUser() != value.toBool()) {
            message->setIsUser(value.toBool());
            changed = true;
        }
        break;
    default:
        return false;
    }

    if (changed)
        emit dataChanged(index, index, QVector<int>() << role);

    return changed;
}

QHash<int, QByteArray> MessageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TextRole] = "text";
    roles[IsUserRole] = "isUser";
    return roles;
}

void MessageModel::addMessage(const QString &text, bool isUser)
{
    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
    m_messages.append(new Message(text, isUser, this));
    endInsertRows();
}

void MessageModel::appendToLastMessage(const QString &text)
{
    if (!m_messages.isEmpty()) {
        QModelIndex lastIndex = index(m_messages.size() - 1);
        setData(lastIndex, data(lastIndex, TextRole).toString() + text, TextRole);
    }
}