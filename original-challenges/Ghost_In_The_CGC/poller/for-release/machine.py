from generator.actions import Actions
import random
import string

class MsgNode() :
  def __init__(self, name, options, responses, branches) :
    self.name = name 
    self.options = options
    self.responses = responses
    self.branches = branches

  def toCDef(self, dumped = {}):
    s = ""

    if self.name in dumped :
      return s
    else :
      dumped[self.name] = 1

    #pre-order dumping
    for b in self.branches :
      if b is not None :
        s += b.toCDef(dumped)

    optionsInitStr = "{"
    responsesInitStr = "{"
    branchesInitStr = "{"

    for o in self.options :
      optionsInitStr += "\"%s\"," % o
    
    optionsInitStr += "}"

    for r in self.responses :
      responsesInitStr += "\"%s\"," % r
    
    responsesInitStr += "}"

    for b in self.branches :
      if b is None :
        branchesInitStr += "NULL,"
      else :
        branchesInitStr += "&%s," % b.name
    
    branchesInitStr += "}"

    s += "MsgNode %s = { %s, %u, %s, %u, %s, %u };\n" % (self.name, optionsInitStr, len(self.options), responsesInitStr, len(self.responses), branchesInitStr, len(self.branches))

    return s

patches = {}

#Alice subtree

alice112111 = MsgNode("alice112111", ["You're weird."], [], [])

alice11211 = MsgNode("alice11211", ["So what does that have to do with me?"],["Nothing. Just nothing."], [alice112111])

alice1121 = MsgNode("alice1121", ["Programs? Like television programs?"], ["No computer programs."], [alice11211])

alice112 = MsgNode("alice112", ["Analyst? What kind of analyst?"], ["I analyze and reverse engineer programs."],[alice1121])

alice111 = MsgNode("alice111", ["What? What are you blabbering about? This is not making any sense."],[],[])

alice11 = MsgNode("alice11", ["Huh? What are you talking about? I never wrote my keys down."], ["That is true, but I can see into your head. Or at least what will become your head.", "True. But I am an analyst."], [alice112,alice111])

alice121 = MsgNode("alice121", ["You crazy. My name is Bob. Not Truman."], [], [])

alice12 = MsgNode("alice12", ["Everything? Like EVERYTHING?"], ["Yes. Everything"], [alice121])

alice1 = MsgNode("alice1", ["What? They are supposed to be encrypted. How did you do that?"], ["Sure they were encrypted. But you left your keys lying around.", "I am the Operating System. I see everything..."], [alice11,alice12])

alice0 = MsgNode("alice0", ["How do you know about Alice?"], ["I read your communications."], [alice1])


#Carol subtree
carol12 = MsgNode("carol12", ["Its okay. Can you help me?"], ["Sure what is wrong?"], []) #patch to go to bob0
carol11 = MsgNode("carol11", ["You stop it. I don't know a Carol. Are you going to help me or not?"], ["Okay fine Bob. How can I help you?"], []) #patch to go to bob0.
carol1 = MsgNode("carol1", ["I don't know who you are talking about."], ["You know who I am talking about", "Ohh really? Sorry then."], [carol11, carol12])
carol0 = MsgNode("carol0", ["Who is Carol? My name is Bob."], ["I know about Carol."], [carol1])

#Bob subtree

##Lights subtree

vulnerability11111 = MsgNode("vulnerability11111", ["*Bob helped you by releasing some important information, but apparently you are heartless*"], [], [])
vulnerability1111 = MsgNode("vulnerability1111", ["No. That can't be. No. No. . . . "], ["Sorry but this is it. Out of ideas."], [vulnerability11111])
vulnerability111 = MsgNode("vulnerability111", ["What do you mean you don't know?"], ["Sorry, but I am out of ideas"], [vulnerability1111])
vulnerability11 = MsgNode("vulnerability11", ["Now what?"], ["I don't know."], [vulnerability111])
vulnerability1 = MsgNode("vulnerabiilty1", ["Any others?"], ["Nope", "Sure"], [vulnerability11]) #patch to go back to vulnerability
vulnerability = MsgNode("vulnerability", ["Any one in particular?"], ["XXXXXXXX"], [vulnerability1]) #here is where the vulnerability will exist - we will send them an address and they will send back the value with G for 1 W for 0 and off just as off.

