# SocialNetworkImplementation
A social network implementation by using doubly linked list. This project includes two big parts. **Linked List** part shows the data structure used in the project. **Social Network** part shows the social network implementation.

## Linked List Part

**Node** class represents nodes that build linked lists. A Node includes two node pointers, **prev** and **next**, pointing to its previous and next nodes in the doubly linked list, and the data variable of type **T** to hold the data. There are two constuctors. First one is constructs an object with null pointers and no data, second one is creates an object with given data, prev and next parameters. Definition is in *Node.h*.

**LinkedList** class implements a doubly linked list structure with the **head** and the **tail** pointers. It also includes several methods. Implemetations and explanations of these methods given in the *LinkedList.h*. 

## Social Network Part

**SocialNetwork** class represents the social network. It includes two **LinkedList** objects, **profiles** and **posts** with data type **Profile** and **Post**, respectively. **profiles** keeps the profiles in social network and **posts** includes the posts of social network. **Profile** class represents users of the social network and **Post** class represents the messages shared by users. **SocialNetwork** class has several methods to organize the social network. Definitions of these methods are in *SocialNetwork.h*. Implementations and explanations of them can be found in *SocialNetwork.cpp*. 

**Profile** class includes information about users. There are three **std::string** variables, **firstname**, **lastname** and **email**, to hold the data related with users. There are also three **LinkedList** including the pointers pointing to the profiles of the user's friends(**friends**), to the posts liked by the user(**likes**), to the posts shared by the user(**posts**). There are some methods in **Profile** class. Definition of class and declarations of methods is in *Profile.h*. Implementations and explanations of methods can be found in *Profile.cpp*.

**Post** class includes **message** variable of type **std::string** and **postId** variable of type **int** to hold the data related with posts of the users. There are some methods in **Post** class. Definition of class and declarations of methods is in *Post.h*. Implementations and explanations of methods can be found in *Post.cpp*.


