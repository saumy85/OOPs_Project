#include <bits/stdc++.h>

using namespace std;

class Comment {
private:
    string content;
    string author;
public:
    Comment(string comment = "", string author = "") :
        content(comment), author(author) {}

    void printComment() {
        cout << author << ": " << content << endl;
    }
};

class Post {
private:
    string content;
    string author;
    vector<Comment> comments;
    unordered_set<string> likes;
public:
    Post(const string& content, const string& author) :
        content(content), author(author) {}

    void addComment(const Comment& comment) {
        comments.push_back(comment);
    }

    void addLike(const string& username) {
        likes.insert(username);
    }

    void printPost() {
        cout << "Post by " << author << ": " << content << endl;
        cout << "Likes: " << likes.size() << endl;
        cout << "Comments: " << endl;

        for (auto& comment : comments) {
            comment.printComment();
        }
    }
};

class User {
private:
    string username;
    string password;
    unordered_set<string> likedPosts;

public:
    User(string username="", string password="") :
        username(username), password(password) {}

    string getUserName() {
        return username;
    }

    bool checkPassword(const string& password) {
        return this->password == password;
    }

    void likePost(const string& postId) {
        likedPosts.insert(postId);
    }

    void displayLikedPost() {
        cout << username << " liked post: " << likedPosts.size() << endl;
    }
};

class SocialMediaApp {
private:
    unordered_map<string, User> users;
    vector<Post> posts;
public:
    bool signup(const string& userName, const string& password) {
        if (users.count(userName) == 0) {
            users[userName] = User(userName, password);
            cout << "User " << userName << " registered successfully!" << endl;
            return true;
        }
        else {
            cout << "User already exists!" << endl;
            return false;
        }
    }

    User* login(const string& userName, const string& password) {
        if (users.count(userName) && users[userName].checkPassword(password)) {
            cout << "User " << userName << " logged in successfully! " << endl;
            return &users[userName];
        }
        else {
            cout << "Invalid login credentials!" << endl;
            return nullptr;
        }
    }

    void createPost(const string& username, const string& content) {
        if (users.count(username)) {
            posts.push_back(Post(content, username));
            cout << "Post created by " << username << endl;
        }
    }

    void likePost(const string& username, const int& postIndex) {
        if (users.count(username) && postIndex >= 0 && postIndex < posts.size()) {
            posts[postIndex].addLike(username);
            users[username].likePost(to_string(postIndex));
            cout << username << " liked the post." << endl;
        }
    }

    void commentOnPost(const string& username, int postIndex, const string& commentContent) {
        if (users.count(username) && postIndex >= 0 && postIndex < posts.size()) {
            Comment comment(commentContent, username);
            posts[postIndex].addComment(comment);
            cout << username << " commented on the post." << endl;
        }
    }

    void viewPosts() {
        cout << "\n----Posts----\n";
        for (size_t i = 0; i < posts.size(); i++) {
            cout << "Post Index: " << i << endl;
            posts[i].printPost();
            cout << endl;
        }
    }
};

int main() {
    SocialMediaApp fb;
    fb.signup("alice", "password");
    fb.signup("bob", "mypass");

    fb.createPost("alice", "hello world");
    fb.createPost("alice", "Ram Ram");
    fb.createPost("bob", "Hare Krishna");

    fb.viewPosts();
    fb.likePost("bob", 0);

    fb.commentOnPost("alice", 0, "Good morning, Bob!");

    fb.viewPosts();

    return 0;
}