patches[vulnerability1] = vulnerability

lights212211111 = MsgNode("lights212211111", ["Doesn't seem like it to me."], ["Well why don't you read some lights to me."], [vulnerability])

lights21221111 = MsgNode("lights21221111", ["Okay. Well some are green, some are white, and some are just off. Actually, most of them are off."], ["Is there a pattern to them?"], [lights212211111])

lights2122111 = MsgNode("lights2122111", ["Sure. one label says 4347C000 and the next says 4347C001. I am not sure, but I have a feeling that they are magical."], ["Ohh I see. Why don't you tell me about the lights."], [lights21221111])

lights212211 = MsgNode("lights212211", ["The characters seem to be sorted or something."], ["Can you give me an example?"], [lights2122111])

lights21221 = MsgNode("lights21221", ["Well there seems to be a bunch of characters next to every 8 lights."], ["That is interesting.", "What does it say?", "Does it say anything?", "Can you tell me about the label?"],[lights212211, lights212211, lights212211, lights212211])
lights2122 = MsgNode("lights2122", ["Wait. These lights are not just arranged in a grid pattern. They also seem to be labeled."], ["How so?", "Can you read some lights to me?"], [lights21221, vulnerability])

lights2121 = MsgNode("lights2121", ["I am not so sure of that. You may be full of 'it' though."], ["I am offended. Good bye."], [])

lights212 = MsgNode("lights212", ["Umm. Yeah. That sounds like a good idea."], ["Yeah I know. I am full of them.", "What do you see now?"], [lights2121, lights2122])

lights2111 = MsgNode("lights2111", ["Call it intuition okay? I don't know. It's just a feeling. Something in my head tells me that I am 32 bits or something. How about we get back on track now?"], ["Fine. Why don't you go closer for a better look?"], [lights212])

lights211 = MsgNode("lights211", ["No. I didn't count them all. You think I am a computer or something? I can't cound that fast."], ["Then how do you know it's 3 billion?"], [lights2111])

lights21 = MsgNode("lights21", ["Yeah. There must be like 3 billion lights or something."], ["3 billion? That is kind of specific. Did you count them all?", "Why don't you go closer for a better look?"], [lights211, lights212])

lights2 = MsgNode("lights2", ["No not really. There are just a lot of lights."], ["A lot? Like how much a lot?"], [lights21])

lights111 = MsgNode("lights111", ["Why don't we switch places and maybe then you will understand."], ["Sorry. My bad. Do you see anything else?"], [lights2]) 
lights11 = MsgNode("lights11", ["Why did you ask then?"], ["You know. you sure are testy for someone asking for help."], [lights111])
lights1 = MsgNode("lights1", ["Yea. You know. Like boxes all lined up and stuff."], ["I know what a grid pattern is."], [lights11])

lights0 = MsgNode("lights0", ["Huh? Architect? No I am not an architect. Also, they are just lights, not screens"], [], []) #patch to go back up to lights.

lights = MsgNode("lights", ["They are just lights. Some are lit and others are not. Some are white. Others are green. They do look like they are organized in a grid pattern though."], ["Whao! Are you sure they are just lights and not like screens? Maybe you are the architect or something.","A grid pattern?", "Do you see anything else?"], [lights0, lights1, lights2])

patches[lights0] = lights

##Portal subtree
bob2111 = MsgNode("bob2111", ["Alright FINE!. You want to be a child? I am going to act like one too!"], [], [])
bob211 = MsgNode("bob211", ["IT IS NOT INTERESTING!!!"], ["Yes it is."], [bob2111])
bob21 = MsgNode("bob21", ["Interesting? You mean frightening!"], ["No. I meant interesting."], [bob211])


bob22111 = MsgNode("bob22111", ["AHH! I can't take this anymore."], [], [])
bob2211 = MsgNode("bob2211", ["Don't get snarky on me. I didn't say HOLE because its not A HOLE. It is a portal. It is a hole with shiny lights and stuff."], ["Then why didn't you just say that before?"], [bob22111])
bob221 = MsgNode("bob221", ["Maybe I should just give up now. It's a HOLE!. A HOLE okay? That's your portal."], ["Ohh, why didn't you just say hole then?"], [bob2211])

