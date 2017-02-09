#!/usr/bin/perl -w

use strict;                        # important pragma
print "What is your username?  ";  # print out the question
my $username;                      # "declare" variable
$username = <STDIN>;               # ask for the username
chomp($username);                  # cut off new line
print "Hello, $username.\n";       # print out the greeting

