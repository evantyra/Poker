#!/bin/perl
use strict;

#call this script with four arguments:
#1. Executable of AIDeckDriverShell
#2. lower bound to test for starting money
#3. upper bound to test for starting money
#4. lower bound to test for cards drawn
#5. upper bound to test for cards drawn

if (@ARGV != 5)
{
    print "Script requires five arguments. Reference comments at header of script for instructions.\n";
    exit 0;
}

my $driver = $ARGV[0];
my $moneyLowBound = $ARGV[1];
my $moneyHighBound = $ARGV[2];
my $drawnLowBound = $ARGV[3];
my $drawnHighBound = $ARGV[4];
my $success = 0;
my $fail = 0;

if ($moneyLowBound < 0 or $drawnLowBound < 0 or $drawnHighBound > 52 or $moneyLowBound > $moneyHighBound or $drawnLowBound > $drawnHighBound)
{
    print "Error in user entry or boundaries. Please try again.\n";
    exit 0;
}

foreach my $i ($drawnLowBound..$drawnHighBound)
{
    foreach my $j ($moneyLowBound..$moneyHighBound)
    {
        my $output = `perl DeckAI.perl $driver $j $i`;
        my @array = split(/\n/, $output);
        
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
    }
}

if ($fail == 0)
{
    print "All tests passed\n";
}
else
{
    print "$fail tests failed.\n";
}