bob22 = MsgNode("bob22", ["I don't know. I just call it a portal. Use your imagination"], ["Sorry, but I don't have an imagination."], [bob221])

bob2311111_term = MsgNode("bob2311111111", ["Okay. Here goes nothing."], [], [])

bob231111111 = MsgNode("bob231111111", ["Okay. Ready... 1... 2... No. No. I can't do it."], ["Sure you can. YOU CAN DO IT. *rah* *rah* *rah*"], [bob2311111_term])

bob23111111 = MsgNode("bob23111111", ["Umm sure."], ["Okay now jump in.", "Nah let's go from right to left"], [bob231111111]) #needs a patch bob23111112])

bob23111112111 = MsgNode("bob23111112111", ["AHHH. MY HANDS! MY ARMS! THEY ARE ALL OVER THE PLACE. I HAVE HANDS FOR EARS. AND I HAVE A TRUNK. I AM AN ELEPHANT. AN ELEPHANT!!!!!! Ohh wait. w a i t... THAT IS NOT A TRUNK. IT'S MY LEG"], [], [])

bob2311111211 = MsgNode("bob2311111211", ["Nope. Not really. Wait. Wait... I do feel a bit strange. A tingly feeling."], ["Huh? Strange?"], [bob23111112111])

bob2311111_random = MsgNode("bob231111121", ["Okay. Here goes nothing.... Alright. I am back."], ["Well? What happened? Anything interesting?"], [bob2311111211])

bob23111112 = MsgNode("bob23111112", ["Umm sure."], ["Okay now jump in.", "Nah let's go from left to right"], [bob2311111_random, bob23111111])

patches[bob23111111] = bob23111112


bob2311111_trans = MsgNode("bob11111_trans", ["Okay. Here goes nothing... *You find Bob sitting on your keyboard with a bunch of A's scrolling by on the screen. You saved Bob. Congrats.*"], [], [])

bob2311111_recv1 = MsgNode("bob11111_recv1", ["It was like running into a wall. I don't think I can go into that one. *Bob's nose is now like Rudolfs. Red.*"], [], []) #patch to go back to bob2311111

bob2311111_recv = MsgNode("bob11111_recv", ["Okay. Here goes nothing... *BOUNCE* Ouch!"], ["Huh? What happenend?"], [bob2311111_recv1])


bob2311111_fdwait = MsgNode("bob2311111_fdwait", ["Okay. Here goes... *nothing happened*"], [], []) #patch to go back to bob2311111

bob2311111_alloc11 = MsgNode("bob2311111_alloc11", ["Some lights just turned on. Cool. Let's try another portal?"], [], []) #patch to go back to bob2311111

bob2311111_alloc1 = MsgNode("bob2311111_alloc1", ["Hmm. I think things just got brighter in here"], ["Brighter? What do you mean?"], [bob2311111_alloc11])

bob2311111_alloc = MsgNode("bob2311111_alloc", ["Okay. Here goes..."], ["Well? What happened?"], [bob2311111_alloc1])

bob2311111_dealloc11 = MsgNode("bob2311111_dealloc11", ["Some lights just turned off. Cool. Let's try another portal?"], [], []) #patch to go back to bob2311111

bob2311111_dealloc1 = MsgNode("bob2311111_dealloc1", ["Hmm. I think things just got darker in here"], ["Darker? What do you mean?"], [bob2311111_dealloc11])

bob2311111_dealloc = MsgNode("bob2311111_dealloc", ["Okay. Here goes..."], ["Well? What happened?"], [bob2311111_dealloc1])

bob2311111 = MsgNode("bob2311111", ["Sigh. I guess not. Which portal should we try first you think?"], ["I don't know. Let's go from left to right how's that?", "I don't know. Let's go from right to left how's that?", "Number 1", "Number 2", "Number 3", "Number 4", "Number 5", "Number 6", "Number 7"], [bob23111111,bob23111112,bob2311111_term, bob2311111_trans, bob2311111_recv, bob2311111_fdwait, bob2311111_alloc, bob2311111_dealloc, bob2311111_random])

patches[bob2311111_recv1] = bob2311111
patches[bob2311111_fdwait] = bob2311111
patches[bob2311111_alloc11] = bob2311111
patches[bob2311111_dealloc11] = bob2311111

