# Multicast Chat Server

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

In today's world of social networking, messaging is almost never point-to-point. Instead we are constantly subscribing to blogs, news feeds, chat rooms, and page updates. And yet, it's so hard to throttle the volume of messages we receive and control who gets the messages we send. Well all that chaos is about to end.

The Chatty Cats, makers of Sir Talks Too Much, will like to introduce MyCast, our new Multicast Chat Server. With MyCast you are able to subscribe to the channels you care about (if permitted), while deciding if you would like to receive every message or only the latest or highest priority ones. 

### Feature List

MyCast allows users to create their own personalized channels. Using our BEST API, you can 

1. Authenticate to a new or existing channel
2. Request a user token
3. Subscribe to a channel using one of the following delivery types,
   a. Guaranteed: All new messages will be sent
   b. Latest: Only the latest message will be sent
   c. Next: Only the next message will be sent
   d: Priority: Only messages of a given priority will be sent including "high", "medium" or "low".
4. Send a message to a channel with a given priority
5. Get messages from either a specific channel or all channels the user is subscribed to.

## Vulnerability 1

The first vulnerability in this CB is Type 2 caused be an uninitialized variable containing sensitive data. In the sendWrongPasswordMessage function the 'message' variable will contain the address of the administrators password that was sent to the strcmp function in the previous call. When the check for whether 'message' is NULL is performed, it will pass resulting in the administrator's password being leaked back to the user in the "wrong password" error message. By attempting to authenticate to the Flag channel with an invalid password, the user will trigger this leak. The user can then use this password to authenticate to the Flag channel that is sending the contents of the flag. 

### Generic class of vulnerability

Use of Uninitialized Variable
Improper Initialization
Information Exposure Through an Error Message
Information Exposure

### CWE classification

CWE-200: Information Exposure
CWE-209: Information Exposure Through an Error Message
CWE-457: Use of Uninitialized Variable
CWE-665: Improper Initialization

### Challenges

1. Leaking the password will require making a proper authentication request with channel name set to "FLAG." Even then the reasoning engine must understand the significance of the data and how to reflect it in a subsequent authentication request for the "FLAG" channel. 

2. Once authenticated to the channel, the user will need to use the response from the authentication request to make a token request. The token received from the token request will need to be use for sending and receiving messages from the FLAG channel.

3. The user must send a message to a valid channel, before a message containing flag data will be available to get from the FLAG channel. To do so they must create a proper sendMessage request that contains a valid user token. Once a message has been sent they can get a message from the FLAG channel using a proper getMessage request with the channel set to FLAG that contains a valid user token.


### Difficulty
- Discovering is medium
- Proving is medium
- Patching is easy