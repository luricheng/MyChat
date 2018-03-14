#ifndef FRIEND_H
#define FRIEND_H

#include<QString>

class Friend
{
public:
    Friend(unsigned int friendId, QString groupName);
    unsigned int getFriendId()const;
    QString getGroupName()const;
private:
    unsigned int friendId;
    QString groupName;
};

#endif // FRIEND_H