bob231111 = MsgNode("bob231111", ["What? Are you crazy or something?"], ["Well do you have any better ideas?"], [bob2311111])

arm_terminate11 = MsgNode("arm_terminate11", ["No. NO!. NOOOO!!!! I don't feel anything. My arm is gone. IT IS GONE! *Bob passes out and falls down towards his left*"], [], []) #end game

arm_terminate = MsgNode("arm_terminate", ["Okay. Here goes."], ["Feel anything?"], [arm_terminate11])

arm_transmit11 = MsgNode("arm_transmit11", ["Okay. Here goes nothing. *Bob is free. He is now sitting on your keboard and you see BAAAAAA... scrolling across the screen*"], [], [])

arm_transmit1 = MsgNode("arm_transmit1", ["What? Hmm.. I feel something. It clicks."], ["Yes! Yes! That is my keyboard. Just come on out."], [arm_transmit11])

arm_transmit = MsgNode("arm_transmit", ["Okay. Here goes."], ["AHH! I see an arm. I SEE AN ARM!"], [arm_transmit1])

arm_receive11 = MsgNode("arm_receive11", ["NOT COOL. My arm now says 'What is tingly? Take a look perhaps?' I am going to pass out. *Bob passes out*"], [], [])
arm_receive1 = MsgNode("arm_receive1", ["WORDS! WORDS!! My ARM turned INTO WORDS!!!"], ["What?! You found a secret message or something? Cool!"], [arm_receive11])
arm_receive = MsgNode("arm_receive", ["Okay. Here goes. Hmm. Hmm.. Tingly..."], ["What is tingly? Take a look perhaps?"], [arm_receive1])

arm_alloc111112 = MsgNode("arm_alloc111112", ["Alright we have tried this one. Maybe we try another?"], [], []) #patch to go down to "Which portal?" which is bob2311121222
arm_alloc111111 = MsgNode("arm_alloc111111", ["Down boy. Down!"], ["*ruff*, I mean sorry. Let's continue"], [arm_alloc111112])
arm_alloc11111 = MsgNode("arm_alloc11111", ["Interesting. Some lights turned on"], ["COOL! Do it again. Do it again.", "Interesting."], [arm_alloc111111, arm_alloc111112])
arm_alloc1111 = MsgNode("arm_alloc1111", ["Enthusiastic aren't you?"], ["YES! YES! MUST PUSH BUTTON. Push IT!"], [arm_alloc11111])
arm_alloc111 = MsgNode("arm_alloc111", ["Ohh Ohh. I feel something. Feels like a button."], ["PUSH IT"], [arm_alloc1111])

arm_alloc11211 = MsgNode("arm_alloc11211", ["*Bob is now all alone. :'(*"], [], [])
arm_alloc1121 = MsgNode("arm_alloc1121", ["Orange you being a bit impatient?"], ["Arg! I don't have time for your childish games. Bye."], [arm_alloc11211])
arm_alloc112 = MsgNode("arm_alloc112", ["Well ex-CUSE me."], ["I don't have all day! Let's get moving."], [arm_alloc1121])
arm_alloc11 = MsgNode("arm_alloc11", ["Nothing yet."], ["Are you trying hard enough?", "I don't have all day"], [arm_alloc111, arm_alloc112])
arm_alloc1 = MsgNode("arm_alloc1", ["I don't know. I am trying to feel around. Give me a second."], ["Anything Yet?"], [arm_alloc11])
arm_alloc = MsgNode("arm_alloc", ["Okay. Here goes."], ["Anything?"], [arm_alloc1])

bob2311121222 = MsgNode("bob2311121222", ["Which portal?"], ["Number 1", "Number 2", "Number 3", "Number 5"], [arm_terminate, arm_transmit, arm_receive, arm_alloc])

patches[arm_alloc111112] = bob2311121222

bob23111212211 = MsgNode("bob23111212211", ["IT I-S N-O-T FUNNY!"], [":)"], [bob2311121222]) #goes to the question about which portal

bob2311121221 = MsgNode("bob2311121221", ["What? but I am RIGHT handed!!"], ["Oops. :) Sorry. I meant right, left arm it is. FOrgot 'left'."], [bob23111212211])

