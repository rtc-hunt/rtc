#! /usr/bin/env python

# This is the code written by Rhiannon to pull words out and filter them
# Preserved here in case it is useful.

def makewords():
    """Run this at a Python REPL and then paste the words.txt file in."""
    words = [0]
    while words[-1] != "American-Canadian":
        words.append(raw_input().strip())
    return words[1:]

def findwords(letter, position, length, words):
    matches = []
    for word in words:
        wordcheck = list(word)
        if len(word) == length:
            if wordcheck[position-1].lower() == letter.lower():
                matches.append(word)
    return matches
