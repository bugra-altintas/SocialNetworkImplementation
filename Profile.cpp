#include "Profile.h"
// default constructor
Profile::Profile() {

}

// A constructor constructs a Profile object with given parameters
Profile::Profile(const std::string &firstname, const std::string &lastname, const std::string &email) {
    this->firstname = firstname;
    this->lastname = lastname;
    this->email = email;
}

// Getters
const std::string &Profile::getFirstname() const {
    return this->firstname;
}

const std::string &Profile::getLastname() const {
    return this->lastname;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

LinkedList<Profile *> &Profile::getFriends() {
    return this->friends;
}

LinkedList<Post *> &Profile::getLikes() {
    return this->likes;
}

LinkedList<Post *> &Profile::getPosts() {
    return this->posts;
}

// Setters
void Profile::setFirstname(const std::string &firstname) {
    this->firstname = firstname;
}

void Profile::setLastname(const std::string &lastname) {
    this->lastname = lastname;
}

void Profile::setEmail(const std::string &email) {
    this->email = email;
}

// A function adds a node with given Profile pointer to the friends linked list of user.
void Profile::addFriend(Profile *profile) {
    this->friends.insertAtTheTail(profile);
}

// A function adds a node with given Post pointer to the likes linked list of user.
void Profile::addLike(Post *post) {
    this->likes.insertAtTheTail(post);
}

// A function adds a node given Post pointer to the posts linked list of user.
void Profile::addPost(Post *post) {
    this->posts.insertAtTheTail(post);
}

// A function removes a node with given Profile pointer from the friends linked list of user.
void Profile::dropFriend(Profile *profile) {
    this->friends.removeNode(profile);
}

// A function removes a node with given Post pointer from the likes linked list of user.
void Profile::dropLike(Post *post) {
    this->likes.removeNode(post);
}

// A function removes a node with given Post pointer from the posts linked list of user.
void Profile::dropPost(Post *post) {
    this->posts.removeNode(post);
}


// Overloading stream operator to print a Profile object
std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "firstname: " << profile.firstname;
    os << " lastname: " << profile.lastname;
    os << " email: " << profile.email;
	
    os << " friends: [";
    Node<Profile *> *f = profile.friends.getFirstNode();
    while (f) {
        os << f->data->getEmail();
        if (f->next) os << ", ";
        f = f->next;
    }
    os << "]";

    os << " likes: [";
    Node<Post *> *l = profile.likes.getFirstNode();
    while (l) {
        os << l->data->getPostId();
        if (l->next) os << ", ";
        l = l->next;
    }
    os << "]";

    os << " posts: [";
    Node<Post *> *p = profile.posts.getFirstNode();
    while (p) {
        os << p->data->getPostId();
        if (p->next) os << ", ";
        p = p->next;
    }
    os << "]";

    return os;
}

// Overloading == operator to compare the user with given Profile object.
bool Profile::operator==(const Profile &rhs) const {
    if((this->firstname == rhs.getFirstname()) && (this->lastname == rhs.getLastname()) && (this->email == rhs.getEmail())){
		return true;
	}
	return false;
}

// Overloading != operator to compare the user with given Profile object.
bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

// Overloading < operator to compare the user with given Profile object, by their lastname's and firstname's lexicographically.
bool Profile::operator<(const Profile &rhs) const {
	if(this->lastname < rhs.getLastname()){
		return true;
	}
	else if(this->lastname == rhs.getLastname()){
		if(this->firstname < rhs.getFirstname()){
			return true;
		}
	}
	return false;
}

// Overloading > operator to compare the user with given Profile object, by their lastname's and firstname's lexicographically.
bool Profile::operator>(const Profile &rhs) const {
    return rhs < *this;
}

// Overloading <= operator to compare the user with given Profile object, by their lastname's and firstname's lexicographically.
bool Profile::operator<=(const Profile &rhs) const {
    return !(rhs < *this);
}

// Overloading >= operator to compare the user with given Profile object, by their lastname's and firstname's lexicographically.
bool Profile::operator>=(const Profile &rhs) const {
    return !(*this < rhs);
}