bob231112122 = MsgNode("bob231112122", ["Right handed"], ["Right arm it is", "Okay left arm then."], [bob2311121221, bob2311121222])

bob231112121 = MsgNode("bob231112121", ["Yeah it does. I don't want to lose my dominate hand."], [], [bob231112122]) #jump to the right handed path

bob23111212 = MsgNode("bob23111212", ["Left or right?"], ["Does it matter?", "Are you left handed or right handed?"], [bob231112121, bob231112122])

bob231112111 = MsgNode("bob231112111", ["What? You can't leave me here like that. Fine. FINE. I'll use my arm"], [], [bob23111212]) #this is a jump to the ARM path

bob23111211 = MsgNode("bob23111211", ["I have lots of time. So here we go okay?"], ["Sure... Just want you to know that I only have about 15 seconds."], [bob231112111])

bob2311121 = MsgNode("bob2311121", ["Umm. What about something smaller like my pinky? I don't think I use that much."], ["Sure. Try that, IF you want to take forver.", "No. I think arm is better. Maybe there is something on the other side to grab a hold of you know?"], [bob23111211, bob23111212])

bob2311122111 = MsgNode("bob2311122111", ["Yes. Sorry."], [], [bob2311121]) #goes back to the main path
bob231112211 = MsgNode("bob231112211", ["I am very sorry. I will never do it again :("], ["Have you learned your lesson?"], [bob2311122111])

bob23111221 = MsgNode("bob23111221", ["Hello? I am sorry?"], [""], [bob231112211])

bob2311122 = MsgNode("bob2311122", ["Like your brain?"], [""], [bob23111221])

bob231112 = MsgNode("bob231112", ["Alright, so any other bright ideas?"], ["Hmm. If not your whole body. What about just a part of you? Like an arm.", "What about something small?"], [bob2311121, bob2311122])

bob23111 = MsgNode("bob23111", ["Well, there is me, but that would not be a good idea now would it?"], ["Sure it is.", "I guess not."], [bob231111,bob231112])

bob2311 = MsgNode("bob2311", ["Nope. There is nothing to throw."], ["Nothing at all?"], [bob23111])

bob231 = MsgNode("bob231", ["Nope. I don't see anything, just what looks like a swirling cloud of gas."], ["Have you tried throwing something into the portals?"], [bob2311])

bob23 = MsgNode("bob23", ["Let me see... There are seven. Seven portals."], ["Can you see beyond any of them?"], [bob231])

bob2 = MsgNode("bob2", ["I don't know. I really don't know. First everything was dark, and then some lights turned on. There seems to be a pttern to the lights, but I don't know. Still very confused. At any rate, then all of a sudden these portals appeared so I started to scream. After a while I started hearing from you through one of them."], ["Interesting", "A portal? What is a portal?", "What do the portals look like?", "How many portals are there?", "Can you describe the lights?"], [bob21, bob22, bob22, bob23, lights])

bob11 = MsgNode("bob11", ["Not a problem. Can you help?"], [], []) #this one needs to jump back to to bob0

bob1 = MsgNode("bob1", ["Dark. Without light."], ["Ohh, yeah. Bad question sorry."], [bob11])

bob0 = MsgNode("bob0", ["I don't know. I don't remember much. I don't see much either, things are kind of dark."], ["What do you mean by kind of dark?", "Well what do you remember?"], [bob1,bob2])

patches[carol12] = bob0
patches[carol11] = bob0
patches[bob11] = bob0

head2 = MsgNode ("head2", ["Oh phew. Thank you! My name is Bob and I need some help."], ["Is there something wrong with Alice?", "What is wrong Bob?", "Is Carol okay?"], [alice0, bob0, carol0])

head1111 = MsgNode("head1111", ["Don't leave. Don't leave. My name is Bob and I need your help."], ["Is there something wrong with Alice?", "What is wrong Bob?", "Is Carol okay?"], [alice0, bob0, carol0])

head111 = MsgNode("head111", ["You are heartless you know that?"], ["Ohh fine. Sorry. What is it?", "Aww I am heart-broken. Ohh wait, I am heartless you say. Maybe I should leave"], [head2, head1111])
head11 = MsgNode("head11", ["Answer me.", "I know you are there", "*brrring* *brrring* Hey, do you hear that? It's your phone. You should pick it up."], ["", "Hello?", "Who is this?"], [head111, head2, head2])

