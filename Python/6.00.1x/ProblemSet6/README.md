#Problem Set 6

##Caesar cipher

###Problem 1: Encryption

You'll now write a program to encrypt plaintext into ciphertext using the Caesar cipher.

Next, define the function `applyCoder`, which applies a coder to a string of text.

Once you have written `buildCoder` and `applyCoder`, you should be able to use them to encode strings.

Your friend, who is also taking 6.00.1x, is really excited about the program she wrote for Problem 1 of this problem set. She sends you emails, but they're all encrypted with the Caesar cipher!

If you know which shift key she is using, then decrypting her message is an easy task. If the string message is the encrypted message and `k` is the shift key she is using, then calling `applyShift(message, 26-k)` returns her original message. Do you see why?

The problem is, you don't know which shift key she is using. The good news is, you know your friend only speaks and writes English words. So if you can write a program to find the decoding that produces the maximum number of real English words, you can probably find the right decoding (there's always a chance that the shift may not be unique. Accounting for this would use statistical methods that we won't require of you.)

To assist you in solving this problem, we have provided a helper function, `isWord(wordList, word)`. This simply determines if word is a valid word according to the `wordList`. This function ignores capitalization and punctuation.

###Problem 2: Decryption

Now that you have all the pieces to the puzzle, please use them to decode the file `story.txt`. In the skeleton file, you will see a method `getStoryString()` that will return the encrypted version of the story. Fill in the following function; it should create the `wordList`, obtain the story, and then decrypt the story. Be sure you've read through the whole file to see what helper functions we've defined for you that may assist you in these tasks! This function will be only a few lines of code (our solution does it in 4 lines).

**Functions I implemented:** `buildCoder`, `applyCoder`, `applyShift`, `findBestShift`, `decryptStory`
