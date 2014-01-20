#!/bin/perl
use strict;

#first param is executable of AIDeckDriverShell.cpp

my $numArgs = $#ARGV + 1;  #Number of arguments passed to script
my $numExpected = 3;
my $success = 0;
my $fail = 0; 

if ($numArgs != $numExpected)      #Number can change, just placeholder
{
    print "Please provide exactly $numExpected integer arguments to the test script.\n";
    exit 0;
}

my $driver = $ARGV[0]; 
my $output = `./$ARGV[0] $ARGV[1] $ARGV[2]`;     #Include arguments later
my @array = split (/\n/, $output);  #Split output on new lines

foreach my $line (0..$#array)
{
    my $currentLine = $array[$line];

    if ($currentLine =~ /Success/)
    {
        $success++;
    }
    else
    {
        $fail++;
    }
}

if ($fail == 0)
{
    print "Success\n";
}
else
{
    print "Failure\n";
}
