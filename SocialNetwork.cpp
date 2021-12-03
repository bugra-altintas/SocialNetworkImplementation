#include "SocialNetwork.h"

#include <iostream>
using namespace std;
SocialNetwork::SocialNetwork() {

}

void SocialNetwork::addProfile(const std::string &firstname, const std::string &lastname, const std::string &email) {
	Profile newProfile(firstname,lastname,email);
	profiles.insertSorted(newProfile);
}

void SocialNetwork::addPost(const std::string &message, const std::string &email) {
	Node<Profile> *curr = profiles.getFirstNode();
	while(curr->data.getEmail() != email) curr = curr->next; 
	Post newPost(message);
	posts.insertAtTheTail(newPost);
	Node<Post> *curr1 = posts.getNode(newPost);
	Post *post = &(curr1->data);
	curr->data.addPost(post);
}

void SocialNetwork::deleteProfile(const std::string &email) {
	Node<Profile> *curr = profiles.getFirstNode();
	while(curr != nullptr && curr->data.getEmail() != email) curr = curr->next;
	if(!curr) return;
	Profile *user = &(curr->data);
	// deleting the user from its friends' list of friends (works)
	Node<Profile*> *fr = user->getFriends().getFirstNode();
	while(fr){
		fr->data->dropFriend(user);
		fr = fr->next;
	}
	
	//deleting the user's posts from other users' list of likes(works)
	Node<Post*> *post = user->getPosts().getFirstNode();
	Node<Profile> *prof = profiles.getFirstNode();
	while(prof){
		while(post){
			prof->data.dropLike(post->data);
			post = post->next;
		}
		post = user->getPosts().getFirstNode();
		prof = prof->next;
	}
	//deleting the user's posts from SocialNetwork::posts
	post = user->getPosts().getFirstNode();
	Node<Post> *postnode;
	post = user->getPosts().getFirstNode();
	while(post){
		postnode = posts.getFirstNode();
		while(postnode){
			if(*(post->data) == (postnode->data)){
				Node<Post> *currpost;
				currpost = postnode;
				postnode = postnode->next;
				posts.removeNode(currpost);
				break;
			}
			else{
				postnode = postnode->next;
			}
		}
		post = post->next;
	}
	
	
	//deleting the content of the profile object(works)
	user->getPosts().removeAllNodes();
	user->getFriends().removeAllNodes();
	user->getLikes().removeAllNodes();
	//deleting the profile from social network(works)
	profiles.removeNode(curr);
	
	
}

void SocialNetwork::makeFriends(const std::string &email1, const std::string &email2) {
	Node<Profile> *curr1 = profiles.getFirstNode();
	while(curr1 != nullptr && curr1->data.getEmail() != email1) curr1 = curr1->next;
	if(!curr1) return;
	Profile *user1 = &(curr1->data);
	Node<Profile> *curr2 = profiles.getFirstNode();
	while(curr2 != nullptr && curr2->data.getEmail() != email2) curr2 = curr2->next;
	if(!curr2) return;
	Profile *user2 = &(curr2->data);
	curr1->data.addFriend(user2);
	curr2->data.addFriend(user1);
	
}

void SocialNetwork::likePost(int postId, const std::string &email) {
	Node<Post> *curr = posts.getFirstNode();
	while(curr != nullptr && curr->data.getPostId() != postId) curr = curr->next;
	Node<Profile> *curr1 = profiles.getFirstNode();
	while(curr1 != nullptr && curr1->data.getEmail() != email) curr1 = curr1->next;
	if(curr == nullptr || curr1 == nullptr) return;
	curr1->data.addLike(&(curr->data));
	
}
void SocialNetwork::unlikePost(int postId, const std::string &email) {
	Node<Post> *curr = posts.getFirstNode();
	while(curr->data.getPostId() != postId) curr = curr->next;
	if(!curr) return; 
	Post *post = &(curr->data);
	Node<Profile> *curr1 = profiles.getFirstNode();
	while(curr1 != nullptr && curr1->data.getEmail() != email) curr1 = curr1->next;
	if(!curr1) return;
	(curr1->data).dropLike(post);
}

LinkedList<Profile *> SocialNetwork::getMutualFriends(const std::string &email1, const std::string &email2) {
    Node<Profile> *curr1 = profiles.getFirstNode();
	while(curr1 != nullptr && curr1->data.getEmail() != email1) curr1 = curr1->next;
	Node<Profile> *curr2 = profiles.getFirstNode();
	while(curr2 != nullptr && curr2->data.getEmail() != email2) curr2 = curr2->next;
	LinkedList<Profile *> mutual;
	if(curr1 == nullptr || curr2 == nullptr) return mutual;
	Node<Profile *> *fr1 = curr1->data.getFriends().getFirstNode();
	Node<Profile *> *fr2 = curr2->data.getFriends().getFirstNode();
	while(fr1){
		while(fr2){
			if(fr1->data == fr2->data){
				mutual.insertAtTheTail(fr1->data);
			}
			fr2 = fr2->next;
		}
		fr2 = curr2->data.getFriends().getFirstNode();
		fr1 = fr1->next;
	}
	return mutual;
}

LinkedList<Post *> SocialNetwork::getListOfMostRecentPosts(const std::string &email, int k) {
	Node<Profile> *curr1 = profiles.getFirstNode();
	while(curr1 != nullptr && curr1->data.getEmail() != email) curr1 = curr1->next;
	LinkedList<Post *> recent;
	if(!curr1) return recent;
	if(curr1->data.getPosts().isEmpty()){
		return recent;
	}
	int len = curr1->data.getPosts().getNumberOfNodes();
	Node<Post*> *curr2 = curr1->data.getPosts().getLastNode();
	if(k>len){
		k=len;
	}
	while(k>0 && curr2){
		recent.insertAtTheTail(curr2->data);
		curr2 = curr2->prev;
		k--;
	}
	return recent;
}

void SocialNetwork::print() const {
    std::cout << "# Printing the social network ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getNumberOfNodes() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of posts is " << posts.getNumberOfNodes() << ":" << std::endl;
    posts.print();

    std::cout << "# Printing is done." << std::endl;
}

