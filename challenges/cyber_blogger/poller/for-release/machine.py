from generator.actions import Actions
import random
import string
import struct
import StringIO

def random_word(max_size=8, min_size=5):
    characters = string.letters
    max_size = max_size if max_size >= min_size else min_size
    max_size = random.randint(min_size, max_size)
    return ("".join(random.choice(characters) for c in range(max_size))).lower()

def random_text(max_words=50, min_words=2):
    max_words = max_words if max_words >= min_words else min_words
    text = ''
    for x in xrange(random.randint(min_words, max_words)):
        text += random_word() + ' '
        if x+1 % 8 == 0:
            text += '\n'
    return text

class BlogPictureFile():
    def __init__(self):
        self.filename = random_word()
        self.magic = 49
        self.size = random.randint(50, 260)

        self.magic_p = struct.pack('i', self.magic)
        self.size_p = struct.pack('i', self.size)
        self.data = ''

        while len(self.data) < self.size:
            self.data += random_word(10, 40) + '\n'
        self.data = self.data[:self.size]

    def getfile(self):
        return (self.magic_p + self.size_p + self.data)

    def getstr(self):
        return self.data

    def read_blog_data(self, _read):
        _read(self.getstr() + '\n')

class BlogAsciiFile():
    def __init__(self):
        self.filename = random_word()
        self.magic = 13873
        self.line_width = random.randint(20, 60)
        self.num_lines = random.randint(10, 30)

        self.magic_p = struct.pack('I', self.magic)
        self.line_width_p = struct.pack('H', self.line_width)
        self.num_lines_p = struct.pack('H', self.num_lines)
        self.data = ''

        for x in xrange(self.num_lines):
            self.data += random_word(self.line_width-1, self.line_width-1) + '\n'

    def getfile(self):
        return (self.magic_p + self.line_width_p + self.num_lines_p + self.data)

    def getstr(self):
        return self.data

    def read_blog_data(self, _read):
        _read(self.getstr() + '\n')

class BlogText():
    def __init__(self, text):
        self.text = text

    def read_blog_data(self, _read):
        _read("%s\n" % self.text)

def create_file():
    if random.randint(0,1):
        return BlogPictureFile()
    else:
        return BlogAsciiFile()

class Post():
    def __init__(self, owner, _read, _write):
        done = False
        self.owner = owner
        self.post_data = []
        self.title = random_text(5)
        self.likes = []

        _read("Enter post title: \n\t")
        _write("%s\n" % self.title)
        while not done:
            _read("Enter Post Text (end with: ```):\n")
            text = random_text()
            _write(text)
            _write("```\n")
            self.post_data.append(BlogText(text))

            if owner.is_full_user():
                _read("Upload Image?\n")
                _read("1. Yes\n")
                _read("2. No\n")
                _read("Selection: ")
                if random.randint(0,5) == 0:
                    _write("1\n")
                    blog_file = create_file()
                    _read("Enter Filename: ")
                    _write(blog_file.filename + '\n')
                    _read("--Begin Uploading File--\n")
                    _write(blog_file.getfile())
                    self.post_data.append(blog_file)
                else:
                    _write("2\n")

            _read("Add more Text?\n")
            _read("1. Yes\n")
            _read("2. No\n")
            _read("Selection: ")
            if random.randint(0,5) == 0:
                _write("1\n")
            else:
                _write("2\n")
                done = True

    def add_like(self, friend, _read):
        for like in self.likes:
            if like.username == friend.username:
                _read("You already liked this\n")
                return

        self.likes.append(friend)
        self.owner.total_likes += 1

    def read_post(self, _read):
        _read("Post by: %s\n" % self.owner.username)
        _read("---%s---\n" % self.title)
        for pdata in self.post_data:
            pdata.read_blog_data(_read)

    def read_title(self, _read):
        _read(self.title)


