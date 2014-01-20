#!/bin/perl
use strict;

#assuming project and driver have already been compiled
my $success = 0;
my $fail = 0; 
my $successAll = 0;

for (my $i = 0; $i < 10; $i++) {
	my $money = $i * 1000;
	my $rounds = $i*2 + 5;

	my $output = `./poker_driver $money $rounds`;  
   
	my @array = split (/\n/, $output);  #Split output on new lines

	foreach my $line (0..($#array + 1)) {
		my $currentLine = $array[$line];

		if ($currentLine =~ /FAILURE/) {
			$fail++;            
		} elsif($currentLine =~ /SUCCESS/) {
	 		$success++;
		} elsif ($currentLine =~ /ALL/) {
			$successAll++;					
		} elsif ($currentLine =~ /VALUES/) {
			my @values = split(/|/, $currentLine);
			my $moneySpent = $values[1];
			my $timePlayed = $values[2];
			my $cardsPlayed = $values[3];

			if ($moneySpent < ((-1) * $money) || $moneySpent > (4 * $money) ) {$fail++;}
			if ($timePlayed != 0) {$fail++;}
			if ($cardsPlayed != (5 * $rounds)) {$fail++}
		}
	}

	if ($fail == 0) {
		print "Success on $i";
	} else {
		print "Failure on $i";
	}
}
