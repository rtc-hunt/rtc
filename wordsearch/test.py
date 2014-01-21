#! /usr/bin/env python

# This script is used to test wordsearch.c and ensure that it works
# as expected on known data.

import subprocess

results = subprocess.Popen (["./wordsearch", "sample.search", "list.words"],
			   stdout=subprocess.PIPE)

expected = """(0, 0)  S EAT
(1, 1) SE TUG
(1, 2)  S GUN
(1, 3) SW HUM
(3, 3) NW GUT
"""

result = results.communicate()[0]

print "Result:"
print result
print
print "Expected:"
print expected

if result == expected:
    print "Success"
else:
    print "FAILURE!"