class User():
    def __init__(self, username, password, friendcode):
        self.username = username
        self.password = password
        self.friendcode = friendcode
        self.profile = ""
        self.total_likes = 0
        self.posts = []
        self.friends = []

    def is_full_user(self):
        if len(self.friends) >= 3 and len(self.posts) >= 5 and self.total_likes > 5:
            return True
        return False

    def update_profile(self, _write):
        self.profile = random_text()
        _write(self.profile)
        _write("```\n")

    def add_friend(self, friend, _read):
        if friend.username == self.username:
            _read("Trying to add self\n")
            return False

        for f in self.friends:
            if f.username == friend.username:
                return False
        self.friends.append(friend)
        return True

    def read_friend_list(self, _read):
        for i, friend in enumerate(self.friends):
            _read("%d - %s\n" % (i+1, friend.username))

    def read_post_list(self, _read):
        for i, post in enumerate(self.posts):
            _read("%d - %s\n" % (i+1, post.title))

    def read_profile(self, _read):
        _read("User %s's profile:\n" % self.username)
        if not self.profile:
            _read("No profile yet!\n")
        else:
            _read("%s\n" % self.profile)

class Blog(Actions):
    def _read(self, string):
        self.read(length=len(string), expect=string)

    def start(self):
        self.users = []
        self.state['logged_in_user'] = None

    def logged_out_menu(self):
        self._read("Select an option\n")
        self._read("1. Register\n")
        self._read("2. Log in\n")
        self._read("3. View a user's posts\n")
        self._read("4. View a user's profile\n")
        self._read("5. Quit\n")
        self._read("Selection: ")

    def register(self):
        self.write('1\n')
        username = random_word()
        password = random_word()
        friendcode = random_word()

        self._read("Enter username: ")
        self.write(username + "\n")
        for user in self.users:
            if user.username == username:
                self._read("Error: Username already exists. Try a different username\n")
                return

        self._read("Enter password: ")
        self.write(password + "\n")
        self._read("Friend code: ")
        self.write(friendcode + "\n")
        self.users.append(User(username, password, friendcode))

    def login(self):
        if not self.users:
            self.register()
            self.logged_out_menu()

        self.write("2\n")
        user = self.users[random.randint(0, len(self.users) - 1)]

        self.read("Username: ")
        self.write(user.username + "\n")
        self.read("Password: ")
        self.write(user.password + "\n")
        self._read("Authenticated\n")
        self.state['logged_in_user'] = user

    def view_user_posts_out(self):
        self.write("3\n")
        self._read("Enter username: ")
        if self.users:
            user = self.users[random.randint(0, len(self.users) - 1)]
        else:
            self.write("\n")
            self._read("Bad Username\n")
            return

        self.write(user.username + "\n")
        self._read("Select a post id to view\n")
        self._read("0. Go Back\n")
        user.read_post_list(self._read)
        self._read("Selection: ")
        if user.posts:
            choice = random.randint(0, len(user.posts))
            self.write("%d\n" % (choice))
            if choice == 0:
                self._read("Returning to main menu\n")
            else:
                post = user.posts[choice - 1]
                post.read_post(self._read)
        else:
            self.write("0\n")
            self._read("Returning to main menu\n")

    def view_user_profile_out(self):
        self.write("4\n")
        self._read("Enter username: ")
        if self.users:
            user = self.users[random.randint(0, len(self.users) - 1)]
        else:
            self.write("\n")
            self._read("Bad Username\n")
            return

        self.write(user.username + "\n")
        user.read_profile(self._read)

    def logged_in_menu(self):
        self._read("Select an option\n")
        self._read("1. Add new blog post\n")
        self._read("2. Delete blog post\n")
        self._read("3. Update profile\n")
        self._read("4. Add a friend\n")
        self._read("5. View my friends\n")
        self._read("6. Unfriend someone\n")
        self._read("7. View my posts\n")
        self._read("8. View my profile\n")
        self._read("9. View a user's posts\n")
        self._read("10. View a user's profile\n")
        self._read("11. Log out\n")
        self._read("Selection: ")

    def add_new_post(self):
        self.write("1\n")
        user = self.state['logged_in_user']
        post = Post(user, self._read, self.write)
        if post:
            user.posts.append(post)

    def delete_blog_post(self):
        self.write("2\n")
        user = self.state['logged_in_user']
        self._read("Select a post to delete:\n")
        self._read("0. Go Back\n")
        user.read_post_list(self._read)
        self._read("Selection: ")
        if user.posts:
            choice = random.randint(0, len(user.posts))
            self.write("%d\n" % (choice))
            if choice == 0:
                self._read("Returning to main menu\n")
            else:
                del user.posts[choice - 1]
        else:
            self.write("0\n")
            self._read("Returning to main menu\n")

    def update_profile(self):
        self.write("3\n")
        user = self.state['logged_in_user']
        self._read("Enter new profile info (end with: ```)\n")
        user.update_profile(self.write)

    def add_friend(self):
        self.write("4\n")
        user = self.state['logged_in_user']
        friend = self.users[random.randint(0, len(self.users) - 1)]

        self.read("Enter friend username: ")
        self.write(friend.username + "\n")
        self.read("Friend code: ")
        self.write(friend.friendcode + "\n")
        if user.add_friend(friend, self._read):
            self._read("Added friend, %s!\n" % friend.username)
        else:
            self._read("Couldn't add as friend.\n")

    def view_friends(self):
        self.write("5\n")
        user = self.state['logged_in_user']
        user.read_friend_list(self._read)

    def unfriend(self):
        self.write("6\n")
        user = self.state['logged_in_user']
        self._read("Select a user to unfriend:\n")
        self._read("0. Go Back\n")
        user.read_friend_list(self._read)
        self._read("Selection: ")
        if user.friends:
            choice = random.randint(0, len(user.friends))
            self.write("%d\n" % (choice))
            if choice == 0:
                self._read("Returning to main menu\n")
            else:
                del user.friends[choice - 1]
        else:
            self.write("0\n")
            self._read("Returning to main menu\n")

    def view_my_posts(self):
        self.write("7\n")
        user = self.state['logged_in_user']
        self._read("Select a post id to view\n")
        self._read("0. Go Back\n")
        user.read_post_list(self._read)
        self._read("Selection: ")
        if user.posts:
            choice = random.randint(0, len(user.posts))
            self.write("%d\n" % (choice))
            if choice == 0:
                self._read("Returning to main menu\n")
            else:
                post = user.posts[choice - 1]
                post.read_post(self._read)
        else:
            self.write("0\n")
            self._read("Returning to main menu\n")

    def view_my_profile(self):
        self.write("8\n")
        user = self.state['logged_in_user']
        user.read_profile(self._read)
        pass

    def view_user_posts_in(self):
        self.write("9\n")
        self._read("Enter username: ")
        cur_user = self.state['logged_in_user']
        if self.users:
            user = self.users[random.randint(0, len(self.users) - 1)]
        else:
            self.write("\n")
            self._read("Bad Username\n")
            return

        self.write(user.username + "\n")
        self._read("Select a post id to view\n")
        self._read("0. Go Back\n")
        user.read_post_list(self._read)
        self._read("Selection: ")
        if user.posts:
            choice = random.randint(0, len(user.posts))
            self.write("%d\n" % (choice))
            if choice == 0:
                self._read("Returning to main menu\n")
            else:
                post = user.posts[choice - 1]
                post.read_post(self._read)
                if cur_user.username != user.username:
                    self._read("Like Post?\n")
                    self._read("1. Yes\n")
                    self._read("2. No\n")
                    self._read("Selection: ")
                    if random.randint(0,1):
                        self.write("1\n")
                        post.add_like(cur_user, self._read)
                        self._read("Liked!\n")
                    else:
                        self.write("2\n")
        else:
            self.write("0\n")
            self._read("Returning to main menu\n")



    def view_user_profile_in(self):
        self.write("10\n")
        self._read("Enter username: ")
        if self.users:
            user = self.users[random.randint(0, len(self.users) - 1)]
        else:
            self.write("\n")
            self._read("Bad Username\n")
            return

        self.write(user.username + "\n")
        user.read_profile(self._read)

    def logout(self):
        self.write("11\n")
        self.state['logged_in_user'] = None
        self._read("Logging Out\n")

    def quit(self):
        self.write('5\n')
        self._read("Quitting\n")
