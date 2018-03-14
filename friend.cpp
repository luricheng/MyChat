#include "friend.h"

Friend::Friend(unsigned int friendId, QString groupName){
    this->friendId = friendId;
    this->groupName = groupName;
}

unsigned int Friend::getFriendId()const{
    return friendId;
}

QString Friend::getGroupName()const{
    return groupName;
}
