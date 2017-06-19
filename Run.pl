#!/usr/bin/perl
use warnings;

#########################################
# Input parameters

# Input dataset
$data = $ARGV[0];
open (IN, "<$ARGV[0]") || die "Error in input dataset file $ARGV[0]";
close(IN),

# Chromosome length file
open (IN, "<$ARGV[1]") || die "Error in the chromosome length file $ARGV[1]";

while (!eof(IN)){
	chomp($row=<IN>);
	@tmp = split /\t/, $row;
    push(@chromosomes, $tmp[0]);
	push(@start, $tmp[1]);
	push(@chrlen, $tmp[2]);
}

# Overlap threshold
$tau = $ARGV[2];

#############################################
# Iteration of RefGen algoritm over all chromosomes

$i = 0;	
foreach $chr(@chromosomes){
	system "./RefGen $data $data"."_$chr $start[$i] $chrlen[$i] $tau $chromosomes[$i]";
	$i += 1;
}

system "cat $data"."_chr* > $data"."_All_chr";
