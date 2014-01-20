#!/bin/perl
use strict;

#assuming project and driver have already been compiled

my $numArgs = $#ARGV + 1;  #Number of arguments passed to script
my $numExpected = 0;
my $success = 0;
my $fail = 0; 

if ($numArgs != $numExpected)      #Number can change, just placeholder
{
    print "Please provide exactly $numExpected integer arguments to the test script.\n";
    exit 0;
}

my $output = `./HandDr`;     #Include arguments later
my @array = split (/\n/, $output);  #Split output on new lines

foreach my $line (0..$#array)
{
    my $currentLine = $array[$line];

    if ($currentLine =~ /Failure/)
    {
        $fail++;
    }
    elsif($currentLine =~ /Success/)
    {
        $success++;
    }
}

if ($fail == 0)
{
    print "Successes: $success\n";
}
else
{
    print "Failures: $fail\n";
}
