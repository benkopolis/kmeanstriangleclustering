#!/usr/bin/perl
use strict;
use warnings;

# (1) quit unless we have the correct number of command-line args
my $num_args = $#ARGV + 1;
if ($num_args != 1) {
  print "\nUsage: analyze_tfidf.pl filename\n";
  exit;
}

my $file = $ARGV[0];
open my $info, $file or die "Could not open $file: $!";

my $coords = -1;
my $lines = -1;

while( my $line = <$info>)  {   
    ++$lines;
	$coords = $coords + ($line =~ tr/ //);
}

my $coordsPerLine = $coords / $lines;

print "Lines: $lines, Coords: $coords\n";
print "Coords per point: $coordsPerLine\n";

