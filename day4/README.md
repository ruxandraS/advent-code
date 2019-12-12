# Day 4: Secure Container

#### Advent of Code 2019
The Advent of Code 2019 is available on-line [here](https://adventofcode.com/2019).

#### Part One


You arrive at the Venus fuel depot only to discover it's protected by a password. The Elves had written the password on a sticky note, but someone threw it out.

However, they do remember a few key facts about the password:

It is a six-digit number.
The value is within the range given in your puzzle input.
Two adjacent digits are the same (like 22 in 122345).
Going from left to right, the digits never decrease; they only ever increase or stay the same (like 111123 or 135679).
Other than the range rule, the following are true:

1. 111111 meets these criteria (double 11, never decreases).
2. 223450 does not meet these criteria (decreasing pair of digits 50).
3. 123789 does not meet these criteria (no double).

How many different passwords within the range given in your puzzle input meet these criteria?

#### Part Two

An Elf just remembered one more important detail: the two adjacent matching digits are not part of a larger group of matching digits.

Given this additional criterion, but still ignoring the range rule, the following are now true:

1. 112233 meets these criteria because the digits never decrease and all repeated digits are exactly two digits long.
2. 123444 no longer meets the criteria (the repeated 44 is part of a larger group of 444).
3. 111122 meets the criteria (even though 1 is repeated more than twice, it still contains a double 22).

How many different passwords within the range given in your puzzle input meet all of the criteria?

#### Compiling
Compile from parent directory
```sh
$ make container
```

#### Running
Run from parent directory
```sh
$ make run
```

#### Cleaning up folder
Clean up from parent directory
```sh
$ make clean
```
