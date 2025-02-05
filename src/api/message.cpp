#include "message.h"

Message::Message(const QString &text, bool isUser, QObject *parent)
    : QObject(parent), m_text(text), m_isUser(isUser)
{
}

QString Message::text() const
{
    return m_text;
}

void Message::setText(const QString &text)
{
    if (m_text != text) {
        m_text = text;
        emit textChanged();
    }
}

bool Message::isUser() const
{
    return m_isUser;
}

void Message::setIsUser(bool isUser)
{
    if (m_isUser != isUser) {
        m_isUser = isUser;
        emit isUserChanged();
    }
}