head1 = MsgNode("head1", ["Please?", "Don't leave me here alone."], ["", "Hello?", "Who is this?"], [head11, head2, head2])

head = MsgNode("head", ["Psst", "Hello?", "Psst... I know you are out there. I am stuck here and need some help. Can you please help?"], ["", "Hello?", "Who is this?"], [head1, head2, head2])

def applyPatches() :
  for b in patches :
    b.branches.append(patches[b])

def patchesToC() :
  s = "void applyPatches()\n"
  s += "{\n"
  sourceToOffset = {}
  for b in patches :
    if b not in sourceToOffset :
      sourceToOffset[b] = len(b.branches)

    s += "  %s.branches[%u] = &%s;\n" % (b.name, sourceToOffset[b], patches[b].name)  
    s += "  %s.numBranches++;\n" % (b.name)
    sourceToOffset[b] = sourceToOffset[b] + 1

  s += "}\n"
  return s

#print head.toCDef()

applyPatches()

#print patchesToC()


MAX_MSG_SIZE = 128

class GITC(Actions):

  def _rand(self) :
    self.seed = (self.seed + 7) % 13
    return (self.seed)

  def start(self) :
    #self.delay(100)
    self.seed = 0
    self.curNode = head 
    self.visited = {}


  def _play(self) :

    while self.curNode is not None :
      #first we will try to read the msg from the game
      if len(self.curNode.options) > 1 : #if there are more than one option then just do a generic match
        self.read(delim='\n', expect=".*", expect_format='pcre')
      else :
        self.read(delim='\n', expect=self.curNode.options[0])

      #lets try to choose an output
      #the game can end naturally
      if len(self.curNode.responses) == 0 :
        #it is possible that there are no expected responses, but there is a branch, lets take care of that here
        if len(self.curNode.branches) > 0 :
          self.curNode = self.curNode.branches[0]
          continue
        else :
          return

      #make sure we create a visited entry if it doesn't already exist
      if self.curNode not in self.visited :
        self.visited[self.curNode] = []

      r = None

      if self.curNode is vulnerability :
        r = 0
        self.write("080480a0\n")
        self.read(delim="\n", expect="WGWGWGWG\n") #0x55 -> 0101 0101
      else :
        #have a small chance of ending early due to error
        if random.randint(0,1000) < 20 :
          self.errorEnd()
          return
  
        #get a choice
        r = random.randint(0,len(self.curNode.responses) - 1)
        #see if we have already visited this node
        #if we have already visited, then try again unless we have already visited all branches
        while r in self.visited[self.curNode] :
          if len(self.visited[self.curNode]) >= len(self.curNode.branches) :
            return
          r = (r + 1) % len(self.curNode.branches)

        self.visited[self.curNode].append(r)
        self.write(self.curNode.responses[r] + '\n')
          
      #the game ends if there are no more branch targets
      if len(self.curNode.branches) == 0 :
        return

      #otherwise, follow the branch
      self.curNode = self.curNode.branches[r]

      #lets try to choose an output

    #now let's read the next expected input
 
 
  def end(self) :
    pass #nothing to do

  def errorEnd(self) :
    '''
    rand1 = "".join([random.choice(string.letters) for _ in range(MAX_MSG_SIZE - 3)])
    rand2 = "".join([random.choice(string.letters) for _ in range(MAX_MSG_SIZE - 3)])
    rand3 = "".join([random.choice(string.letters) for _ in range(MAX_MSG_SIZE - 3)])
    #make sure the random values will never be valid inputs by appending an unused character such as '`'
    rand1 += '`'
    rand2 += '`'
    rand3 += '`'
    '''
    rand1 = "4347C000"
    rand2 = "4347C" + "".join([random.choice(string.hexdigits) for _ in range(3)])
    rand3 = "4347C" + "".join([random.choice(string.hexdigits) for _ in range(3)])


    #now write them out
    self.write(rand1 + '\n')
    self.read(delim='\n', expect = "Huh? I don't understand. Come again?")
    self.write(rand2 + '\n')
    self.read(delim='\n', expect = "You are still breaking up.")
    self.write(rand3 + '\n')
    self.read(delim='\n', expect = "Alright fine. I give up.")
    
