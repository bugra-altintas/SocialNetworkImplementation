#include "Post.h"
// default constructor
Post::Post() {

}

// A constructor constructs a Post object with given message.
Post::Post(const std::string &message) {
    static int postId = 1;

    this->message = message;
    this->postId = postId;

    postId += 1;
}

// Getters
const std::string &Post::getMessage() const {
    return this->message;
}

int Post::getPostId() const {
    return this->postId;
}
// Setters
void Post::setMessage(const std::string &message) {
    this->message = message;
}

void Post::setPostId(int postId) {
    this->postId = postId;
}

// Overloading stream operator to print a Post object.
std::ostream &operator<<(std::ostream &os, const Post &post) {
    os << "message: " << post.message;
    os << " postId: " << post.postId;
    return os;
}

// Overloading == operator to compare the post with given Post object, by comparing message and postId.
bool Post::operator==(const Post &rhs) const {
    return ((this->message == rhs.getMessage()) && (this->postId == rhs.getPostId()));
}

// Overloading != operator to compare the post with given Post object, by comparing message and postId.
bool Post::operator!=(const Post &rhs) const {
    return !(rhs == *this);
}

// Overloading < operator to compare the post with given Post object, by their postId's.
bool Post::operator<(const Post &rhs) const {
    return (this->postId < rhs.getPostId());
}

// Overloading > operator to compare the post with given Post object, by their postId's.
bool Post::operator>(const Post &rhs) const {
    return rhs < *this;
}

// Overloading <= operator to compare the post with given Post object, by their postId's.
bool Post::operator<=(const Post &rhs) const {
    return !(rhs < *this);
}

// Overloading >= operator to compare the post with given Post object, by their postId's.
bool Post::operator>=(const Post &rhs) const {
    return !(*this < rhs);
}
