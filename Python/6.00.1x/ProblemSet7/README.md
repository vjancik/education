#Problem Set 7

In problem set 7, you will build a program to monitor news feeds over the Internet. Your program will filter the news, alerting the user when it notices a news story that matches that user's interests (for example, the user may be interested in a notification whenever a story related to the Red Sox is posted).

##Part 1: Data structure design

*Parsing* is the process of turning a data stream into a structured format that is more convenient to work with. We have provided you with code that will retrieve and parse the Google and Yahoo news feeds.

Parsing all of this information from the feeds that Google/Yahoo/the New York Times/etc. gives us is no small feat. So, let's tackle an easy part of the problem first: Pretend that someone has already done the specific parsing, and has left you with variables that contain the following information for a news story:

- globally unique identifier (GUID) - a string that serves as a unique name for this entry
- title - a string
- subject - a string
- summary - a string
- link to more content - a string

We want to store this information in an object that we can then pass around in the rest of our program. Your task, in this problem, is to write a class, `NewsStory`, **starting with a constructor** that takes `(guid, title, subject, summary, link)` as arguments and stores them appropriately. NewsStory also needs to contain the following methods:

- `getGuid(self)`
- `getTitle(self)`
- `getSubject(self)`
- `getSummary(self)`
- `getLink(self)`

##Part 2: Word Triggers

Given a set of news stories, your program will generate **alerts** for a subset of those stories. Stories with alerts will be displayed to the user, and the other stories will be silently discarded. We will represent alerting rules as **triggers**. A trigger is a rule that is evaluated over a single news story and may fire to generate an alert. For example, a simple trigger could fire for every news story whose title contained the word "Microsoft". Another trigger may be set up to fire for all news stories where the summary contained the word "Boston". Finally, a more specific trigger could be set up to fire only when a news story contained both the words "Microsoft" and "Boston" in the summary.

In order to simplify our code, we will use object polymorphism. We will define a trigger interface and then implement a number of different classes that implement that trigger interface in different ways.

####Trigger Interface

Each trigger class you define should implement the following interface, either directly or transitively. It must implement the `evaluate` method that takes a news item (`NewsStory` object) as an input and returns `True` if an alert should be generated for that item. We will not directly use the implementation of the `Trigger` class, which is why it throws an exception should anyone attempt to use it

Having a trigger that always fires isn't interesting; let's write some that are. A user may want to be alerted about news items that contain specific words. For instance, a simple trigger could fire for every news item whose *title* contains the word "Microsoft". In the following problems, you will create a `WordTrigger` *abstract* class and implement three classes that inherit from this class.

####Problem 2

Implement a word trigger abstract class, WordTrigger. It should take in a string word as an argument to the class's constructor.

WordTrigger should be a subclass of Trigger. It has one new method, isWordIn, which takes in one string argument text. It returns True if the whole word word is present in text, False otherwise, as described in the above examples. This method should not be case-sensitive. Implement this method.

####Problem 3

Implement a word trigger class, TitleTrigger, that fires when a news item's title contains a given word. The word should be an argument to the class's constructor. This trigger should not be case-sensitive (it should treat "Intel" and "intel" as being equal).

####Problem 4

Implement a word trigger class, SubjectTrigger, that fires when a news item's subject contains a given word. The word should be an argument to the class's constructor. This trigger should not be case-sensitive.

####Problem 5

Implement a word trigger class, SummaryTrigger, that fires when a news item's summary contains a given word. The word should be an argument to the class's constructor. This trigger should not be case-sensitive.

###Part 2: Composite triggers

####Problem 6

Implement a NOT trigger (`NotTrigger`).

This trigger should produce its output by inverting the output of another trigger. The NOT trigger should take this other trigger as an argument to its constructor. (Why its constructor? Because we can't change what parameters `evaluate` takes in... that'd break our polymorphism). So, given a trigger `T` and a news item `x`, the output of the NOT trigger's `evaluate` method should be equivalent to `not T.evaluate(x)`.

####Problem 7

Implement an AND trigger (`AndTrigger`).

This trigger should take two triggers as arguments to its constructor, and should fire on a news story only if both of the inputted triggers would fire on that item.

####Problem 8

Implement an OR trigger (`OrTrigger`).

This trigger should take two triggers as arguments to its constructor, and should fire if either one (or both) of its inputted triggers would fire on that item.

###Part 2: Phrase Triggers

####Problem 9

Implement a phrase trigger (PhraseTrigger) that fires when a given phrase is in any of the story's subject, title, or summary. The phrase should be an argument to the class's constructor.


###Part 3: Filtering

####Problem 10

Write a function, `filterStories(stories, triggerlist)` that takes in a list of news stories and a list of triggers, and returns a list of only the stories for which any of the triggers fires on. The list of stories should be unique - that is, do not include any duplicates in the list. For example, if 2 triggers fire on StoryA, only include StoryA in the list one time.


###Part 4: User-Specified Triggers

Right now, your triggers are specified in your Python code, and to change them, you have to edit your program. This is very user-unfriendly. (Imagine if you had to edit the source code of your web browser every time you wanted to add a bookmark!)

Instead, we want you to read your trigger configuration from a `triggers.txt` file every time your application starts, and use the triggers specified there.

####Problem 11

We have implemented the function `readTriggerConfig(filename)` for you. We've written code to open the file and throw away all the lines that don't begin with instructions (e.g. comments and blank spaces), and then reads in the code that defines triggers and instantiates the triggers by making a call to the helper function makeTrigger. The function `readTriggerConfig` then returns a list of triggers specified in the configuration file.

Implement the function `makeTrigger(triggerMap, triggerType, params, name)`. This helper function should build and return a trigger depending on its type. It also keeps track of triggers and names in a map.

**Classes I implemented**: NewsStory, WordTrigger, TitleTrigger, SubjectTrigger, SummaryTrigger, NotTrigger, AndTrigger, OrTrigger, PhraseTrigger

**Functions I implemented**: filterStories, makeTrigger
